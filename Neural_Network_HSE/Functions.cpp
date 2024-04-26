#include "Functions.h"

Vector Sigmoida::operator()(const Vector& vec, bool is_derivative = false) {
    auto f{ [](double x) -> double {return 1 / (1 + exp(-x));}};
    Vector new_vec = vec;
    for (size_t i = 0; i < vec.Size(); ++i) {
        if (!is_derivative) {
            new_vec[i] = f(new_vec[i]);
        }
        else {
            new_vec[i] = f(new_vec[i]) * (1 - f(new_vec[i]));
        }
    }
    return new_vec;
}

double ReLU_func(double x, bool is_derivative = false) {
    const double alpha = 1e-2; // можно менять
    if (!is_derivative) {
        if (x < 0) return alpha * x;
        if (x > 1) return 1 + alpha * (x - 1);
        return x;
    }
    if (x < 0 or x > 1) return alpha;
    return 1;
}

Vector ReLU::operator()(const Vector& vec, bool is_derivative = false) {
    Vector new_vec = vec;
    for (size_t i = 0; i < vec.Size(); ++i) {
        if (!is_derivative) {
            new_vec[i] = ReLU_func(new_vec[i]);
        }
        else {
            new_vec[i] = ReLU_func(new_vec[i], true);
        }
    }
    return new_vec;
}

double Th_func(double x, bool is_derivative = false) {
    const double alpha = 1e-2; // можно менять
    auto f{ [](double x) -> double {return (exp(x) - exp(-x)) / (exp(x) + exp(-x));}};
    if (!is_derivative) {
       if (x < 0) return alpha * f(x);
       return f(x);
    }
    if (x < 0) return alpha * (1 - f(x) * f(x));
    return 1 - f(x) * f(x);
}

Vector Th::operator()(const Vector& vec, bool is_derivative = false) {
    Vector new_vec = vec;
    for (size_t i = 0; i < vec.Size(); ++i) {
        if (!is_derivative) {
            new_vec[i] = Th_func(new_vec[i]);
        }
        else {
            new_vec[i] = Th_func(new_vec[i], true);
        }
    }
    return new_vec;
}