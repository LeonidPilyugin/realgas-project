// 
// lammpssaver.cpp
// 
// This file contains LammpsSaver functions definitions
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#include "lammpssaver.hpp"

void LammpsSaver::Move(LammpsSaver &s) {
    // move output
    output = std::move(s.output);
}

LammpsSaver::LammpsSaver(LammpsSaver &&s) {
    // move
    Move(s);
}

LammpsSaver& LammpsSaver::operator=(LammpsSaver &&s) {
    // if s is not this, move
    if (this != &s) {
        Move(s);
    }

    // return
    return *this;
}

LammpsSaver::LammpsSaver(std::string &path) {
    // open file
    output.open(path);
}

LammpsSaver::~LammpsSaver() {
    // close if is opened
    if (IsOpen()) {
        Close();
    }
}

void LammpsSaver::Save(const Environment &environment, uint64_t timestep) {
    // output timestep
    output << "ITEM: TIMESTEP\n" << timestep << "\n";
    output << "ITEM: NUMBER OF ATOMS\n" << environment.system.size() << "\n";
    // output box
    output << "ITEM: BOX BOUNDS pp pp pp\n";
    output << environment.box.l.x << " " << environment.box.r.x << "\n";
    output << environment.box.l.y << " " << environment.box.r.y << "\n";
    output << environment.box.l.z << " " << environment.box.r.z << "\n";
    // output positions and velocities
    output << "ITEM: ATOMS id x y z vx vy vz\n";
    for (uint64_t i = 0; i < environment.system.size(); i++) {
        output << environment.system[i].id << " ";
        output << environment.system[i].pos.x << " ";
        output << environment.system[i].pos.y << " ";
        output << environment.system[i].pos.z << " ";
        output << environment.system[i].vel.x << " ";
        output << environment.system[i].vel.y << " ";
        output << environment.system[i].vel.z << "\n";
    }
}

bool LammpsSaver::IsOpen() {
    return output.is_open();
}

void LammpsSaver::Close() {
    output.close();
}
