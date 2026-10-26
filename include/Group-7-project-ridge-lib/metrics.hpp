#ifndef GROUP_7_PROJECT_RIDGE_LIB_METRICS_HPP
#define GROUP_7_PROJECT_RIDGE_LIB_METRICS_HPP

#include "Group-7-project-ridge-lib/matrix.hpp"

namespace ridge_ml {

// Standard error and goodness-of-fit scores for regression predictions.
class RegressionMetrics {
public:
    // Average absolute prediction error.
    static double mean_absolute_error(const Vector& actual, const Vector& predicted);
    // Average squared prediction error.
    static double mean_squared_error(const Vector& actual, const Vector& predicted);
    // Square root of MSE, in the same units as the target.
    static double root_mean_squared_error(const Vector& actual, const Vector& predicted);
    // Fraction of target variation explained; higher is better.
    static double r_squared(const Vector& actual, const Vector& predicted);
};

} // namespace ridge_ml

#endif // GROUP_7_PROJECT_RIDGE_LIB_METRICS_HPP
