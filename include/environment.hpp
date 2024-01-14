// 
// environment.hpp
// 
// This file contains Environment struct
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#pragma once

#include "box.hpp"
#include "particle.hpp"

// struct Environment
// 
// Describes simulation environment
// 
// Fields:
// 1) Box box -- simulation cell
// 2) System system -- system of particle
// 
struct Environment {
    Box box; 
    System system;
};
