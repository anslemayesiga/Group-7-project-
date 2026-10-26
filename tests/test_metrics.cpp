#include "Group-7-project-ridge-lib/metrics.hpp"
#include <cassert>
#include <cmath>
#include <limits>
#include <stdexcept>

// Verify the regression score formulas and reject empty or non-finite inputs.
int main() {
    using ridge_ml::RegressionMetrics;
    // Use a small example with residuals 1, 0, and 1 for hand-checkable scores.
    const ridge_ml::Vector actual{1.0, 2.0, 3.0};
    const ridge_ml::Vector predicted{2.0, 2.0, 4.0};
    // Compare each metric with its expected arithmetic result.
    assert(std::abs(RegressionMetrics::mean_absolute_error(actual, predicted) - 2.0 / 3.0) < 1e-12);
    assert(std::abs(RegressionMetrics::mean_squared_error(actual, predicted) - 2.0 / 3.0) < 1e-12);
    assert(std::abs(RegressionMetrics::root_mean_squared_error(actual, predicted) - std::sqrt(2.0 / 3.0)) < 1e-12);
    assert(std::abs(RegressionMetrics::r_squared(actual, actual) - 1.0) < 1e-12);
    const ridge_ml::Vector constant{2.0, 2.0};
    // Constant targets follow the documented exact-prediction convention.
    assert(RegressionMetrics::r_squared(constant, constant) == 1.0);
    bool rejected = false;
    // Empty vectors and non-finite values are invalid metric inputs.
    try { (void)RegressionMetrics::mean_squared_error({}, {}); }
    catch (const std::invalid_argument&) { rejected = true; }
    assert(rejected);
    rejected = false;
    try { (void)RegressionMetrics::mean_absolute_error({1.0}, {std::numeric_limits<double>::infinity()}); }
    catch (const std::invalid_argument&) { rejected = true; }
    assert(rejected);
}
