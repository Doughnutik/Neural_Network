#include "ActivationFunction.h"

ActivationFunction::ActivationFunction(const act_func& func) {
    func_ = func;
}

Vector ActivationFunction::operator()(const Vector& vec, bool is_derivative = false) {
    return func_(vec, is_derivative);
}

double ActivationFunction::operator()(double v, bool is_derivative = false) {
    return func_(v, is_derivative);
}