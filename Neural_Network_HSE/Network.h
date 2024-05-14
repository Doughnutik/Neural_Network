#pragma once
#include "Layer.h"
#include <map>

const std::map<std::string, std::pair<function, derivative>> func_names_map{
  {"sigmoida", {SigmoidaFunc, SigmoidaDer}}, {"relu", {ReluFunc, ReluDer}}, {"th", {ThFunc, ThDer}}
};

struct DigitData {
    std::vector<std::vector<double>> pixels;
    int digit;
};

class Network {
  public:
    void Init(size_t num_layers, const std::vector<int> num_neurons,
              const std::string& func_name, double rate);

    void PrintData();

    void LoadData(const std::vector<double> &vec);

    int Propagate();

    int Search(const Vector &vec);

    void PrintValues(size_t id);

    void BackPropagate(int expect);

    void WeightUpdate();

    void SaveData(const std::string& filename);

    void ReadData(const std::string& filename);

    void SaveConfig(const std::string& filename);

    void ReadConfig(const std::string& filename);

    std::vector<int> Train(const std::vector<DigitData>& digits);

    std::vector<int> Test(const std::vector<DigitData>& digits);

  private:
    size_t num_layers_;
    std::vector<int> num_neurons_;
    std::vector<Layer> layers_;
    std::vector<Vector> neurons_values_, neurons_errors_, sum_values_;
    function func_;
    derivative der_;
    std::string func_name_;
    double learning_rate_;
};
