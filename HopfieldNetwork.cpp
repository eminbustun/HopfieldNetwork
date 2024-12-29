#include <iostream>
#include <vector>
#include <iomanip> // Required for fixed and setprecision
#include "HopfieldNetwork.h"

using namespace std;

/*
The purpose of this network:

- It stores patterns in memory (train).
- It can complete corrupted/incomplete patterns (update).
- It continues updating until the nearest stable state is reached.
- The energy function shows how stable the system is. Lower the energy, more stable the system.
*/

HopfieldNetwork::HopfieldNetwork(int size)
{
    this->size = size;
    W = vector<vector<double>>(size, vector<double>(size, 0)); //* 2D vector
}

// w_ij = 0 if i ==j
// w_ij == w_ji
// N = pattern number
void HopfieldNetwork::train(vector<vector<int>> &patterns)
{

    int numPatterns = patterns.size();    //* N
    int patternSize = patterns[0].size(); //* Matrix size

    for (int i = 0; i < patternSize; i++) {
        for (int j = 0; j < patternSize; j++) {
            W[i][j] = 0;
        }
    }

    for (int i = 0; i < patternSize; i++)
    {
        for (int j = 0; j < patternSize; j++)
        {
         if (i != j) {
                double sum = 0;
                for (int k = 0; k < numPatterns; k++)
                {
                    sum += patterns[k][i] * patterns[k][j];
                }
                W[i][j] = sum / numPatterns;
            }
        }
    }
}

/*
* Low Energy = Stable system
*/
double HopfieldNetwork::energy(vector<int> &state)
{
    double energy = 0.0;
    int matrixSize = W[0].size();

    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            energy += W[i][j] * state[i] * state[j];
        }
    }
    energy = -0.5 * energy;

    return energy;
}

//* SYNC Update: Update all neurons at the same time.
vector<int> HopfieldNetwork::update(vector<int> &state)
{

    vector<int> new_state = state;

    int neuronSize = W[0].size();

    for (int i = 0; i < neuronSize; i++)
    {
        double total = 0;
        for (int j = 0; j < neuronSize; j++)
        {
            total += W[i][j] * state[j];
        }

        if (total > 0)
        {
            new_state[i] = 1;
        }
        else if (total < 0)
        {
            new_state[i] = -1;
        }
        else
        {
            new_state[i] = state[i];
        }
    }

    return new_state;
}

void HopfieldNetwork::print(){
    int matrixSize = W[0].size();
    cout << fixed << setprecision(6);
    for(int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            cout << W[i][j] << " ";
        }
        cout << endl;
    }
}