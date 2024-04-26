#pragma once
#include "LinAlg.h"

class Sigmoida {
public:

    Vector operator()(const Vector& vec, bool is_derivative = false);
};

class ReLU {
public:

    Vector operator()(const Vector& vec, bool is_derivative = false);
};

class Th{
public:

    Vector operator()(const Vector& vec, bool is_derivative = false);
};