#pragma once
#include "Functions.h"
#include "LinAlg.h"

class Layer {
  public:
    Layer() = default;

    void Init(size_t rows, size_t cols);

    const Matrix& GetWeights() const;
    Matrix& ChangeWeights() const;

    const Vector& GetBias() const;
    Vector& ChangeBias() const;

  private:
    Matrix a_, aT_;  // weights
    Vector b_;  // bias
};
