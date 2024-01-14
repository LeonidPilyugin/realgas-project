// 
// integrator.hpp
// 
// This file contains Integrator class
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#pragma once

#include <cstdint>
#include "environment.hpp"
#include "saver.hpp"

// class Integrator
// 
// Describes integrator of particle system
// 
// Methods:
// 1) virtual void Load(const Environment&) = 0
// 2) virtual Environment GetEnvironment() = 0
// 3) virtual void SetSaver(Saver &scanner) = 0
// 4) virtual void Run(uint64_t steps, uint64_t dump, float dt) = 0
// 
class Integrator {
public:
    // virtual void Load(const Environment& env) = 0
    // 
    // Loads environment
    // 
    // Arguments:
    // 1) const Environment& env -- environment to load
    // 
    // Returns: nothing
    // 
    virtual void Load(const Environment& env) = 0;

    // virtual Environment GetEnvironment() = 0
    // 
    // Returns environment
    // 
    // Arguments: no
    // 
    // Returns: copy of current environment
    // 
    virtual Environment GetEnvironment() = 0;

    // virtual void SetSaver(Saver &scanner) = 0
    // 
    // Sets saver
    // 
    // Arguments:
    // 1) Saver &saver -- saver to use
    // 
    // Returns: nothing
    // 
    void SetSaver(Saver &saver);

    // virtual void Run(uint64_t steps, uint64_t dump, float dt) = 0
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
    virtual void Run(uint64_t steps, uint64_t dump, float dt) = 0;

protected:
    Environment environment; // environment
    Saver *saver;  // saver
}; 