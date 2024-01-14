// 
// ljintegrator.hpp
// 
// This file contains Ljintagrator class and LjProperties struct
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#pragma once

#include "integrator.hpp"

// struct LjProperties
// 
// Describes properties of one-component Lennard-Jones system
// 
// Fields:
// 1) float sigma -- sigma of each particle
// 2) float epsilon -- epsilon of each particle
// 3) mass -- mass of each particle
// 
struct LjProperties {
    float sigma, epsilon, mass;
};

// class LjIntegrator : public Integrator
// 
// Describes integrator of one-component Lennard-Jones system
// 
// Methods:
// 1) virtual void Load(const Environment&) = 0
// 2) virtual Environment GetEnvironment() = 0
// 3) virtual void SetSaver(Saver &scanner) = 0
// 4) virtual void Run(uint64_t steps, uint64_t dump, float dt) = 0
// 5) void SetProperties(const LjProperties &properties)
// 6) LjProperties GetProperties()
// 
class LjIntegrator : public Integrator {
public:

    // void SetProperties(const LjProperties &properties)
    // 
    // Sets properties of system
    // 
    // Arguments:
    // 1) const LjProperties &properties -- setting properties
    // 
    // Returns: nothing
    // 
    void SetProperties(const LjProperties &properties);

    // LjProperties GetProperties()
    // 
    // Gets properties of system
    // 
    // Arguments: no
    // 
    // Returns properties of system
    // 
    LjProperties GetProperties();

protected:
    LjProperties properties;  // properties of system
};
