#ifndef RIDGELIB_STANDARD_SCALER_HPP
#define RIDGELIB_STANDARD_SCALER_HPP

#include <vector>

namespace ridge_ml {

// Center one feature vector and scale it using its fitted mean and deviation.
class StandardScaler {
public:
    // Learn population mean and standard deviation from training values.
    void fit(const std::vector<double>& values);
    // Apply the stored statistics to new values.
    std::vector<double> transform(const std::vector<double>& values) const;
    // Fit and transform the same vector in one call.
    std::vector<double> fit_transform(const std::vector<double>& values);
    // Return the training statistics; both require a prior fit().
    double mean() const;
    double scale() const;
private:
    double mean_ = 0.0;
    double scale_ = 1.0;
    bool fitted_ = false;
};
}
#endif
