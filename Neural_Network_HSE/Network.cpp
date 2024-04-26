#include "Network.h"
#include <iostream>

void Network::Init(size_t num_layers, const std::vector<int> num_neurons, const ActivationFunction& act_func) {
    num_layers_ = num_layers;
    num_neurons_ = num_neurons; 
    for (int i = 0; i < num_layers - 1; ++i) {
        layers_[i].Init(num_neurons[i + 1], num_neurons[i], act_func);
    }
    neurons_values_.resize(num_layers, Vector());
    neurons_errors_.resize(num_layers, Vector());
    for (int i = 0; i < num_layers; ++i){
        neurons_values_[i].Init(num_neurons[i]);
        neurons_errors_[i].Init(num_neurons[i]);
    }
}

void Network::PrintData() { 
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
    std::cout << num_layers_ << "слоёв нейросети\n";
    for (size_t i = 0; i < num_layers_; ++i) {
        std::cout << "На " << i << " слоё " << num_neurons_[i] << " нейронов\n";
    }
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
}

void Network::PrintValues(size_t id) {
    std::cout << "$$$   Values   $$$\n";
    for (size_t i = 0; i < num_neurons_[id]) {
        std::cout << i << " " << neurons_values_[id][i] << "\n";
    }
    std::cout << "$$$$$$$$$$$$$$$$$$\n";
}

void Network::LoadData(const std::vector<double>& vec) {
    neurons_values_[0] = Vector(vec);
}

double Network::Propagate() {
    for (size_t i = 1; i < num_layers_; ++i) {
        Vector res = (layers_[i - 1].a_ * neurons_values_[i - 1]) + layers_[i - 1].b_;
        res = layers_[i - 1].act_func_(res);
        neurons_values_[i] = res;
    }
    std::pair<int, double> p = neurons_values_[num_layers_ - 1].FindMax();
    return p.first;
}