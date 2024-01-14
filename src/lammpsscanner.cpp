// 
// lammpsscanner.cpp
// 
// This file contains LammpsScanner functions definitions
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#include "lammpsscanner.hpp"
#include <limits>

#define SKIP_UNTIL(c) do { input.ignore(std::numeric_limits<std::streamsize>::max(), (c)); } while(false)
#define SKIP_LINE() SKIP_UNTIL('\n')
#define SKIP_LINES(n) for (uint64_t i = 0; i < (n); i++) SKIP_LINE()

void LammpsScanner::Move(LammpsScanner &s) {
    // move input
    s.input = std::move(input);
}

LammpsScanner::LammpsScanner(std::string &path) {
    // open file
    input.open(path);
}

LammpsScanner::LammpsScanner(LammpsScanner &&s) {
    // move
    Move(s);
}

LammpsScanner::~LammpsScanner() {
    // close if opened
    if (IsOpen()) {
        Close();
    }
}

LammpsScanner& LammpsScanner::operator=(LammpsScanner&& s) {
    // if s is not this, move
    if (this != &s) {
        Move(s);
    }

    // return
    return *this;
}

Environment LammpsScanner::Scan() {
    // result
    Environment result;
    // temporary structure
    Particle atom;
    // number of particles
    uint64_t n = 0;
    // input n
    SKIP_LINES(3);
    input >> n;
    // input box
    SKIP_LINES(2);
    input >> result.box.l.x >> result.box.r.x;
    input >> result.box.l.y >> result.box.r.y;
    input >> result.box.l.z >> result.box.r.z;
    // input particles
    SKIP_LINES(2);
    for (uint64_t i = 0; i < n; i++) {
        input >> atom.id;
        input >> atom.pos.x;
        input >> atom.pos.y;
        input >> atom.pos.z;
        input >> atom.vel.x;
        input >> atom.vel.y;
        input >> atom.vel.z;
        result.system.push_back(atom);
    }

    // return
    return result;
}

bool LammpsScanner::IsOpen() {
    return input.is_open();
}

void LammpsScanner::Close() {
    input.close();
}
