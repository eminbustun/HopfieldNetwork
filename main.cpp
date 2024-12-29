#include <iostream>
#include <vector>
#include "HopfieldNetwork.h"

using namespace std;

int main() {
    HopfieldNetwork network(3);

    // Training patterns'leri yazdır
    vector<vector<int>> patterns = {
        {1, -1, 1}, 
    };

    cout << "Training Patterns:" << endl;
    for(const auto& p : patterns) {
        for(int v : p) cout << v << " ";
        cout << endl;
    }
    cout << endl;

    network.train(patterns);

    cout << "Weight Matrix:" << endl;
    network.print();
    cout << endl;

    vector<int> test_pattern = {1, -1, -1};
    cout << "Testing with pattern: ";
    for(int v : test_pattern) cout << v << " ";
    cout << endl << endl;

    double prev_energy = network.energy(test_pattern);
    cout << "Initial Energy: " << prev_energy << endl;

    for (int i = 0; i < 5; i++) {
        test_pattern = network.update(test_pattern);
        double curr_energy = network.energy(test_pattern);
        
        cout << "\nIteration " << i+1 << ":" << endl;
        cout << "Pattern: ";
        for (int j = 0; j < test_pattern.size(); j++) {
            cout << test_pattern[j] << " ";
        }
        cout << "\nEnergy: " << curr_energy;
        cout << "\nEnergy Change: " << curr_energy - prev_energy << endl;
        
        prev_energy = curr_energy;
    }
}