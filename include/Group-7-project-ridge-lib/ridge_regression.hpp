#ifndef GROUP_7_PROJECT_RIDGE_LIB_RIDGE_REGRESSION_HPP
#define GROUP_7_PROJECT_RIDGE_LIB_RIDGE_REGRESSION_HPP

#include "Group-7-project-ridge-lib/regressor.hpp"

namespace ridge_ml {

// Linear regression with L2 regularization applied to feature coefficients.
class RidgeRegression final : public Regressor {
public:
    // lambda must be finite and non-negative; the intercept is not penalized.
    explicit RidgeRegression(double lambda = 1.0);

    // Learn coefficients using the configured regularization strength.
    void fit(const Matrix& features, const Vector& targets) override;
    // Predict using the learned intercept and feature coefficients.
    Vector predict(const Matrix& features) const override;
    // Coefficient zero is the unpenalized intercept.
    const Vector& coefficients() const;
    double lambda() const noexcept;

private:
    double lambda_;
    Vector coefficients_; // coefficient 0 is the unpenalized intercept
    bool fitted_ = false;
};

} // namespace ridge_ml

#endif // GROUP_7_PROJECT_RIDGE_LIB_RIDGE_REGRESSION_HPP
