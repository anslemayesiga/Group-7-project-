#include "Group-7-project-ridge-lib/ridge_regression.hpp"

#include "Group-7-project-ridge-lib/normal_equation.hpp"

#include <cmath>
#include <stdexcept>

namespace ridge_ml {
namespace {
Matrix add_intercept(const Matrix& features) {
    if (features.rows() == 0 || features.cols() == 0) {
        throw std::invalid_argument("Ridge regression requires non-empty features");
    }
    Matrix design(features.rows(), features.cols() + 1, 1.0);
    for (std::size_t row = 0; row < features.rows(); ++row) {
        for (std::size_t col = 0; col < features.cols(); ++col) {
            design(row, col + 1) = features(row, col);
        }
    }
    return design;
}
} // namespace

RidgeRegression::RidgeRegression(double lambda) : lambda_(lambda) {
    if (!std::isfinite(lambda_) || lambda_ < 0.0) {
        throw std::invalid_argument("Ridge lambda must be finite and non-negative");
    }
}

void RidgeRegression::fit(const Matrix& features, const Vector& targets) {
    if (features.rows() != targets.size()) {
        throw std::invalid_argument("Feature rows and target count must match");
    }
    const Matrix design = add_intercept(features);
    Matrix gram = design.transpose() * design;
    for (std::size_t i = 1; i < gram.rows(); ++i) {
        gram(i, i) += lambda_;
    }
    const Vector rhs = design.transpose().multiply(targets);
    coefficients_ = gaussian_solve(gram, rhs);
    fitted_ = true;
}

Vector RidgeRegression::predict(const Matrix& features) const {
    if (!fitted_) {
        throw std::logic_error("RidgeRegression must be fitted before prediction");
    }
    if (features.cols() + 1 != coefficients_.size()) {
        throw std::invalid_argument("Feature count does not match fitted model");
    }
    Vector result(features.rows(), coefficients_[0]);
    for (std::size_t row = 0; row < features.rows(); ++row) {
        for (std::size_t col = 0; col < features.cols(); ++col) {
            result[row] += features(row, col) * coefficients_[col + 1];
        }
    }
    return result;
}

const Vector& RidgeRegression::coefficients() const {
    if (!fitted_) {
        throw std::logic_error("RidgeRegression has no coefficients before fit");
    }
    return coefficients_;
}

double RidgeRegression::lambda() const noexcept { return lambda_; }

} // namespace ridge_ml
