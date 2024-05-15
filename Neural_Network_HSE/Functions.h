#pragma once
#include "LinAlg.h"
#include <functional>

using function = std::function<Vector(const Vector &)>;
using derivative = std::function<Vector(const Vector &)>;

Vector SigmoidaFunc(const Vector &vec);
Vector SigmoidaDer(const Vector &vec);

Vector ReluFunc(const Vector &vec);
Vector ReluDer(const Vector &vec);

Vector ThFunc(const Vector &vec);
Vector ThDer(const Vector &vec);

function sigmoida_func = SigmoidaFunc;
derivative sigmoida_der = SigmoidaDer;

function relu_func = ReluFunc;
derivative relu_der = ReluDer;

function th_func = ThFunc;
derivative th_der = ThDer;
