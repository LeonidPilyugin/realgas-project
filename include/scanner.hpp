//
// scanner.hpp
// 
// Contains Scanner class
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#pragma once

#include "environment.hpp"

// class Scanner
// 
// Describes a scanner
// 
// Methods:
// 1) virtual Environment Scan() = 0
// 
class Scanner {
public:
    // virtual Environment Scan() = 0
    // 
    // Scans environment
    // 
    // Arguments: no
    // 
    // Returns scanned environment
    // 
    virtual Environment Scan() = 0;
};