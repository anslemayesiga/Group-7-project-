#ifndef GROUP_7_PROJECT_RIDGE_LIB_RIDGE_REGRESSION_HPP
#define GROUP_7_PROJECT_RIDGE_LIB_RIDGE_REGRESSION_HPP

#include "Group-7-project-ridge-lib/regressor.hpp"

namespace ridge_ml {

class RidgeRegression final : public Regressor {
public:
    explicit RidgeRegression(double lambda = 1.0);

    void fit(const Matrix& features, const Vector& targets) override;
    Vector predict(const Matrix& features) const override;
    const Vector& coefficients() const;
    double lambda() const noexcept;

private:
    double lambda_;
    Vector coefficients_; // coefficient 0 is the unpenalized intercept
    bool fitted_ = false;
};

} // namespace ridge_ml

#endif // GROUP_7_PROJECT_RIDGE_LIB_RIDGE_REGRESSION_HPP
