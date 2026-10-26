#include "Group-7-project-ridge-lib/StandardScaler.hpp"
#include <cmath>
#include <stdexcept>

namespace ridge_ml {
void StandardScaler::fit(const std::vector<double>& values) {
    // Validate the complete training vector before computing its statistics.
    if (values.empty()) throw std::invalid_argument("Cannot fit scaler to empty data");
    for (double value : values) if (!std::isfinite(value)) throw std::invalid_argument("Scaler values must be finite");
    mean_ = 0.0;
    // Add each value's share to avoid a separate sum that could overflow sooner.
    for (double value : values) mean_ += value / static_cast<double>(values.size());
    // Use population variance because the input values are the full fit dataset.
    double variance = 0.0;
    // Measure average squared distance from the mean (population variance).
    for (double value : values) { const double delta = value - mean_; variance += delta * delta / static_cast<double>(values.size()); }
    scale_ = std::sqrt(variance);
    // Use a unit divisor for constant features so transformed values stay finite.
    if (scale_ == 0.0) scale_ = 1.0;
    fitted_ = true;
}
std::vector<double> StandardScaler::transform(const std::vector<double>& values) const {
    if (!fitted_) throw std::logic_error("Scaler must be fitted before transform");
    // Reuse stored training statistics to transform this vector consistently.
    std::vector<double> result; result.reserve(values.size());
    for (double value : values) {
        if (!std::isfinite(value)) throw std::invalid_argument("Scaler values must be finite");
        result.push_back((value - mean_) / scale_);
    }
    return result;
}
// Convenience path for fitting and transforming the same training vector.
std::vector<double> StandardScaler::fit_transform(const std::vector<double>& values) { fit(values); return transform(values); }
// Expose learned statistics only after fit() has successfully completed.
double StandardScaler::mean() const { if (!fitted_) throw std::logic_error("Scaler is not fitted"); return mean_; }
double StandardScaler::scale() const { if (!fitted_) throw std::logic_error("Scaler is not fitted"); return scale_; }
}
