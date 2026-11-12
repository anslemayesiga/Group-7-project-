#include "Group-7-project-ridge-lib/gradient_descent.hpp"

// Check convergence, early stopping, and rejection of invalid training inputs.
#include <cassert>
#include <cmath>//
#include <limits>// provides std::numeric_limits
#include <stdexcept> // provides std::invalid_argument


int main() {
    using namespace ridge_ml;

    // Use a one-column design and constant targets for an easy-to-check fit.
    const Matrix design(3, 1, {1, 1, 1});
    const Vector targets{2, 2, 2};
    const GradientDescent optimizer(0.1, 200);
    const auto result = optimizer.fit(design, targets);

    // Confirm the parameter approaches the target and the recorded cost falls.
    assert(result.parameters.size() == 1);// Checks that the model produces exactly one parameter because the design matrix has one column
    assert(std::abs(result.parameters[0] - 2) < 1e-5);
    assert(result.cost_history.size() == 200);
    assert(result.cost_history.back() < result.cost_history.front());// Checks that the final cost is lower than the initial cost, showing that training is improving.


    // A nonzero tolerance should stop once successive costs barely change.
    const GradientDescent early_stopping(0.1, 500, 0, 1e-8);// Creates another optimizer with learning rate 0.1, maximum 500 iterations, zero regularization strength, and a convergence tolerance of 0.00000001.
    const auto early_result = early_stopping.fit(design, targets);
    assert(early_result.converged);
    assert(early_result.iterations_run < 500);

    // Mismatched target count must be rejected before optimization starts.
    bool rejected = false;
    try {
        (void)optimizer.fit(design, {1, 2}); // Attempts to train using a matrix with 3 rows but only 2 target values; void ignores the returned result.
    } catch (const std::invalid_argument&) {// Catches an invalid_argument exception if the number of targets does not match the number of matrix rows.
        rejected = true; // Changes rejected to true to indicate that the invalid input was detected.
       
    }
    assert(rejected);

    // A learning rate of zero is invalid configuration.
    rejected = false;
    try {
        const GradientDescent invalid(0, 1);// Attempts to create an optimizer with a learning rate of zero and only one iteration.
        (void)invalid;
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);

    // Initial parameters must have one entry per design-matrix column.
    rejected = false;
    try {
        (void)optimizer.fit(design, targets, {1, 2});// Attempts to train with two initial parameters even though the design matrix has only one column.
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);

    // Non-finite initial values are rejected rather than poisoning the fit.
    rejected = false;
    try {
        (void)optimizer.fit(design, targets,
                            {std::numeric_limits<double>::quiet_NaN()});// Supplies NaN (Not a Number) as the initial parameter instead of a valid numerical value.
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);
}





