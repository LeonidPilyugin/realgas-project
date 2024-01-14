// 
// main.cpp
// 
// This file contains main function
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#include <string>
#include <iostream>
#include <boost/program_options.hpp>
#include "lammpssaver.hpp"
#include "lammpsscanner.hpp"
#include "particle.hpp"

namespace po = boost::program_options;

#if defined(GPU) // compile with AMD HIP acceleration
#include "gpuljintegrator.hpp"
using LI = GpuLjIntegrator;
#else // compile only for CPU
#include "simpleljintegrator.hpp"
using LI = SimpleLjIntegrator;
#endif


int main(int argc, char *argv[]) {
    // parse console arguments
    std::string input;    // input file path
    std::string output;   // output file path
    uint64_t iterations;  // number of iteration
    uint64_t dump;        // number of steps to dump after
    float dt;             // time step of simulation
    LjProperties prop;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("input,i", po::value<std::string>(&input), "input file path")
        ("output,o", po::value<std::string>(&output)->default_value("output.lammpstrj"), "output file path")
        ("iterations,I", po::value<uint64_t>(&iterations), "number of iterations")
        ("time,t", po::value<float>(&dt), "time step")
        ("dump,d", po::value<uint64_t>(&dump)->default_value(1), "number of iterations to dump last")
        ("sigma,s", po::value<float>(&(prop.sigma))->default_value(1.0f), "sigma")
        ("epsilon,e", po::value<float>(&(prop.epsilon))->default_value(1.0f), "epsilon")
        ("mass,m", po::value<float>(&(prop.mass))->default_value(1.0f), "mass")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        exit(0);
    }

    if (!vm.count("input") || !vm.count("iterations") || !vm.count("time")) {
        std::cerr << desc << "\n";
        exit(1);
    }

    LammpsScanner scanner(input);  // create scanner
    LammpsSaver saver(output);  // create saver
    LI integrator(scanner.Scan(), saver, prop);  // create integrator
    integrator.Run(iterations, dump, dt);  // run simulation

    return 0;
}