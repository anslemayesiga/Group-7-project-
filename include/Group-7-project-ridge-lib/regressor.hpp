#ifndef GROUP_7_PROJECT_RIDGE_LIB_REGRESSOR_HPP
#define GROUP_7_PROJECT_RIDGE_LIB_REGRESSOR_HPP

#include "Group-7-project-ridge-lib/matrix.hpp"

namespace ridge_ml {

// Shared fit/predict interface for interchangeable regression models.
class Regressor {
public:
    virtual ~Regressor() = default;
    virtual void fit(const Matrix& features, const Vector& targets) = 0;
    virtual Vector predict(const Matrix& features) const = 0;
};

} // namespace ridge_ml

#endif // GROUP_7_PROJECT_RIDGE_LIB_REGRESSOR_HPP
