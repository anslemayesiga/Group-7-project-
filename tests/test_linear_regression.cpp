#include "Group-7-project-ridge-lib/linear_regression.hpp"

// Check that fitting learns the expected line and prediction requires a fit.
#include <cassert>
#include <cmath>
#include <stdexcept>

int main() {
    using namespace ridge_ml;

    // These points lie exactly on y = 1 + 2x.
    const Matrix features(3, 1, {1, 2, 3});
    const Vector targets{3, 5, 7};
    LinearRegression model;

    // Prediction before training should report a logic error.
    bool rejected = false;
    try {
        (void)model.predict(features);
    } catch (const std::logic_error&) {
        rejected = true;
    }
    assert(rejected);

    // Fit the line and check one prediction and the intercept-plus-slope result.
    model.fit(features, targets);
    const Vector predictions = model.predict(features);
    assert(std::abs(predictions[1] - 5) < 1e-8);
    assert(model.coefficients().size() == 2);
}
