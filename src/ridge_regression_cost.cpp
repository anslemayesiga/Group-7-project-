#include "Group-7-project-ridge-lib/ridge_cost.hpp"

#include <cmath>
#include <stdexcept>

namespace ridge_ml {

double ridge_cost(
    const Vector& actual,
    const Vector& predicted,
    const Vector& theta,
    double lambda
) {
    if (actual.empty() || predicted.size() != actual.size() || theta.empty()) {
        throw std::invalid_argument("Ridge cost requires matching non-empty data and parameters");
    }
    if (!std::isfinite(lambda) || lambda < 0.0) {
        throw std::invalid_argument("Ridge regularization strength must be finite and non-negative");
    }

    double squared_error = 0.0;
    for (std::size_t i = 0; i < actual.size(); ++i) {
        if (!std::isfinite(actual[i]) || !std::isfinite(predicted[i])) {
            throw std::invalid_argument("Ridge cost inputs must be finite");
        }
        const double error = predicted[i] - actual[i];
        squared_error += error * error;
    }

    double penalty = 0.0;
    for (std::size_t j = 1; j < theta.size(); ++j) {
        if (!std::isfinite(theta[j])) {
            throw std::invalid_argument("Ridge parameters must be finite");
        }
        penalty += theta[j] * theta[j];
    }
    if (!std::isfinite(theta[0])) {
        throw std::invalid_argument("Ridge parameters must be finite");
    }

    const double sample_count = static_cast<double>(actual.size());
    return squared_error / (2.0 * sample_count)
        + lambda * penalty / (2.0 * sample_count);
}

} // namespace ridge_ml
