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

static function sigmoida_func = SigmoidaFunc;
static derivative sigmoida_der = SigmoidaDer;

static function relu_func = ReluFunc;
static derivative relu_der = ReluDer;

static function th_func = ThFunc;
static derivative th_der = ThDer;
