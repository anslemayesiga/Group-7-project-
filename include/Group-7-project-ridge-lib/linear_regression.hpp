#ifndef GROUP_7_PROJECT_RIDGE_LIB_LINEAR_REGRESSION_HPP
#define GROUP_7_PROJECT_RIDGE_LIB_LINEAR_REGRESSION_HPP

#include "Group-7-project-ridge-lib/regressor.hpp"

namespace ridge_ml {

class LinearRegression final : public Regressor {
public:
    void fit(const Matrix& features, const Vector& targets) override;
    Vector predict(const Matrix& features) const override;
    const Vector& coefficients() const;

private:
    Vector coefficients_; // coefficient 0 is the intercept
    bool fitted_ = false;
};

} // namespace ridge_ml

#endif // GROUP_7_PROJECT_RIDGE_LIB_LINEAR_REGRESSION_HPP
