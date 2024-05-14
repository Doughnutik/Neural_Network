#pragma once
#include "Functions.h"
#include "LinAlg.h"

enum class Filling {
  Random, Zeroes
};

class Layer {
  public:
    Layer() = default;

    void Init(size_t rows, size_t cols, Filling filling_type);

    const Matrix& GetWeights() const;
    Matrix& ChangeWeights();

    const Vector& GetBias() const;
    Vector& ChangeBias();

    std::pair<size_t, size_t> GetSize() const;

  private:
    Matrix a_, aT_;  // weights
    Vector b_;  // bias
    size_t rows_, cols_;
};