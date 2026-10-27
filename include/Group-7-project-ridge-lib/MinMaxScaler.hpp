#ifndef SCALERLIB_MIN_MAX_SCALER_HPP
#define SCALERLIB_MIN_MAX_SCALER_HPP

#include <vector>

namespace ridge_ml {

// Scale one feature vector into the [0, 1] range learned during fit().
class MinMaxScaler {
public:
    // Store the minimum and maximum from training values.
    void fit(const std::vector<double>& data);
    // Apply the stored range to new values without refitting.
    std::vector<double> transform(const std::vector<double>& data) const;
    // Fit once and transform the training values with the fitted range.
    std::vector<double> fit_transform(const std::vector<double>& data);

private:
    double min_value_ = 0.0;
    double max_value_ = 0.0;
    bool fitted_ = false;
};

} // namespace ridge_ml

#endif // SCALERLIB_MIN_MAX_SCALER_HPP
