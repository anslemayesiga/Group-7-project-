#include "scalerlib/MinMaxScaler.hpp"
#include <stdexcept>
#include <algorithm>

void MinMaxScaler::fit(const std::vector<double>& data) {
    if (data.empty()) {
        throw std::invalid_argument("Cannot fit an empty dataset.");
    }
    
    auto result = std::minmax_element(data.begin(), data.end());
    min_val = *result.first;
    max_val = *result.second;
    is_fitted = true;
}

std::vector<double> MinMaxScaler::transform(const std::vector<double>& data) const {
    if (!is_fitted) {
        throw std::runtime_error("Scaler must be fitted before transforming data.");
    }
    if (data.empty()) {
        return {};
    }

    std::vector<double> scaled_data;
    scaled_data.reserve(data.size());

    // Handle Edge Case requirement: Zero Variance (Prevents Division by Zero)
    double range = max_val - min_val;
    if (range == 0.0) {
        for (size_t i = 0; i < data.size(); ++i) {
            scaled_data.push_back(0.0);
        }
        return scaled_data;
    }

    for (double val : data) {
        double scaled = (val - min_val) / range;
        scaled_data.push_back(scaled);
    }

    return scaled_data;
}

std::vector<double> MinMaxScaler::fit_transform(const std::vector<double>& data) {
    fit(data);
    return transform(data);
}
