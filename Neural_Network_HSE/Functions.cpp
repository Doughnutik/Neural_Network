#include "Functions.h"

Vector SigmoidaFunc(const Vector &vec) {
    auto f{[](double x) -> double { return 1 / (1 + exp(-x)); }};
    Vector new_vec = vec;
    for (size_t i = 0; i < vec.Size(); ++i) {
        new_vec[i] = f(new_vec[i]);
    }
    return new_vec;
}

Vector SigmoidaDer(const Vector &vec) {
    auto f{[](double x) -> double { return 1 / (1 + exp(-x)); }};
    Vector new_vec = vec;
    for (size_t i = 0; i < vec.Size(); ++i) {
        new_vec[i] = f(new_vec[i]) * (1 - f(new_vec[i]));
    }
    return new_vec;
}

Vector ReluFunc(const Vector &vec) {
    const double alpha = 1e-2; // можно менять
    Vector new_vec = vec;
    for (size_t i = 0; i < vec.Size(); ++i) {
        if (new_vec[i] < 0) {
            new_vec[i] *= alpha;
        } else if (new_vec[i] > 1)
            new_vec[i] = 1 + alpha * (new_vec[i] - 1);
    }
    return new_vec;
}

Vector ReluDer(const Vector &vec) {
    const double alpha = 1e-2; // можно менять
    Vector new_vec = vec;
    for (size_t i = 0; i < vec.Size(); ++i) {
        if (new_vec[i] < 0 or new_vec[i] > 1) {
            new_vec[i] = alpha;
        } else
            new_vec[i] = 1;
    }
    return new_vec;
}

Vector ThFunc(const Vector &vec) {
    const double alpha = 1e-2; // можно менять
    auto f{[](double x) -> double {
        return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
    }};
    Vector new_vec = vec;
    for (size_t i = 0; i < vec.Size(); ++i) {
        if (new_vec[i] < 0) {
            new_vec[i] = alpha * f(new_vec[i]);
        } else {
            new_vec[i] = f(new_vec[i]);
        }
    }
    return new_vec;
}

Vector ThDer(const Vector &vec) {
    const double alpha = 1e-2; // можно менять
    auto f{[](double x) -> double {
        return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
    }};
    Vector new_vec = vec;
    for (size_t i = 0; i < vec.Size(); ++i) {
        if (new_vec[i] < 0) {
            new_vec[i] = alpha * (1 - f(new_vec[i]) * f(new_vec[i]));
        } else {
            new_vec[i] = 1 - f(new_vec[i]) * f(new_vec[i]);
        }
    }
    return new_vec;
}
