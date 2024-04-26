#include "Network.h"
#include <iostream>
#include <fstream>

void Network::Init(size_t num_layers, const std::vector<int> num_neurons, const ActivationFunction& act_func, double rate) {
    num_layers_ = num_layers;
    num_neurons_ = num_neurons;
    layers_.resize(num_layers - 1, Layer());
    for (int i = 0; i < num_layers - 1; ++i) {
        layers_[i].Init(num_neurons[i + 1], num_neurons[i], act_func);
    }
    neurons_values_.resize(num_layers, Vector());
    neurons_errors_.resize(num_layers, Vector());
    for (int i = 0; i < num_layers; ++i){
        neurons_values_[i].Init(num_neurons[i]);
        neurons_errors_[i].Init(num_neurons[i]);
    }

    learning_rate_ = rate;
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

int Network::Propagate() {
    for (size_t i = 1; i < num_layers_; ++i) {
        Vector res = (layers_[i - 1].a_ * neurons_values_[i - 1]) + layers_[i - 1].b_;
        res = layers_[i - 1].act_func_(res);
        neurons_values_[i] = res;
    }
    std::pair<int, double> p = neurons_values_[num_layers_ - 1].FindMax();
    return p.first;
}

void Network::BackPropagate(int expect) {
    for (size_t i = 0; i < num_neurons_[num_layers_ - 1]; ++i) {
        if (i != expect) {
            neurons_errors_[num_layers_ - 1][i] = neurons_values_[num_layers_ - 1][i] * 
            layers_[num_layers_ - 2].act_func_(neurons_values_[num_layers_ - 1][i], true);
        }
        else{
            neurons_errors_[num_layers_ - 1][i] = (1.0 - neurons_values_[num_layers_ - 1][i]) * 
            layers_[num_layers_ - 2].act_func_(neurons_values_[num_layers_ - 1][i], true);
        }
    }
    for (int i = num_layers_ - 2; i >= 0; --i) {
        neurons_errors_[i] = layers_[i].aT_ * neurons_errors_[i + 1];
        for (int j = 0; j < num_neurons_[i]; j++) {
			neurons_errors_[i][j] *= layers_[i].act_func_(neurons_errors_[i][j], true);
        }
    }
}

void Network::WeightUpdate() {
    for (int i = 0; i < num_layers_ - 1; ++i) {
		for (int j = 0; j < num_neurons_[i + 1]; ++j) {
			for (int k = 0; k < num_neurons_[i]; ++k) {
				layers_[i].a_[j][k] += neurons_values_[i][k] * neurons_errors_[i + 1][j] * learning_rate_;
			}
		}
	}
	for (int i = 0; i < num_layers_ - 1; i++) {
		for (int k = 0; k < num_neurons_[i + 1]; k++) {
			layers_[i].b_[k] += neurons_errors_[i + 1][k] * learning_rate_;
		}
	}
}

void Network::SaveData() {
    std::ofstream fout;
	fout.open("Data.txt");
	if (!fout.is_open()) {
		std::cout << "Error reading the file";
		system("pause");
	}
	for (int i = 0; i < num_layers_ - 1; ++i)
		fout << layers_[i].a_ << "\n";

	for (int i = 0; i < num_layers_ - 1; ++i) {
		for (int j = 0; j < num_neurons_[i + 1]; ++j) {
			fout << layers_[i].b_[j] << "\n";
		}
	}
	std::cout << "Weights saved \n";
	fout.close();
}

void Network::ReadData() {
	std::ifstream fin;
	fin.open("Data.txt");
	if (!fin.is_open()) {
		std::cout << "Error reading the file";
		system("pause");
	}
	for (int i = 0; i < num_layers_ - 1; ++i) {
		fin >> layers_[i].a_;
	}
	for (int i = 0; i < num_layers_ - 1; ++i) {
		for (int j = 0; j < num_neurons_[i + 1]; ++j) {
			fin >> layers_[i].b_[j];
		}
	}
	std::cout << "Weights readed \n";
	fin.close();
}