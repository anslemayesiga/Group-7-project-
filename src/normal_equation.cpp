#include "Group-7-project-ridge-lib/normal_equation.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace ridge_ml {

Vector gaussian_solve(const Matrix& matrix, const Vector& right_hand_side) {
    if (matrix.rows() == 0 || matrix.rows() != matrix.cols()) {
        throw std::invalid_argument("Gaussian solve requires a non-empty square matrix");
    }
    if (matrix.rows() != right_hand_side.size()) {
        throw std::invalid_argument("Gaussian solve right-hand side size mismatch");
    }

    const std::size_t size = matrix.rows();
    Matrix augmented(size, size + 1);
    double matrix_scale = 0.0;

    for (std::size_t i = 0; i < size; ++i) {
        if (!std::isfinite(right_hand_side[i])) {
            throw std::invalid_argument("Gaussian solve inputs must be finite");
        }
        for (std::size_t j = 0; j < size; ++j) {
            const double value = matrix(i, j);
            if (!std::isfinite(value)) {
                throw std::invalid_argument("Gaussian solve inputs must be finite");
            }
            augmented(i, j) = value;
            matrix_scale = std::max(matrix_scale, std::abs(value));
        }
        augmented(i, size) = right_hand_side[i];
    }

    const double tolerance = std::numeric_limits<double>::epsilon()
        * std::max(matrix_scale, std::numeric_limits<double>::min())
        * static_cast<double>(size) * 16.0;

    for (std::size_t pivot = 0; pivot < size; ++pivot) {
        std::size_t pivot_row = pivot;
        double pivot_magnitude = std::abs(augmented(pivot, pivot));
        for (std::size_t row = pivot + 1; row < size; ++row) {
            const double candidate = std::abs(augmented(row, pivot));
            if (candidate > pivot_magnitude) {
                pivot_magnitude = candidate;
                pivot_row = row;
            }
        }
        if (pivot_magnitude <= tolerance) {
            throw std::runtime_error("Gaussian solve encountered a singular matrix");
        }

        if (pivot_row != pivot) {
            for (std::size_t col = 0; col <= size; ++col) {
                std::swap(augmented(pivot, col), augmented(pivot_row, col));
            }
        }

        for (std::size_t row = pivot + 1; row < size; ++row) {
            const double factor = augmented(row, pivot) / augmented(pivot, pivot);
            augmented(row, pivot) = 0.0;
            for (std::size_t col = pivot + 1; col <= size; ++col) {
                augmented(row, col) -= factor * augmented(pivot, col);
            }
        }
    }

    Vector solution(size, 0.0);
    for (std::size_t reverse = size; reverse-- > 0;) {
        double value = augmented(reverse, size);
        for (std::size_t col = reverse + 1; col < size; ++col) {
            value -= augmented(reverse, col) * solution[col];
        }
        const double diagonal = augmented(reverse, reverse);
        if (std::abs(diagonal) <= tolerance) {
            throw std::runtime_error("Gaussian solve encountered a singular matrix");
        }
        solution[reverse] = value / diagonal;
    }
    return solution;
}

Vector fit_normal_equation(const Matrix& features, const Vector& targets) {
    if (features.rows() == 0 || features.cols() == 0) {
        throw std::invalid_argument("Normal equation requires non-empty features");
    }
    if (features.rows() != targets.size()) {
        throw std::invalid_argument("Feature and target row counts must match");
    }

    const Matrix transpose = features.transpose();
    const Matrix gram = transpose * features;
    const Vector projected_targets = transpose.multiply(targets);
    return gaussian_solve(gram, projected_targets);
}

} // namespace ridge_ml
