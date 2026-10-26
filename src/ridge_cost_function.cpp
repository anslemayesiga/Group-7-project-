#include "Group-7-project-ridge-lib/ridge_cost_function.hpp"

#include "Group-7-project-ridge-lib/normal_equation.hpp"

#include <cmath>
#include <stdexcept>

namespace ridge_ml {
namespace {
// The intercept is placed first so the solver can leave it unpenalized.
Matrix add_intercept(const Matrix& features) {
    if (features.rows() == 0 || features.cols() == 0) {
        throw std::invalid_argument("Ridge regression requires non-empty features");
    }
    Matrix design(features.rows(), features.cols() + 1, 1.0);
    // Keep a leading column of ones for the model bias.
    for (std::size_t row = 0; row < features.rows(); ++row) {
        for (std::size_t col = 0; col < features.cols(); ++col) {
            design(row, col + 1) = features(row, col);
        }
    }
    return design;
}
} // namespace

RidgeRegression::RidgeRegression(double lambda) : lambda_(lambda) {
    // Validate the regularization strength once when the model is configured.
    if (!std::isfinite(lambda_) || lambda_ < 0.0) {
        throw std::invalid_argument("Ridge lambda must be finite and non-negative");
    }
}

void RidgeRegression::fit(const Matrix& features, const Vector& targets) {
    // Each feature row must have one corresponding target value.
    if (features.rows() != targets.size()) {
        throw std::invalid_argument("Feature rows and target count must match");
    }
    // Add bias, then compute the normal-equation matrix and right-hand side.
    const Matrix design = add_intercept(features);
    Matrix gram = design.transpose() * design;
    // Start at column one to exclude the intercept from the L2 penalty.
    for (std::size_t i = 1; i < gram.rows(); ++i) {
        gram(i, i) += lambda_;
    }
    // Solve the regularized system and replace coefficients only on success.
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
    // Start with the bias term, then add each weighted feature.
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

double ridge_cost(
    const Vector& actual,
    const Vector& predicted,
    const Vector& theta,
    double lambda
) {
    // Check vector shapes and lambda before calculating the objective.
    if (actual.empty() || predicted.size() != actual.size() || theta.empty()) {
        throw std::invalid_argument("Ridge cost requires matching non-empty data and parameters");
    }
    if (!std::isfinite(lambda) || lambda < 0.0) {
        throw std::invalid_argument("Ridge regularization strength must be finite and non-negative");
    }

    // The residual term measures prediction error over all observations.
    double squared_error = 0.0;
    for (std::size_t i = 0; i < actual.size(); ++i) {
        if (!std::isfinite(actual[i]) || !std::isfinite(predicted[i])) {
            throw std::invalid_argument("Ridge cost inputs must be finite");
        }
        const double error = predicted[i] - actual[i];
        squared_error += error * error;
    }

    // The regularization term shrinks feature coefficients, not the intercept.
    double penalty = 0.0;
    for (std::size_t j = 1; j < theta.size(); ++j) {
        if (!std::isfinite(theta[j])) {
            throw std::invalid_argument("Ridge parameters must be finite");
        }
        penalty += theta[j] * theta[j];
    }
    if (!std::isfinite(theta[0])) {
        throw std::invalid_argument("Ridge parameters must be finite");
    }

    // Divide both terms by 2m, matching the gradient-descent objective.
    const double sample_count = static_cast<double>(actual.size());
    return squared_error / (2.0 * sample_count)
        + lambda * penalty / (2.0 * sample_count);
}

} // namespace ridge_ml
