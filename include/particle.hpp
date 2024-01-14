// 
// particle.hpp
// 
// Contains a Particle struct and System class
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#pragma once
#include <cstdint>
#include <vector>
#include "vector.hpp"

// struct Particle
// 
// Describes a particle
// 
// Fields:
// 1) uint32_t id -- id
// 2) Vector pos -- position
// 3) Vector vel -- velocity
// 
struct Particle {
    uint32_t id;  // id
    Vector pos;  // position
    Vector vel;  // velocity
};

// System = std::vector<Particle>
// 
// Describes a system of particles
// 
// Notes:
// 1) Equal to std::vector<Particle> class
// 
using System = std::vector<Particle>;
