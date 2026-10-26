#include "Group-7-project-ridge-lib/linear_regression.hpp"

#include "Group-7-project-ridge-lib/normal_equation.hpp"

#include <stdexcept>

namespace ridge_ml {
namespace {
// Keep the intercept in column zero so it matches the coefficient layout.
Matrix add_intercept(const Matrix& features) {
    if (features.rows() == 0 || features.cols() == 0) {
        throw std::invalid_argument("Linear regression requires non-empty features");
    }
    Matrix design(features.rows(), features.cols() + 1, 1.0);
    // The initialized first column contains ones; copy features after it.
    for (std::size_t row = 0; row < features.rows(); ++row) {
        for (std::size_t col = 0; col < features.cols(); ++col) {
            design(row, col + 1) = features(row, col);
        }
    }
    return design;
}
} // namespace

void LinearRegression::fit(const Matrix& features, const Vector& targets) {
    // One target is required for every feature row.
    if (features.rows() != targets.size()) {
        throw std::invalid_argument("Feature rows and target count must match");
    }
    // Solve ordinary least squares on the design matrix that includes bias.
    coefficients_ = fit_normal_equation(add_intercept(features), targets);
    // Mark fitted only after coefficient estimation succeeds.
    fitted_ = true;
}

Vector LinearRegression::predict(const Matrix& features) const {
    if (!fitted_) {
        throw std::logic_error("LinearRegression must be fitted before prediction");
    }
    if (features.cols() + 1 != coefficients_.size()) {
        throw std::invalid_argument("Feature count does not match fitted model");
    }
    // Begin each prediction with the fitted intercept.
    Vector result(features.rows(), coefficients_[0]);
    // Add each feature value multiplied by its learned coefficient.
    for (std::size_t row = 0; row < features.rows(); ++row) {
        for (std::size_t col = 0; col < features.cols(); ++col) {
            result[row] += features(row, col) * coefficients_[col + 1];
        }
    }
    return result;
}

const Vector& LinearRegression::coefficients() const {
    if (!fitted_) {
        throw std::logic_error("LinearRegression has no coefficients before fit");
    }
    return coefficients_;
}

} // namespace ridge_ml
