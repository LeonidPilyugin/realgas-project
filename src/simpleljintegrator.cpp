// 
// simpleljintegrator.cpp
// 
// This file contains LammpsScanner functions definitions
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 

#include "simpleljintegrator.hpp"
#include <cmath>

SimpleLjIntegrator::SimpleLjIntegrator(const Environment &env, Saver &saver, const LjProperties &prop) {
    // load and set saver
    Load(env);
    SetSaver(saver);
    SetProperties(prop);
}

void SimpleLjIntegrator::Load(const Environment &env) {
    // copy environment
    environment = env;
    // change positions
    for (uint64_t i = 0; i < env.system.size(); i++) {
        environment.system[i].pos -= environment.box.l; 
    }
}

Environment SimpleLjIntegrator::GetEnvironment() {
    // result environment
    Environment result = environment;
    // change positions
    for (uint64_t i = 0; i < environment.system.size(); i++) {
        result.system[i].pos += environment.box.l; 
    }
    // return
    return result;
}

void SimpleLjIntegrator::Run(uint64_t steps, uint64_t dump, float dt) {
    // for each step
    for (uint64_t i = 0; i < steps; i++) {
        // move
        MoveBodies(dt);
        // save if neccesary
        if (i % dump == 0) {
            saver->Save(GetEnvironment(), i);
        }
    }
}

void SimpleLjIntegrator::MoveBodies(float dt) {
    // sizes of box
    Vector box_size = environment.box.r - environment.box.l;

    for (uint64_t i = 0; i < environment.system.size(); i++) {
        Vector force;
        Particle &p = environment.system[i];

        // compute force
        for (uint64_t j = 0; j < environment.system.size(); j++) {
            if (i != j) {
                force += ComputeForce(p, environment.system[j]);
            }
        }

        // change velocity
        p.vel += force * dt / properties.mass;
    }

    for (uint64_t i = 0; i < environment.system.size(); i++) {
        Particle &p = environment.system[i];
        // change position
        p.pos.x = fmodf(box_size.x + p.pos.x + p.vel.x * dt, box_size.x);
        p.pos.y = fmodf(box_size.y + p.pos.y + p.vel.y * dt, box_size.y);
        p.pos.z = fmodf(box_size.z + p.pos.z + p.vel.z * dt, box_size.z);
    }
}

Vector SimpleLjIntegrator::ComputeForce(const Particle &p1, const Particle &p2) {
    // difference in position
    Vector r = p1.pos - p2.pos;
    // size of box
    Vector box_size = environment.box.r - environment.box.l;
    // count position of the nearest image of p2
    r.x = r.x - (float)lroundf(r.x / box_size.x) * box_size.x;
    r.y = r.y - (float)lroundf(r.y / box_size.y) * box_size.y;
    r.z = r.z - (float)lroundf(r.z / box_size.z) * box_size.z;
    // (r, r)
    float r2 = r * r;
    // 1 / r
    float inv_dist = 1.0f / sqrtf(r2);
    // factor for difference in position
    float s = 24.0f * properties.epsilon *
        (2.0f * powf(properties.sigma * inv_dist, 12.0f) -
        powf(properties.sigma * inv_dist, 6.0f)) * inv_dist * inv_dist;

    // return result
    return r * s;
}
