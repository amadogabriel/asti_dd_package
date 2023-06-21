# A Parallelized Implementation of Decision Diagrams Written in C++

With code from the QMDD implementation provided by Michael Miller (University of Victoria, Canada)
and Philipp Niemann (University of Bremen, Germany), and Technical University of Munich's Munich Quantum Toolkit (dd_package).

## Quantum Innovation Laboratory
The project entitled “Establishment of Quantum Innovation Laboratory: Optimizing a Decision Diagram-based Free and Open-Source Quantum Circuit Simulator for Benchmarking in an HPC Environment using Entanglement, Random Circuits, and Quantum Algorithms Benchmark Datasets”, or QCS Project, is an initiative for quantum computing research in DOST-ASTI that will serve as the foundation for the succeeding project proposals of the institution in this domain. The project will focus on the optimization of available quantum circuit simulators for execution in DOST-ASTI’s COARE HPC facility. Outputs of the project will allow local researchers to execute few-qubit simulation of quantum algorithms for algorithm verification in COARE. Also, knowledge-sharing activities will be conducted to teach/train potential researchers in the domain on how to use the simulators in COARE for their own quantum computing research.

## Usage

### System Requirements
1. g++/clang compiler.
2. openmp (openmp is included in g++, you might need to install it separately when using a different compiler.
3. graphviz (optional, for illustrating qmdd's)
  
### Build and Run 

To build the package and run a small demo type:
```
$ mkdir build
$ cd build 
$ cmake ..
$ make
$ ./dd_example
Circuits are equal!
00: 0.707107 + 0i
01: 0 + 0i
10: 0 + 0i
11: 0.707107 + 0i
Bell states have a fidelity of 1
Bell state and zero state have a fidelity of 0.707107

DD statistics:
  Current # nodes in UniqueTable: 18
  Total compute table lookups: 33
  Number of operations:
    add:  20
    mult: 95
    kron: 0
  Compute table hit ratios (hits/looks/ratio):
    adds: 0 / 4 / 0
    mult: 14 / 29 / 0.482759
    kron: 0 / 0 / -nan
  UniqueTable:
    Collisions: 2
    Matches:    20
```

### Building on Windows
```
$ mkdir build && cd build
$ cmake .. -G "Visual Studio 15 2017" -A x64 -DCMAKE_BUILD_TYPE=Release
$ cmake --build . --config Release
```
#
