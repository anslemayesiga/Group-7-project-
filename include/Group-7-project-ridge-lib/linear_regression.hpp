#ifndef GROUP_7_PROJECT_RIDGE_LIB_LINEAR_REGRESSION_HPP
#define GROUP_7_PROJECT_RIDGE_LIB_LINEAR_REGRESSION_HPP

#include "Group-7-project-ridge-lib/regressor.hpp"

namespace ridge_ml {

// Ordinary least-squares regression with an automatically added intercept.
class LinearRegression final : public Regressor {
public:
    // Estimate coefficients from features and their matching target values.
    void fit(const Matrix& features, const Vector& targets) override;
    // Predict one target for every supplied feature row.
    Vector predict(const Matrix& features) const override;
    // Coefficient zero is the intercept; remaining coefficients match features.
    const Vector& coefficients() const;

private:
    Vector coefficients_; // coefficient 0 is the intercept
    bool fitted_ = false;
};

} // namespace ridge_ml

#endif // GROUP_7_PROJECT_RIDGE_LIB_LINEAR_REGRESSION_HPP
