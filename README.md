# HopfieldNetwork Documentation

## Overview
The `HopfieldNetwork` class implements a simple Hopfield Neural Network, capable of learning patterns, completing noisy patterns, and converging to stable states. It is designed for pattern recognition and stability analysis using energy minimization.

### Features:
- **Training**: Stores patterns in the weight matrix.
- **Energy Calculation**: Computes the energy of the system to determine stability.
- **State Update**: Updates all neurons synchronously to converge to stable states.
- **Weight Matrix Visualization**: Prints the weight matrix for debugging and inspection.

---

## Class Definition
### Header File: `HopfieldNetwork.h`
```cpp
#ifndef HOPFIELDNETWORK_H
#define HOPFIELDNETWORK_H

#include <vector>
#include <iostream>

class HopfieldNetwork {
public:
    HopfieldNetwork(int size);                          //* Constructor
    void train(std::vector<std::vector<int>> &patterns); //* Training function
    double energy(std::vector<int> &state);             //* Energy calculation
    std::vector<int> update(std::vector<int> &state);   //* Synchronous state update
    void print();                                       //* Prints the weight matrix

private:
    int size;                                           //? Network size
    std::vector<std::vector<double>> W;                 //? Weight matrix
};

#endif
```

---

## Member Functions

### 1. Constructor
**`HopfieldNetwork(int size)`**
- **Description**: Initializes the Hopfield Network with a given size (number of neurons).
- **Parameters**:
  - `size` (int): Number of neurons in the network.
- **Functionality**:
  - Creates a weight matrix `W` initialized to zero.

---

### 2. Training Function
**`void train(std::vector<std::vector<int>> &patterns)`**
- **Description**: Trains the network using Hebbian learning to store given patterns in the weight matrix.
- **Parameters**:
  - `patterns` (std::vector<std::vector<int>> &): A list of binary patterns (using `-1` and `1`) to store in the network.
- **Functionality**:
  - Initializes the weight matrix to zero.
  - For each pair of neurons \(i, j\), computes the weight:
    
    \[ W_{ij} = \frac{1}{N} \sum_{k} x_i^{(k)} x_j^{(k)} \]
    
    where \(N\) is the number of patterns and \(x_i^{(k)}\) is the \(i\)-th element of the \(k\)-th pattern.
  - Ensures no self-connections by setting \(W_{ii} = 0\).

---

### 3. Energy Function
**`double energy(std::vector<int> &state)`**
- **Description**: Calculates the energy of a given state.
- **Parameters**:
  - `state` (std::vector<int> &): The current state of the network.
- **Returns**:
  - (double): The energy value of the system.
- **Functionality**:
  - Computes the energy using the formula:
    
    \[ E = -\frac{1}{2} \sum_{i,j} W_{ij} s_i s_j \]

---

### 4. Update Function
**`std::vector<int> update(std::vector<int> &state)`**
- **Description**: Updates all neurons synchronously based on the current state.
- **Parameters**:
  - `state` (std::vector<int> &): The current state of the network.
- **Returns**:
  - (std::vector<int>): The updated state of the network.
- **Functionality**:
  - Computes the activation for each neuron:
    
    \[ \text{total} = \sum_{j} W_{ij} s_j \]
    
  - Applies the following update rule:
    - If `total > 0`: Set \(s_i = 1\).
    - If `total < 0`: Set \(s_i = -1\).
    - If `total == 0`: Preserve the previous state \(s_i\).

---

### 5. Print Function
**`void print()`**
- **Description**: Prints the weight matrix for inspection.
- **Functionality**:
  - Outputs the weight matrix with fixed-point precision to six decimal places.

---

## Member Variables

### 1. `int size`
- **Description**: The size of the network (number of neurons).

### 2. `std::vector<std::vector<double>> W`
- **Description**: The weight matrix representing connections between neurons.
- **Structure**: A 2D vector of size `size x size` initialized to zero.

---

## Example Usage
```cpp
#include <iostream>
#include <vector>
#include "HopfieldNetwork.h"

using namespace std;

int main() {
    HopfieldNetwork network(3);

    // Training patterns
    vector<vector<int>> patterns = {
        {1, -1, 1,
        -1, 1, -1,
         1, -1, 1},
    };

    cout << "Training Patterns:" << endl;
    for (const auto &p : patterns) {
        for (int v : p) cout << v << " ";
        cout << endl;
    }
    cout << endl;

    network.train(patterns);

    cout << "Weight Matrix:" << endl;
    network.print();
    cout << endl;

    // Test with a noisy pattern
    vector<int> test_pattern = {1, -1, -1,
                                -1, 1, -1,
                                 1, -1, 1};

    cout << "Testing with pattern: ";
    for (int v : test_pattern) cout << v << " ";
    cout << endl << endl;

    double prev_energy = network.energy(test_pattern);
    cout << "Initial Energy: " << prev_energy << endl;

    for (int i = 0; i < 5; i++) {
        test_pattern = network.update(test_pattern);
        double curr_energy = network.energy(test_pattern);

        cout << "\nIteration " << i + 1 << ":" << endl;
        cout << "Pattern: ";
        for (int v : test_pattern) cout << v << " ";
        cout << "\nEnergy: " << curr_energy;
        cout << "\nEnergy Change: " << curr_energy - prev_energy << endl;

        if (curr_energy == prev_energy) {
            cout << "Converged to a stable state." << endl;
            break;
        }

        prev_energy = curr_energy;
    }

    return 0;
}
```

---

## References
- [Hopfield Network GFG](https://www.geeksforgeeks.org/hopfield-neural-network/)
- Information Theory, Inference, and Learning Algorithms, Daviv J.C. MacKay