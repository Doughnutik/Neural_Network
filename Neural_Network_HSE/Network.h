#pragma once
#include "Layer.h"

class Network {
public:

void Init(size_t num_layers, const std::vector<int> num_neurons, const ActivationFunction& act_func);

void PrintData();

void LoadData(const std::vector<double>& vec);

double Propagate();

int Search(const Vector& vec);

void PrintValues(size_t id);

private:
    size_t num_layers_;
    std::vector<int> num_neurons_;
    std::vector<Layer> layers_;
    std::vector<Vector> neurons_values_, neurons_errors_;
};