#![qil-logo](https://github.com/amadogabriel/asti_dd_package/assets/75212399/05314653-5441-4701-bee3-2504aa454e23| width=100)
 A Parallelized Implementation of a Quantum Multi-Valued Decision Diagram(QMDD) Package Written in C++

With code from the QMDD implementation provided by Michael Miller (University of Victoria, Canada)
and Philipp Niemann (University of Bremen, Germany), and Technical University of Munich's Munich Quantum Toolkit (dd_package).

## Quantum Innovation Laboratory
The project entitled “Establishment of Quantum Innovation Laboratory: Optimizing a Decision Diagram-based Free and Open-Source Quantum Circuit Simulator for Benchmarking in an HPC Environment using Entanglement, Random Circuits, and Quantum Algorithms Benchmark Datasets”, or QCS Project, is an initiative for quantum computing research in DOST-ASTI that will serve as the foundation for the succeeding project proposals of the institution in this domain. The project will focus on the optimization of available quantum circuit simulators for execution in DOST-ASTI’s COARE HPC facility. Outputs of the project will allow local researchers to execute few-qubit simulation of quantum algorithms for algorithm verification in COARE. Also, knowledge-sharing activities will be conducted to teach/train potential researchers in the domain on how to use the simulators in COARE for their own quantum computing research.

## Usage

### System Requirements
1. g++/clang compiler.
2. openmp (openmp is included in g++, you might need to install it separately when using a different compiler.
3. graphviz (optional, for illustrating qmdd's)

### Windows users can run the executable file dd_example.exe to view a test run of 4 quantum circuits.
  
### Build and Run 

To build the package and run a small demo type:
```
$ git clone git clone --recurse-submodules --remote-submodules https://github.com/amadogabriel/asti_dd_package 
$ mkdir build
$ cd build 
$ cmake ..
$ make
$ ./dd_example
Bell state:

00: 0.707107+0i
01: 0+0i
10: 0+0i
11: 0.707107+0i


GHZ cirtcuit (10qbts):

0000000000: 0.707107+0i
1111111111: 0.707107+0i

3-qubit Quantum Fourier Transform

000: 0.353553+0i
001: 0.353553+0i
010: 0.353553+0i
011: 0.353553+0i
100: 0.353553+0i
101: 0.353553+0i
110: 0.353553+0i
111: 0.353553+0i
```

### Building on Windows
```
$ mkdir build && cd build
$ cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release
$ cmake --build . --config Release
```
#
