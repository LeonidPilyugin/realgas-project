// 
// simpleljintegrator.hpp
// 
// This file contains SimpleLjIntegrator class
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#pragma once

#include "ljintegrator.hpp"

// class SimpleLjIntegrator : public LjIntegrator
// 
// Describes integrator of Lennard-Jones particle system
// computing by CPU
// 
// Methods:
// 1) SimpleLjIntegrator(const Environment&, Saver &scanner)
// 2) void Load(const Environment& env) override
// 3) Environment GetEnvironment() override
// 4) void SetSaver(Saver& saver) override
// 5) void Run(uint64_t steps, uint64_t dump, float dt) override
// 6) void SetProperties(const LjProperties &properties)
// 7) LjProperties GetProperties()
// 
class SimpleLjIntegrator : public LjIntegrator {
public:
    // SimpleLjIntegrator() = delete
    // 
    // Deleted default constructor
    // 
    SimpleLjIntegrator() = delete;

    // SimpleLjIntegrator(const SimpleLjIntegrator&) = delete
    // 
    // Deleted copy constructor
    // 
    SimpleLjIntegrator(const SimpleLjIntegrator&) = delete;

    // SimpleLjIntegrator(SimpleLjIntegrator&&) = delete
    // 
    // Deleted move constructor
    // 
    SimpleLjIntegrator(SimpleLjIntegrator&&) = delete;

    // SimpleLjIntegrator& operator=(const SimpleLjIntegrator&) = delete
    // 
    // Deleted copy assigment operator
    // 
    SimpleLjIntegrator& operator=(const SimpleLjIntegrator&) = delete;

    // SimpleLjIntegrator& operator=(SimpleLjIntegrator&&) = delete
    // 
    // Deleted move assigment operator
    // 
    SimpleLjIntegrator& operator=(SimpleLjIntegrator&&) = delete;

    // SimpleLjIntegrator(const Environment&, Saver &scanner)
    // 
    // Constructor
    // 
    // Arguments:
    // 1) const Environment& env -- environment
    // 2) Saver &saver -- saver
    // 
    SimpleLjIntegrator(const Environment &env, Saver &scanner, const LjProperties &prop);

    // void Load(const Environment& env) override
    // 
    // Loads environment
    // 
    // Arguments:
    // 1) const Environment& env -- environment to load
    // 
    // Returns: nothing
    // 
    void Load(const Environment&) override;

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

private:
    // void MoveBodies(float dt)
    // 
    // Moves bodies for dt time step
    // 
    // Arguments:
    // 1) float dt -- time step
    // 
    // Returns: nothing
    // 
    void MoveBodies(float dt);

    // Vector ComputeForce(const Particle &p1, const Particle &p2)
    // 
    // Computes force between two particles
    // 
    // Arguments:
    // 1) const Particle &p1 -- particle for which force is computing
    // 2) const Particle &p2 -- second particle
    // 
    // Returns force
    // 
    Vector ComputeForce(const Particle &p1, const Particle &p2);
};
