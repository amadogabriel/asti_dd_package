
# A Parallelized Implementation of a Quantum Multi-Valued Decision Diagram(QMDD) Package Written in C++

With code from the QMDD implementation provided by Michael Miller (University of Victoria, Canada)
and Philipp Niemann (University of Bremen, Germany), and Technical University of Munich's Munich Quantum Toolkit (dd_package).

<img src="https://github.com/amadogabriel/asti_dd_package/assets/75212399/05314653-5441-4701-bee3-2504aa454e23"  width="400" height="400" />

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

![image](https://github.com/amadogabriel/asti_dd_package/assets/75212399/dd90a8a5-a703-48b4-9756-11882a06cb7f)


### Building on Windows
```
$ mkdir build && cd build
$ cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release
$ cmake --build . --config Release
```
#
