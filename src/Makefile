# 
# Makefile
# 
# Build options:
# 1) to build cpu version run
#     make cpu
# 2) to build a gpu version run
#     make gpu
# 3) to remove object files run
#     make clean
# 4) to remove object files and executables run
#     make clean-all
# 
# Requirements:
# 1) Boost program options library
# 2) AMD HIP for gpu version
# 
# Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
# 

# C++ compiler
CXX = g++
# AMD HIP compiler
HIPC = hipcc
# CUDA compiler
CUDAC = nvcc
# C++ compiler flags
CXXFLAGS = -I../include
# AMD HIP compiler flags
HIPCFLAGS = -I../include
# CUDA compiler flags
CUDACFLAGS = -I../include
# CPU program name
NAME = realgas
# GPU program name
GPUNAME = realgas-gpu

# build cpu version
cpu: main-cpu.o lammpssaver.o lammpsscanner.o simpleljintegrator.o vector.o integrator.o ljintegrator.o
	$(CXX) $(CXXFLAGS) -o $(NAME) main-cpu.o lammpssaver.o lammpsscanner.o simpleljintegrator.o vector.o  integrator.o ljintegrator.o -l:libboost_program_options.so

# build gpu version
gpu: main-gpu.o lammpssaver.o lammpsscanner.o gpuljintegrator.o vector.o  integrator.o ljintegrator.o
	$(HIPC) $(HIPCFLAGS) -o $(GPUNAME) main-gpu.o lammpssaver.o lammpsscanner.o gpuljintegrator.o vector.o  integrator.o ljintegrator.o -l:libboost_program_options.so

cuda: main-gpu.o lammpssaver.o lammpsscanner.o cudaljintegrator.o vector.o  integrator.o ljintegrator.o
	$(CUDAC) $(CUDACFLAGS) -o $(GPUNAME) main-gpu.o lammpssaver.o lammpsscanner.o cudaljintegrator.o vector.o  integrator.o ljintegrator.o -l:libboost_program_options.so

main-gpu.o: main.cpp
	$(CXX) $(CXXFLAGS) -DGPU -c main.cpp -o main-gpu.o

main-cpu.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main-cpu.o

ljparticle.o:
	$(CXX) $(CXXFLAGS) -c ljparticle.cpp

vector.o: vector.cpp
	$(CXX) $(CXXFLAGS) -c vector.cpp

lammpssaver.o: lammpssaver.cpp
	$(CXX) $(CXXFLAGS) -c lammpssaver.cpp

lammpsscanner.o: lammpsscanner.cpp
	$(CXX) $(CXXFLAGS) -c lammpsscanner.cpp

gpuljintegrator.o: gpuljintegrator.hip
	$(HIPC) $(HIPCFLAGS) -c gpuljintegrator.hip

cudaljintegrator.o: cudagpuljintegrator.cu
	$(CUDAC) $(CUDACFLAGS) -c cudagpuljintegrator.cu

simpleljintegrator.o: simpleljintegrator.cpp
	$(CXX) $(CXXFLAGS) -c simpleljintegrator.cpp

integrator.o: integrator.cpp
	$(CXX) $(CXXFLAGS) -c integrator.cpp

ljintegrator.o: ljintegrator.cpp
	$(CXX) $(CXXFLAGS) -c ljintegrator.cpp

# remove object files
clean:
	rm -rf *.o

# remove object files and executables
clean-all:
	rm -rf *.o $(NAME) $(GPUNAME)
