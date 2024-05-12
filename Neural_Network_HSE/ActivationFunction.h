#pragma once
#include <functional>
#include <vector>

#include "LinAlg.h"

template<typename act_func>
class ActivationFunction {
  public:
    ActivationFunction(const act_func &func);

    Vector operator()(const Vector &vec, bool is_derivative = false);

    double operator()(double v, bool is_derivative = false);

  private:
    act_func func_;
};