#pragma once
#include "Functions.h"
#include "LinAlg.h"

class Layer {
  public:
    Layer() = default;

    void Init(size_t rows, size_t cols, const ActivationFunction &func);

    friend Network;

  private:
    Matrix a_, aT_;
    Vector b_;
    std::unique_ptr<ActivationFunction>
        act_func; // = std::make_unique<Derived>();
};
