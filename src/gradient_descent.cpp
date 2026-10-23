#include "Group-7-project-ridge-lib/gradient_descent.hpp"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace ridge_ml {

GradientDescent::GradientDescent(double learning_rate, std::size_t iterations, double lambda,
                                 double tolerance)
    : learning_rate_(learning_rate), iterations_(iterations), lambda_(lambda), tolerance_(tolerance) {
    if (!std::isfinite(learning_rate_) || learning_rate_ <= 0.0) {
        throw std::invalid_argument("Learning rate must be finite and positive");
    }
    if (!std::isfinite(lambda_) || lambda_ < 0.0) {
        throw std::invalid_argument("Lambda must be finite and non-negative");
    }
    if (!std::isfinite(tolerance_) || tolerance_ < 0.0) {
        throw std::invalid_argument("Tolerance must be finite and non-negative");
    }
}

GradientDescentResult GradientDescent::fit(const Matrix& design, const Vector& targets,
                                           Vector parameters) const {
    if (design.rows() == 0 || design.cols() == 0 || design.rows() != targets.size()) {
        throw std::invalid_argument("Design and targets must have matching non-empty rows");
    }
    for (double target : targets) {
        if (!std::isfinite(target)) throw std::invalid_argument("Targets must be finite");
    }
    for (std::size_t row = 0; row < design.rows(); ++row) {
        for (std::size_t col = 0; col < design.cols(); ++col) {
            if (!std::isfinite(design(row, col))) throw std::invalid_argument("Design values must be finite");
        }
    }
    if (parameters.empty()) {
        parameters.assign(design.cols(), 0.0);
    }
    if (parameters.size() != design.cols()) {
        throw std::invalid_argument("Initial parameter count must match design columns");
    }
    for (double parameter : parameters) {
        if (!std::isfinite(parameter)) throw std::invalid_argument("Initial parameters must be finite");
    }

    GradientDescentResult result;
    const double sample_count = static_cast<double>(design.rows());
    result.cost_history.reserve(iterations_);
    for (std::size_t iteration = 0; iteration < iterations_; ++iteration) {
        Vector predictions = design.multiply(parameters);
        Vector gradient(parameters.size(), 0.0);
        double squared_error = 0.0;
        for (std::size_t row = 0; row < design.rows(); ++row) {
            const double error = predictions[row] - targets[row];
            squared_error += error * error;
            for (std::size_t col = 0; col < design.cols(); ++col) {
                gradient[col] += error * design(row, col);
            }
        }
        double penalty = 0.0;
        for (std::size_t col = 0; col < parameters.size(); ++col) {
            gradient[col] /= sample_count;
            if (col != 0) {
                gradient[col] += lambda_ * parameters[col] / sample_count;
                penalty += parameters[col] * parameters[col];
            }
        }
        const double cost = (squared_error + lambda_ * penalty) / (2.0 * sample_count);
        result.cost_history.push_back(cost);
        result.iterations_run = iteration + 1;
        if (tolerance_ > 0.0 && result.cost_history.size() > 1 &&
            std::abs(result.cost_history[result.cost_history.size() - 2] - cost) <= tolerance_) {
            result.converged = true;
            break;
        }
        for (std::size_t col = 0; col < parameters.size(); ++col) {
            parameters[col] -= learning_rate_ * gradient[col];
        }
    }
    result.parameters = std::move(parameters);
    return result;
}

} // namespace ridge_ml
