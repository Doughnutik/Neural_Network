#pragma once
#include "LinAlg.h"
#include <functional>

using function = std::function<Vector(const Vector &)>;
using derivative = std::function<Vector(const Vector &)>;

function sigmoida_func;
derivative sigmoida_der;

function relu_func;
derivative rule_der;

function th_func;
derivative th_der;
