#include "Layer.h"

void Layer::Init(size_t rows, size_t cols, const ActivationFunction& func) {
    a_.Init(rows, cols);
    a_.RandomFill();
    b_.Init(rows);
    b_.RandomFill();
    act_func_ = func;
}