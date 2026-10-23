#ifndef SCALERLIB_MIN_MAX_SCALER_HPP
#define SCALERLIB_MIN_MAX_SCALER_HPP

#include <vector>

namespace ridge_ml {

class MinMaxScaler {
public:
    void fit(const std::vector<double>& data);
    std::vector<double> transform(const std::vector<double>& data) const;
    std::vector<double> fit_transform(const std::vector<double>& data);

private:
    double min_value_ = 0.0;
    double max_value_ = 0.0;
    bool fitted_ = false;
};

} // namespace ridge_ml

#endif // SCALERLIB_MIN_MAX_SCALER_HPP
