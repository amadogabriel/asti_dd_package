# A Parallelized Implementation of Decision Diagrams Written in C++

With code from the QMDD implementation provided by Michael Miller (University of Victoria, Canada)
and Philipp Niemann (University of Bremen, Germany), and Technical University of Munich's Munich Quantum Toolkit (dd_package).

## Usage

### System Requirements

  
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

###Building on Windows
$ mkdir build && cd build
$ cmake .. -G "Visual Studio 15 2017" -A x64 -DCMAKE_BUILD_TYPE=Release
$ cmake --build . --config Release
#
