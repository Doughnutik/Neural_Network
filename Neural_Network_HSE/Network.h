#pragma once
#include "Layer.h"
#include "Functions.h"
#include "MnistReader.h"
#include <map>

const std::map<std::string, std::pair<function, derivative>> func_names_map{
    {"sigmoida", {SigmoidaFunc, SigmoidaDer}},
    {"relu", {ReluFunc, ReluDer}},
    {"th", {ThFunc, ThDer}}};

class Network {
  public:
    void Init(size_t num_layers, const std::vector<size_t>& num_neurons,
              const std::string &func_name, double rate);

    void Reset();

    void ApplyDeltas(size_t n);

    void PrintData();

    void LoadData(const std::vector<double> &vec);

    int Propagate();

    void PrintNeurons(size_t id);

    void BackPropagate(int expect);

    void SaveData(const std::string &filename);

    void ReadData(const std::string &filename);

    void SaveConfig(const std::string &filename);

    void ReadConfig(const std::string &filename);

    void Train(const std::vector<DigitData> &digits);

    std::vector<int> Test(const std::vector<DigitData> &digits);

  private:
    size_t num_layers_;
    std::vector<size_t> num_neurons_;
    std::vector<Layer> layers_;
    std::vector<Vector> neurons_values_, neurons_errors_, sum_values_;
    function func_;
    derivative der_;
    std::string func_name_;
    double learning_rate_;
};
