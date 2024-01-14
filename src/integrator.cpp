// 
// integrator.cpp
// 
// This file contains Integrator functions definitions
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#include "integrator.hpp"

void Integrator::SetSaver(Saver &saver) {
    this->saver = &saver;
}
