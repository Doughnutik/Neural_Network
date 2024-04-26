#pragma once
#include "ActivationFunction.h"
#include "LinAlg.h"

class Layer {
public:

void Init(size_t rows, size_t cols, const ActivationFunction& func);

friend Network;

private:
    Matrix a_;
    Vector b_;
    ActivationFunction act_func_;
};