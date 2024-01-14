// 
// gpuljintegrator.hpp
// 
// This file contains GpuLjIntegrator class
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#pragma once

#include "ljintegrator.hpp"

// size of HIP block
#define BLOCK 256

// class GpuLjIntegrator : public LjIntegrator
// 
// Describes integrator of Lennard-Jones particle system
// accelerated with AMD HIP technology
// 
// Methods:
// 1) GpuLjIntegrator(const Environment& env, Saver &saver, float eps = 1e-6f)
// 2) void Load(const Environment& env) override
// 3) Environment GetEnvironment() override
// 4) void SetSaver(Saver& saver) override
// 5) void Run(uint64_t steps, uint64_t dump, float dt) override
// 6) void SetEps(float eps)
// 7) float GetEps()
// 8) void SetProperties(const LjProperties &properties)
// 9) LjProperties GetProperties()
// 
class GpuLjIntegrator : public LjIntegrator {
public:
    // GpuLjIntegrator() = delete
    // 
    // Deleted default constructor
    // 
    GpuLjIntegrator() = delete;

    // GpuLjIntegrator(const GpuLjIntegrator&) = delete
    // 
    // Deleted copy constructor
    // 
    GpuLjIntegrator(const GpuLjIntegrator&) = delete;

    // GpuLjIntegrator(GpuLjIntegrator&&) = delete
    // 
    // Deleted move constructor
    // 
    GpuLjIntegrator(GpuLjIntegrator&&) = delete;

    // GpuLjIntegrator& operator=(const GpuLjIntegrator&) = delete
    // 
    // Deleted copy assigment operator
    // 
    GpuLjIntegrator& operator=(const GpuLjIntegrator&) = delete;

    // GpuLjIntegrator& operator=(GpuLjIntegrator&&) = delete
    // 
    // Deleted move assigment operator
    // 
    GpuLjIntegrator& operator=(GpuLjIntegrator&&) = delete;

    // GpuLjIntegrator(const Environment& env, Saver &saver, float eps = 1e-6f)
    // 
    // Constructor
    // 
    // Arguments:
    // 1) const Environment& env -- environment
    // 2) Saver &saver -- saver
    // 3) float eps = 1e-6f -- special computation parameter
    // 
    // Notes:
    // 1) float eps is used for computations in adding to
    //    denominator to prevent a zero division
    // 
    GpuLjIntegrator(const Environment& env, Saver &saver, const LjProperties &prop, float eps = 1e-6f);

    // void SetEps(float eps)
    // 
    // Sets eps value
    // 
    // Arguments:
    // 1) float eps -- special computation parameter
    // 
    // Returns: nothing
    // 
    // Notes:
    // 1) float eps is used for computations in adding to
    //    denominator to prevent a zero division
    // 
    void SetEps(float eps);

    // float GetEps()
    // 
    // Gets current eps value
    // 
    // Arguments: no
    // 
    // Returns: current eps value
    // 
    // Notes:
    // 1) float eps is used for computations in adding to
    //    denominator to prevent a zero division
    // 
    float GetEps();

    // void Load(const Environment& env) override
    // 
    // Loads environment
    // 
    // Arguments:
    // 1) const Environment& env -- environment to load
    // 
    // Returns: nothing
    // 
    void Load(const Environment& env) override;

    // Environment GetEnvironment() override
    // 
    // Returns environment
    // 
    // Arguments: no
    // 
    // Returns: copy of current environment
    // 
    Environment GetEnvironment() override;

    // void Run(uint64_t steps, uint64_t dump, float dt) override
    // 
    // Runs simulation
    // 
    // Arguments:
    // 1) uint64_t steps -- number of steps to run
    // 2) uint64_t dump -- number of steps to dump after
    // 3) float dt -- time step
    // 
    // Returns: nothing
    // 
    void Run(uint64_t steps, uint64_t dump, float dt) override;

protected:
    uint64_t n;  // number of threads to run
    float eps;  // eps
};
