#include "DDpackage.h"
#include <omp.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
    #define M_PI_4 M_PI/4
#endif
#include <vector>
#include <chrono>

namespace dd = dd_package;


//QFT circuit constructor for 3 qubits
dd::DDedge QFT3() {
    dd::DD_matrix CTm;
    double m_pi_4 = M_PI_4;

    
    // Define the Controlled-T gate matrix
    CTm[0][0] = dd::Cmake(1, 0);
    CTm[0][1] = dd::Cmake(0, 0);
    CTm[1][0] = dd::Cmake(0, 0);
    CTm[1][1] = dd::Cmake(std::cos(m_pi_4), std::sin(m_pi_4)); // e^(i*pi/4)

    // Define the SWAP gate matrix
    dd::DD_matrix SWAPm;
    SWAPm[0][0] = dd::Cmake(1, 0);
    SWAPm[0][1] = dd::Cmake(0, 0);
    SWAPm[0][2] = dd::Cmake(0, 0);
    SWAPm[0][3] = dd::Cmake(0, 0);
    SWAPm[1][0] = dd::Cmake(0, 0);
    SWAPm[1][1] = dd::Cmake(0, 0);
    SWAPm[1][2] = dd::Cmake(1, 0);
    SWAPm[1][3] = dd::Cmake(0, 0);
    SWAPm[2][0] = dd::Cmake(0, 0);
    SWAPm[2][1] = dd::Cmake(1, 0);
    SWAPm[2][2] = dd::Cmake(0, 0);
    SWAPm[2][3] = dd::Cmake(0, 0);
    SWAPm[3][0] = dd::Cmake(0, 0);
    SWAPm[3][1] = dd::Cmake(0, 0);
    SWAPm[3][2] = dd::Cmake(0, 0);
    SWAPm[3][3] = dd::Cmake(1, 0);

    int line[3];

    // apply Hadamard gate to q0
    line[0] = 2; line[1] = -1; line[2] = -1;
    dd::DDedge h_gate_q0 = DDmvlgate(dd::Hm, 3, line);

    // apply Controlled-S gate to q1 controlled by q0
    line[0] = 1; line[1] = 2; line[2] = -1;
    dd::DDedge cs_gate_q1_q0 = DDmvlgate(dd::Sm, 3, line);

    // apply Hadamard gate to q1
    line[0] = -1; line[1] = 2; line[2] = -1;
    dd::DDedge h_gate_q1 = DDmvlgate(dd::Hm, 3, line);

    // apply Controlled-T gate to q2 controlled by q0
    line[0] = 1; line[1] = -1; line[2] = 2;
    dd::DDedge ct_gate_q2_q0 = DDmvlgate(CTm, 3, line);

    // apply Controlled-S gate to q2 controlled by q1
    line[0] = -1; line[1] = 1; line[2] = 2;
    dd::DDedge cs_gate_q2_q1 = DDmvlgate(dd::Sm, 3, line);

    // apply Hadamard gate to q2
    line[0] = -1; line[1] = -1; line[2] = 2;
    dd::DDedge h_gate_q2 = DDmvlgate(dd::Hm, 3, line);

    // Swap q0 and q2
    line[0] = 2; line[1] = -1; line[2] = 1;
    dd::DDedge swap_gate_q0_q2 = DDmvlgate(SWAPm, 3, line);

    //Multiply gates to get 3-qubit QFT
    dd::DDedge qft3 = dd::DDmultiply(h_gate_q0, cs_gate_q1_q0);
    qft3 = dd::DDmultiply(qft3, h_gate_q1);
    qft3 = dd::DDmultiply(qft3, ct_gate_q2_q0);
    qft3 = dd::DDmultiply(qft3, cs_gate_q2_q1);
    qft3 = dd::DDmultiply(qft3, h_gate_q2);
    qft3 = dd::DDmultiply(qft3, swap_gate_q0_q2);

    return qft3;
}

dd::DDedge QFT10() {
    int num_qubits = 10;
    int line[10];
    dd::DD_matrix CTm;
    dd::DD_matrix SWAPm;

    // Initialize SWAP gate
    SWAPm[0][0] = dd::Cmake(1, 0);
    SWAPm[1][1] = dd::Cmake(1, 0);
    SWAPm[2][2] = dd::Cmake(0, 0);
    SWAPm[3][3] = dd::Cmake(0, 0);
    SWAPm[0][2] = dd::Cmake(0, 0);
    SWAPm[2][0] = dd::Cmake(1, 0);
    SWAPm[1][3] = dd::Cmake(1, 0);
    SWAPm[3][1] = dd::Cmake(0, 0);

    // Initialize empty edge
    dd::DDedge qft;

    for (int i = 0; i < num_qubits; ++i) {
        // Reset the line array
        std::fill(line, line + num_qubits, -1);

        // Apply Hadamard gate to the i-th qubit
        line[i] = 2;
        dd::DDedge h_gate = DDmvlgate(dd::Hm, num_qubits, line);
        qft = dd::DDmultiply(qft, h_gate);

        // Apply controlled gates
        for (int j = i+1; j < num_qubits; ++j) {
            double angle = M_PI / pow(2, j - i);
            // Define the Controlled-T gate matrix
            CTm[0][0] = dd::Cmake(1, 0);
            CTm[0][1] = dd::Cmake(0, 0);
            CTm[1][0] = dd::Cmake(0, 0);
            CTm[1][1] = dd::Cmake(std::cos(angle), std::sin(angle)); // e^(i*angle)

            // Reset the line array
            std::fill(line, line + num_qubits, -1);

            line[i] = 1; line[j] = 2;
            dd::DDedge ct_gate = DDmvlgate(CTm, num_qubits, line);
            qft = dd::DDmultiply(qft, ct_gate);
        }
    }

    // Apply SWAP gates
    for (int i = 0; i < num_qubits / 2; ++i) {
        // Reset the line array
        std::fill(line, line + num_qubits, -1);

        line[i] = 2; line[num_qubits - i - 1] = 1;
        dd::DDedge swap_gate = DDmvlgate(SWAPm, num_qubits, line);
        qft = dd::DDmultiply(qft, swap_gate);
    }

    return qft;
}


dd::DDedge GroverCircuit() {
    // Define the number of qubits
    const int numQubits = 3;

    // Define the Grover iteration count
    const int iterations = 1; // Modify this value for more iterations

    // Create the Hadamard gate
    int hLine[2] = {0, -1};
    dd::DDedge hGate = dd::DDmvlgate(dd::Hm, numQubits, hLine);

    // Create the Oracle gate (U_f)
    int uFLine[2] = {0, 1};
    dd::DDedge uFGate = dd::DDmvlgate(dd::Nm, numQubits, uFLine);

    // Create the Diffusion operator (U_s)
    int uSLine[2] = {0, -1};
    dd::DDedge uSGate = dd::DDmvlgate(dd::Nm, numQubits, uSLine);
    uSLine[0] = -1;
    uSLine[1] = 0;
    dd::DDedge uSControlGate = dd::DDmvlgate(dd::Nm, numQubits, uSLine);
    dd::DDedge uSControlHGate = dd::DDmultiply(hGate, uSControlGate);
    dd::DDedge uS = dd::DDmultiply(uSControlHGate, uSGate);

    // Construct the Grover's algorithm circuit
    dd::DDedge circuit = hGate;
    for (int i = 0; i < iterations; i++) {
        circuit = dd::DDmultiply(uFGate, circuit);
        circuit = dd::DDmultiply(uS, circuit);
    }

    return circuit;
}

dd::DDedge BellCicuit1() {
    /***** define Hadamard gate acting on q0 *****/

    // set control/target:
    //    -1 don't care
    //    0 neg. control
    //    1 pos. control
    //    2 target

    int line[2] = {-1,2};
    dd::DDedge h_gate = DDmvlgate(dd::Hm, 2, line);

    /***** define cx gate with control q0 and target q1*****/
    line[0] = 2;
    line[1] = 1;

    dd::DDedge cx_gate = DDmvlgate(dd::Nm, 2, line);

    //Multiply matrices to get functionality of circuit
    return dd::DDmultiply(cx_gate, h_gate);
}

dd::DDedge BellCicuit2() {
    /***** define Hadamard gate acting on q1 *****/
    int line[2] = {2,-1};
    dd::DDedge h_gate_q1 = DDmvlgate(dd::Hm, 2, line);

    line[0] = -1;
    line[1] = 2;
    dd::DDedge h_gate_q0 = DDmvlgate(dd::Hm, 2, line);

    /***** define cx gate with control q0 and target q1*****/
    line[0] = 1;
    line[1] = 2;
    dd::DDedge cx_gate = DDmvlgate(dd::Nm, 2, line);

    //Multiply matrices to get functionality of circuit
    return dd::DDmultiply(dd::DDmultiply(h_gate_q1, h_gate_q0), dd::DDmultiply(cx_gate, h_gate_q1));
}

dd::DDedge BellCircuit10() {
    int num_qubits = 10;
    dd::DDedge total_gate = dd::DDone;

    // Define Hadamard gate acting on first qubit
    std::vector<int> line(num_qubits, -1);
    line[0] = 2;
    dd::DDedge h_gate = DDmvlgate(dd::Hm, num_qubits, line.data());

    // Initialize total_gate with the Hadamard gate
    total_gate = h_gate;

    // Define CNOT gate with control first qubit and target each of the rest qubits
    for (int i = 1; i < num_qubits; ++i) {
        std::fill(line.begin(), line.end(), -1);
        line[0] = 1;
        line[i] = 2;
        dd::DDedge cx_gate = DDmvlgate(dd::Nm, num_qubits, line.data());

        // Multiply gates to get the total functionality of the circuit
        total_gate = dd::DDmultiply(cx_gate, total_gate);
    }

    return total_gate;
}

dd::DDedge BellCircuit100() {
    int num_qubits = 100;
    dd::DDedge total_gate = dd::DDone;

    // Define Hadamard gate acting on first qubit
    std::vector<int> line(num_qubits, -1);
    line[0] = 2;
    dd::DDedge h_gate = DDmvlgate(dd::Hm, num_qubits, line.data());

    // Initialize total_gate with the Hadamard gate
    total_gate = h_gate;

    // Define CNOT gate with control first qubit and target each of the rest qubits
    for (int i = 1; i < num_qubits; ++i) {
        std::fill(line.begin(), line.end(), -1);
        line[0] = 1;
        line[i] = 2;
        dd::DDedge cx_gate = DDmvlgate(dd::Nm, num_qubits, line.data());

        // Multiply gates to get the total functionality of the circuit
        total_gate = dd::DDmultiply(cx_gate, total_gate);
    }

    return total_gate;
}

int main() {

    
    //Initialize package
    dd::DDinit(false);

    // create Bell circuit 1
    dd::DDedge bell_circuit1 = BellCicuit1();

    // create Bell circuit 2
    dd::DDedge bell_circuit2 = BellCicuit2();

    /***** Equivalence checking *****/
    // if(bell_circuit1.p == bell_circuit2.p && bell_circuit1.w == bell_circuit2.w) {
    //     std::cout << "Circuits are equal!" << std::endl;
    // } else {
    //     std::cout << "Circuits are not equal!" << std::endl;
    // }
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end; 

    /***** Simulation *****/
    //Generate vector in basis state |00>
    begin = std::chrono::steady_clock::now();
    dd::DDedge zero_state = dd::DDzeroState(2);

    //Simulate the bell_circuit with initial state |00>
    dd::DDedge bell_state = dd::DDmultiply(bell_circuit1, zero_state);
    dd::DDedge bell_state2 = dd::DDmultiply(bell_circuit2, zero_state);
    end = std::chrono::steady_clock::now();

    dd::DDdotExportVector(bell_state, "bell_state.dot");

    //print result
    std::cout<<"\n\nBell state: \n\n";
    dd::DDprintVector(bell_state);
    std::cout << "Running time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "microseconds" << std::endl;
    
    begin = std::chrono::steady_clock::now();
    dd::DDedge zero_state30 = dd::DDzeroState(10);
    dd::DDedge bell_circuit30 = BellCircuit10();
    dd::DDedge bell_state30 = dd::DDmultiply(bell_circuit30, zero_state30);
 
    end = std::chrono::steady_clock::now();
    std::cout<<"\n\nGHZ cirtcuit (10qbts): \n\n";   
    dd::DDprintVector(bell_state30);
    std::cout << "Running time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "microseconds" << std::endl;


    begin = std::chrono::steady_clock::now();
    dd::DDedge zero_state100 = dd::DDzeroState(100);
    dd::DDedge bell_circuit100 = BellCircuit100();
    dd::DDedge bell_state100 = dd::DDmultiply(bell_circuit100, zero_state100);
    
    std::cout<<"\n\nGHZ cirtcuit (100qbts): \n\n";   
    dd::DDprintVector(bell_state30);
    end = std::chrono::steady_clock::now();
    std::cout << "Running time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "microseconds  " << std::endl;


    begin = std::chrono::steady_clock::now();
    dd::DDedge zero_state_3 = dd::DDzeroState(3);
    dd::DDedge QFT = QFT3();
    dd::DDedge QFT_zero_state = dd::DDmultiply(QFT, zero_state_3);
    std::cout <<"\n\n3-qubit Quantum Fourier Transform\n\n";
    dd::DDprintVector(QFT_zero_state);end = std::chrono::steady_clock::now();
    std::cout << "Running time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "microseconds  " << std::endl;

    begin = std::chrono::steady_clock::now();
    dd::DDedge zero_state_10 = dd::DDzeroState(10);
    dd::DDedge QFT10_circuit = QFT10();
    dd::DDedge QFT_zero_state10 = dd::DDmultiply(QFT10_circuit, zero_state_10);
    std::cout <<"\n\n10-qubit Quantum Fourier Transform\n\n";
    dd::DDprintVector(QFT_zero_state10);end = std::chrono::steady_clock::now();
    std::cout << "Running time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "microseconds  " << std::endl;


    std::cout <<"\n\nPress enter to exit\n\n";
    std::cin.get();
    /***** Custom gates *****/
    // dd::DD_matrix m;
    // m[0][0] = dd::Cmake(std::sqrt(1 / 2.0L), 0);
    // m[0][1] = dd::Cmake(std::sqrt(1 / 2.0L), 0);
    // m[1][0] = dd::Cmake(std::sqrt(1 / 2.0L), 0);
    // m[1][1] = dd::Cmake(-std::sqrt(1 / 2.0L), 0);

    // int line[1] = {2}; // target on first line

    // const dd::complex_value one{1, 0}, zero{0, 0};
    // dd::DD_matrix X{{{zero}, {one}}, {{one}, {zero}}};

    // dd::DDedge Xgate = DDmvlgate(X, 1, line);
    // dd::DDedge id = DDmultiply(Xgate, Xgate);
    // dd::DDdotExportMatrix(id, "id.dot");

    // dd::DDedge my_very_own_gate = dd::DDmvlgate(m, 1, line);

    // /***** print DDs as SVG file *****/
    // dd::DDdotExportMatrix(bell_circuit1, "bell_circuit1.dot");
    // dd::DDdotExportMatrix(bell_circuit2, "bell_circuit2.dot");

    // dd::DDdotExportMatrix(my_very_own_gate, "my_very_own_gate.dot");

    // dd::DDstatistics();
}
