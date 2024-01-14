// 
// ljintegrator.cpp
// 
// This file contains LjIntegrator functions definitions
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#include "ljintegrator.hpp"

void LjIntegrator::SetProperties(const LjProperties &prop) {
    properties = prop;
}

LjProperties LjIntegrator::GetProperties() {
    return properties;
}
