//* Emin Ustun
//* This file includes the class definition of HopfieldNetwork

#ifndef HOPFIELDNETWORK_H
#define HOPFIELDNETWORK_H

#include <vector>
#include <iostream>

class HopfieldNetwork
{
public:
    HopfieldNetwork(int size);                          //* Constructor
    void train(std::vector<std::vector<int>> &patterns); //* training function
    double energy(std::vector<int> &state);             //* Energy calculation
    std::vector<int> update(std::vector<int> &state);
    void print();

private:
    int size;                                    //? Network size
    std::vector<std::vector<double>> W;          //? Weight matrix
};

#endif