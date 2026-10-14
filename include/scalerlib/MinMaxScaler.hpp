#ifndef MIN_MAX_SCALER_HPP
#define MIN_MAX_SCALER_HPP

#include <vector>

class MinMaxScaler {
private:
    double min_val = 0.0;
    double max_val = 0.0;
    bool is_fitted = false;

public:
    MinMaxScaler() = default;

    // Computes the min and max of data
    void fit(const std::vector<double>& data);

    // Transforms data to a range between 0 and 1
    std::vector<double> transform(const std::vector<double>& data) const;

    // Combines fit and transform
    std::vector<double> fit_transform(const std::vector<double>& data);
};

#endif // MIN_MAX_SCALER_HPP
