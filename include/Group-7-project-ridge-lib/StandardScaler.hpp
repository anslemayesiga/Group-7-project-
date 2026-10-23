#ifndef RIDGELIB_STANDARD_SCALER_HPP
#define RIDGELIB_STANDARD_SCALER_HPP

#include <vector>

namespace ridge_ml {
class StandardScaler {
public:
    void fit(const std::vector<double>& values);
    std::vector<double> transform(const std::vector<double>& values) const;
    std::vector<double> fit_transform(const std::vector<double>& values);
    double mean() const;
    double scale() const;
private:
    double mean_ = 0.0;
    double scale_ = 1.0;
    bool fitted_ = false;
};
}
#endif
