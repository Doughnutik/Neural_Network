#pragma once
#include "Layer.h"

class Network {
  public:
    void Init(size_t num_layers, const std::vector<int> num_neurons,
              const ActivationFunction &act_func, double rate);

    void PrintData();

    void LoadData(const std::vector<double> &vec);

    int Propagate();

    int Search(const Vector &vec);

    void PrintValues(size_t id);

    void BackPropagate(int expect);

    void WeightUpdate();

    void SaveData();

    void ReadData();

  private:
    size_t num_layers_;
    std::vector<int> num_neurons_;
    std::vector<Layer> layers_;
    std::vector<Vector> neurons_values_, neurons_errors_;
    double learning_rate_ = 0.5;
};