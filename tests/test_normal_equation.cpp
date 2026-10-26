#include "Group-7-project-ridge-lib/normal_equation.hpp"
#include <cassert>
#include <cmath>
#include <stdexcept>

// Check pivoting, least-squares coefficients, and singular or invalid systems.
int main() {
    using namespace ridge_ml;

    // The first matrix needs a row swap to find a nonzero first pivot.
    const Matrix system(2, 2, {0, 1, 1, 1});
    const Vector solution = gaussian_solve(system, {2, 3});
    assert(std::abs(solution[0] - 1) < 1e-10);
    assert(std::abs(solution[1] - 2) < 1e-10);

    // Fit a line from a design matrix whose first column is the intercept.
    const Matrix design(3, 2, {1, 1, 1, 2, 1, 3});
    const Vector coefficients = fit_normal_equation(design, {5, 8, 11});
    assert(std::abs(coefficients[0] - 2) < 1e-9);
    assert(std::abs(coefficients[1] - 3) < 1e-9);

    // Feature rows and target values must have matching counts.
    bool rejected = false;
    try {
        (void)fit_normal_equation(Matrix(2, 1), {1});
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);

    // A singular coefficient matrix cannot produce a unique solution.
    rejected = false;
    try {
        (void)gaussian_solve(Matrix(2, 2, {1, 2, 2, 4}), {3, 6});
    } catch (const std::runtime_error&) {
        rejected = true;
    }
    assert(rejected);

    // The linear solver requires a square matrix.
    rejected = false;
    try {
        (void)gaussian_solve(Matrix(2, 1), {1, 2});
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);
}
