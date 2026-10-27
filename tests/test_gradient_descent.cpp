#include "Group-7-project-ridge-lib/gradient_descent.hpp"

// Check convergence, early stopping, and rejection of invalid training inputs.
#include <cassert>
#include <cmath>
#include <limits>
#include <stdexcept>

int main() {
    using namespace ridge_ml;

    // Use a one-column design and constant targets for an easy-to-check fit.
    const Matrix design(3, 1, {1, 1, 1});
    const Vector targets{2, 2, 2};
    const GradientDescent optimizer(0.1, 200);
    const auto result = optimizer.fit(design, targets);

    // Confirm the parameter approaches the target and the recorded cost falls.
    assert(result.parameters.size() == 1);
    assert(std::abs(result.parameters[0] - 2) < 1e-5);
    assert(result.cost_history.size() == 200);
    assert(result.cost_history.back() < result.cost_history.front());

    // A nonzero tolerance should stop once successive costs barely change.
    const GradientDescent early_stopping(0.1, 500, 0, 1e-8);
    const auto early_result = early_stopping.fit(design, targets);
    assert(early_result.converged);
    assert(early_result.iterations_run < 500);

    // Mismatched target count must be rejected before optimization starts.
    bool rejected = false;
    try {
        (void)optimizer.fit(design, {1, 2});
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);

    // A learning rate of zero is invalid configuration.
    rejected = false;
    try {
        const GradientDescent invalid(0, 1);
        (void)invalid;
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);

    // Initial parameters must have one entry per design-matrix column.
    rejected = false;
    try {
        (void)optimizer.fit(design, targets, {1, 2});
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);

    // Non-finite initial values are rejected rather than poisoning the fit.
    rejected = false;
    try {
        (void)optimizer.fit(design, targets,
                            {std::numeric_limits<double>::quiet_NaN()});
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);
}
