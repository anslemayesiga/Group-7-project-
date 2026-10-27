#ifndef RIDGE_ML_RIDGE_COST_FUNCTION_HPP
#define RIDGE_ML_RIDGE_COST_FUNCTION_HPP

#include "Group-7-project-ridge-lib/matrix.hpp"
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
    Vector coefficients_;
    bool fitted_ = false;
};

// Return squared-error cost plus an L2 penalty; theta[0] is the unpenalized
// intercept and all later parameters are treated as feature coefficients.
// actual and predicted must have equal non-zero lengths; lambda must be non-negative.
double ridge_cost(
    const Vector& actual,
    const Vector& predicted,
    const Vector& theta,
    double lambda
);

} // namespace ridge_ml

#endif // RIDGE_ML_RIDGE_COST_FUNCTION_HPP
