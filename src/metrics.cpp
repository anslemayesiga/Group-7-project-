#include "Group-7-project-ridge-lib/metrics.hpp"

#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace ridge_ml {
namespace {
void validate_pair(const Vector& actual, const Vector& predicted) {
    // All score functions share the same input requirements.
    if (actual.empty() || actual.size() != predicted.size()) {
        throw std::invalid_argument("Metric vectors must have equal non-zero length");
    }
    for (std::size_t i = 0; i < actual.size(); ++i) {
        if (!std::isfinite(actual[i]) || !std::isfinite(predicted[i])) {
            throw std::invalid_argument("Metric values must be finite");
        }
    }
}
} // namespace

double RegressionMetrics::mean_absolute_error(const Vector& actual, const Vector& predicted) {
    validate_pair(actual, predicted);
    double total = 0.0;
    // Sum absolute residuals, then divide by the number of samples.
    for (std::size_t i = 0; i < actual.size(); ++i) total += std::abs(actual[i] - predicted[i]);
    return total / static_cast<double>(actual.size());
}

double RegressionMetrics::mean_squared_error(const Vector& actual, const Vector& predicted) {
    validate_pair(actual, predicted);
    double total = 0.0;
    // Squaring gives larger errors greater influence than MAE.
    for (std::size_t i = 0; i < actual.size(); ++i) {
        const double error = actual[i] - predicted[i];
        total += error * error;
    }
    return total / static_cast<double>(actual.size());
}

double RegressionMetrics::root_mean_squared_error(const Vector& actual, const Vector& predicted) {
    // RMSE uses the MSE calculation and returns the error in target units.
    return std::sqrt(mean_squared_error(actual, predicted));
}

double RegressionMetrics::r_squared(const Vector& actual, const Vector& predicted) {
    validate_pair(actual, predicted);
    // Compare residual variation with variation around the actual target mean.
    double mean = 0.0;
    for (double value : actual) mean += value;
    mean /= static_cast<double>(actual.size());
    double residual_sum = 0.0;
    double total_sum = 0.0;
    for (std::size_t i = 0; i < actual.size(); ++i) {
        const double residual = actual[i] - predicted[i];
        const double centered = actual[i] - mean;
        residual_sum += residual * residual;
        total_sum += centered * centered;
    }
    // A constant target has no variance, so use the documented exact-fit convention.
    if (total_sum == 0.0) {
        return residual_sum == 0.0 ? 1.0 : 0.0;
    }
    return 1.0 - residual_sum / total_sum;
}

} // namespace ridge_ml
