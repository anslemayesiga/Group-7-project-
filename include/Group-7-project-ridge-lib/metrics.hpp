#ifndef GROUP_7_PROJECT_RIDGE_LIB_METRICS_HPP
#define GROUP_7_PROJECT_RIDGE_LIB_METRICS_HPP

#include "Group-7-project-ridge-lib/matrix.hpp"

namespace ridge_ml {

class RegressionMetrics {
public:
    static double mean_absolute_error(const Vector& actual, const Vector& predicted);
    static double mean_squared_error(const Vector& actual, const Vector& predicted);
    static double root_mean_squared_error(const Vector& actual, const Vector& predicted);
    static double r_squared(const Vector& actual, const Vector& predicted);
};

} // namespace ridge_ml

#endif // GROUP_7_PROJECT_RIDGE_LIB_METRICS_HPP
