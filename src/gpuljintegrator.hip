// 
// gpuljintegrator.hip
// This file contains definition od GpuLjIntegrator methods
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 

#include "gpuljintegrator.hpp"
#include "hip/hip_runtime.h"
#include <cmath>
#include <cstdlib>

GpuLjIntegrator::GpuLjIntegrator(const Environment &env, Saver &saver, const LjProperties &prop, float eps) {
    SetEps(eps);
    Load(env);
    SetSaver(saver);
    SetProperties(prop);
}

void GpuLjIntegrator::Load(const Environment &env) {
    // copy environment
    environment = env;
    // change positions
    for (uint64_t i = 0; i < env.system.size(); i++) {
        environment.system[i].pos -= environment.box.l; 
    }
    // compute number of threads
    n = environment.system.size() / BLOCK + ((environment.system.size() % BLOCK == 0) ? 0 : 1);
    n *= BLOCK;
}

void GpuLjIntegrator::SetEps(float eps) {
    this->eps = eps;
}

float GpuLjIntegrator::GetEps() {
    return eps;
}

Environment GpuLjIntegrator::GetEnvironment() {
    // result environment
    Environment result = environment;
    // change positions
    for (uint64_t i = 0; i < environment.system.size(); i++) {
        result.system[i].pos += environment.box.l; 
    }
    // return
    return result;
}

__global__ void MoveBodies(float4 *new_pos,
                           float4 *new_vel,
                           float4 *old_pos,
                           float4 *old_vel,
                           float dt,
                           uint16_t n,
                           uint16_t real_n,
                           float xsize,
                           float ysize,
                           float zsize,
                           float epsilon,
                           float sigma,
                           float mass,
                           float eps) {
    // thread index
    unsigned long index = blockIdx.x * blockDim.x + threadIdx.x;

    // position of current particle
    float4 pos = old_pos[index];
    // force
    float3 f = make_float3(0.0f, 0.0f, 0.0f);
    // distance to other particle
    float3 r;
    // velocity
    float4 vel;
    float inv_dist, s, r2;
    // shared buffer
    __shared__ float4 sp[BLOCK];
    unsigned long ind = 0;
    
    for (unsigned long i = 0; i < real_n / BLOCK; i++, ind += BLOCK) {
        // fill shared buffer
        sp[threadIdx.x] = old_pos[ind + threadIdx.x];
        __syncthreads();

        // compute forces from other particles
        for (unsigned long j = 0; j < BLOCK; j++) {
            // i == j
            // compute distances
            r.x = pos.x - sp[j].x - __float2int_rn((pos.x - sp[j].x) / xsize) * xsize;
            r.y = pos.y - sp[j].y - __float2int_rn((pos.y - sp[j].y) / ysize) * ysize;
            r.z = pos.z - sp[j].z - __float2int_rn((pos.z - sp[j].z) / zsize) * zsize;
            // compute inverted distance
            r2 = r.x * r.x + r.y * r.y + r.z * r.z;

            inv_dist = 1.0f / sqrtf(r2 + eps) * r2 / (r2 + eps);
            // compute force
            s = inv_dist * 24.0f * epsilon * (2.0f * powf(sigma * inv_dist, 12.0f) - powf(sigma * inv_dist, 6.0f));
            f.x += r.x * s * inv_dist;
            f.y += r.y * s * inv_dist;
            f.z += r.z * s * inv_dist;

        }
        __syncthreads();
        
    }

    // fill shared buffer
    sp[threadIdx.x] = old_pos[ind + threadIdx.x];
    __syncthreads();

    // compute forces from other particles
    for (unsigned long j = 0; j < real_n % BLOCK; j++) {
        // i == j
        // compute distances
        r.x = pos.x - sp[j].x - __float2int_rn((pos.x - sp[j].x) / xsize) * xsize;
        r.y = pos.y - sp[j].y - __float2int_rn((pos.y - sp[j].y) / ysize) * ysize;
        r.z = pos.z - sp[j].z - __float2int_rn((pos.z - sp[j].z) / zsize) * zsize;
        // compute inverted distance
        r2 = r.x * r.x + r.y * r.y + r.z * r.z;

        inv_dist = 1.0f / sqrtf(r2 + eps) * r2 / (r2 + eps);
        // compute force
        s = inv_dist * 24.0f * epsilon * (2.0f * powf(sigma * inv_dist, 12.0f) - powf(sigma * inv_dist, 6.0f));
        f.x += r.x * s * inv_dist;
        f.y += r.y * s * inv_dist;
        f.z += r.z * s * inv_dist;

    }
    __syncthreads();
    

    vel = old_vel[index];
    // accelerate
    vel.x += f.x * dt / mass;
    vel.y += f.y * dt / mass;
    vel.z += f.z * dt / mass;
    // move
    pos.x = fmod(xsize + pos.x + vel.x * dt, xsize);
    pos.y = fmod(ysize + pos.y + vel.y * dt, ysize);
    pos.z = fmod(zsize + pos.z + vel.z * dt, zsize);
    // write answer
    new_pos[index] = pos;
    new_vel[index] = vel;
}


void GpuLjIntegrator::Run(uint64_t steps, uint64_t dump, float dt) {
    // position and velocity arrays on device
    float4 *pps[2], *vps[2];
    // position and velocity arrays on host
    float4 *p_host, *v_host;
    // allocate memory on host
    p_host = (float4*) malloc(n * sizeof(float4));
    v_host = (float4*) malloc(n * sizeof(float4));
    // temporary variable for atom id
    uint64_t id;
    // sizes of box
    Vector box_size = environment.box.r - environment.box.l;

    // copy system to p_host and v_host
    for (uint64_t i = 0; i < n; i++) {
        // set particles only from environment 
        if (i < environment.system.size()) {
            Particle &p = environment.system[i];
            id = p.id - 1;
            p_host[id].x = p.pos.x;
            p_host[id].y = p.pos.y;
            p_host[id].z = p.pos.z;
            v_host[id].x = p.vel.x;
            v_host[id].y = p.vel.y;
            v_host[id].z = p.vel.z;
        }
    }

    // allocate memory for device arrays
    hipMalloc(&(pps[0]), n * sizeof(float4));
    hipMalloc(&(pps[1]), n * sizeof(float4));
    hipMalloc(&(vps[0]), n * sizeof(float4));
    hipMalloc(&(vps[1]), n * sizeof(float4));

    // copy positions and velocities
    hipMemcpy(pps[0], p_host, n * sizeof(float4), hipMemcpyHostToDevice);
    hipMemcpy(vps[0], v_host, n * sizeof(float4), hipMemcpyHostToDevice);

    // run
    for (uint64_t i = 0, j = 0; i < steps; i++, j = 1 - j) {
        // move particles
        hipLaunchKernelGGL(MoveBodies, dim3(n / BLOCK), dim3(BLOCK), 0, 0, pps[1-j],
            vps[1-j], pps[j], vps[j], dt, n,
            environment.system.size(), box_size.x, box_size.y, box_size.z,
            properties.epsilon, properties.sigma, properties.mass, eps);
        hipDeviceSynchronize();
        
        // dump if necessary
        if (i % dump == 0) {
            hipMemcpy(p_host, pps[1-j], n * sizeof(float4), hipMemcpyDeviceToHost);
            hipMemcpy(v_host, vps[1-j], n * sizeof(float4), hipMemcpyDeviceToHost);
            for (uint64_t k = 0; k < environment.system.size(); k++) {
                Particle &p = environment.system[k];
                p.id = k + 1;
                p.pos.x = p_host[k].x;
                p.pos.y = p_host[k].y;
                p.pos.z = p_host[k].z;
                p.vel.x = v_host[k].x;
                p.vel.y = v_host[k].y;
                p.vel.z = v_host[k].z;
            }
            saver->Save(GetEnvironment(), i);
        }
    }

    hipMemcpy(p_host, pps[1-j], n * sizeof(float4), hipMemcpyDeviceToHost);
    hipMemcpy(v_host, vps[1-j], n * sizeof(float4), hipMemcpyDeviceToHost);
    for (uint64_t k = 0; k < environment.system.size(); k++) {
        Particle &p = environment.system[k];
        p.id = k + 1;
        p.pos.x = p_host[k].x;
        p.pos.y = p_host[k].y;
        p.pos.z = p_host[k].z;
        p.vel.x = v_host[k].x;
        p.vel.y = v_host[k].y;
        p.vel.z = v_host[k].z;
    }

    // free memory
    free(p_host);
    free(v_host);
    hipFree(pps[0]);
    hipFree(pps[1]);
    hipFree(vps[0]);
    hipFree(vps[1]);
}
