#pragma once
#include "matrix.hpp"
#include <stdexcept>

namespace ridge {

Vector gaussian_solve(const Matrix& A, const Vector& b);
Vector fit_normal_equation(const Matrix& X, const Vector& y);

}
