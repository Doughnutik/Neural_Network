#pragma once
#include "LinAlg.h"

enum class Filling { Random, Zeroes };

class Layer {
  public:
    Layer() = default;

    void Init(size_t rows, size_t cols, Filling filling_type);

    const Matrix &GetWeights() const;
    Matrix &ChangeWeights();

    const Vector &GetBias() const;
    Vector &ChangeBias();

    const Matrix &GetWeightErrors() const;
    Matrix &ChangeWeightErrors();

    const Vector &GetBiasErrors() const;
    Vector &ChangeBiasErrors();

    void Reset();

    std::pair<size_t, size_t> GetSize() const;

  private:
    Matrix a_, weight_errors_; // weights
    Vector b_, bias_errors_;      // bias
    size_t rows_, cols_;
};
