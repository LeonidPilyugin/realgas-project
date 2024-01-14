// 
// box.hpp
// 
// This file contains Box struct
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#pragma once

#include "vector.hpp"

// struct Box
// 
// Describes simulation cell
// 
// Fields:
// 1) Vector l -- position of left corner
// 2) Vector r -- position of right corner
// 
struct Box {
    Vector l, r;
};
