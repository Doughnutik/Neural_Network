#pragma once
#include "ActivationFunction.h"
#include "LinAlg.h"

class Layer {
  public:
    Layer() = default;

    void Init(size_t rows, size_t cols, const ActivationFunction &func);

    friend Network;

  private:
    Matrix a_, aT_;
    Vector b_;
    ActivationFunction act_func_;
};