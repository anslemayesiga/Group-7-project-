#include "Group-7-project-ridge-lib/MinMaxScaler.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace ridge_ml {

void MinMaxScaler::fit(const std::vector<double>& data) {
    // Validate before using standard algorithms to find the range.
    if (data.empty()) {
        throw std::invalid_argument("Cannot fit a scaler to empty data");
    }
    for (double value : data) {
        if (!std::isfinite(value)) {
            throw std::invalid_argument("Scaler data must contain only finite values");
        }
    }

    const auto bounds = std::minmax_element(data.begin(), data.end());
    // Save the training range so later data uses the same transformation.
    min_value_ = *bounds.first;
    max_value_ = *bounds.second;
    fitted_ = true;
}

std::vector<double> MinMaxScaler::transform(const std::vector<double>& data) const {
    if (!fitted_) {
        throw std::logic_error("Scaler must be fitted before transform");
    }

    // Allocate the output once, then transform each input using fitted bounds.
    std::vector<double> result;
    result.reserve(data.size());
    const double range = max_value_ - min_value_;
    for (double value : data) {
        if (!std::isfinite(value)) {
            throw std::invalid_argument("Scaler data must contain only finite values");
        }
        // A constant training feature maps to zero rather than dividing by zero.
        result.push_back(range == 0.0 ? 0.0 : (value - min_value_) / range);
    }
    return result;
}

std::vector<double> MinMaxScaler::fit_transform(const std::vector<double>& data) {
    // Fit on these values first, then apply the learned range to the same data.
    fit(data);
    return transform(data);
}

} // namespace ridge_ml
