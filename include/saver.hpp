// 
// saver.hpp
// 
// Contains Saver class
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#pragma once

#include "environment.hpp"

// class Saver
// 
// Describes a saver
// 
// Methods:
// 1) virtual void Save(const Environment&, uint64_t) = 0
// 
class Saver {
public:
    // virtual void Save(const Environment &env, uint64_t step)
    // 
    // Saves environment and step
    // 
    // Arguments:
    // 1) const Environment &env -- environment to save
    // 2) uint64_t step -- step to save
    // 
    // Returns nothing
    // 
    virtual void Save(const Environment &env, uint64_t step) = 0;
};