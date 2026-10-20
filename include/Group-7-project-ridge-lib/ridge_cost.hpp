#ifndef RIDGE_ML_RIDGE_COST_HPP
#define RIDGE_ML_RIDGE_COST_HPP

#include "Group-7-project-ridge-lib/matrix.hpp"

namespace ridge_ml {

// Returns sum((prediction - target)^2)/(2m) plus
// lambda * sum(weights^2)/(2m). theta[0] is treated as the intercept
// and is excluded from the L2 penalty.
double ridge_cost(
    const Vector& actual,
    const Vector& predicted,
    const Vector& theta,
    double lambda
);

} // namespace ridge_ml

#endif // RIDGE_ML_RIDGE_COST_HPP
