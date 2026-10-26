#include "Group-7-project-ridge-lib/ridge_regression.hpp"
#include "Group-7-project-ridge-lib/ridge_cost.hpp"
#include <cassert>
#include <cmath>
#include <stdexcept>
// Check ridge fitting, unpenalized intercept cost, and model input validation.
int main() {
    using namespace ridge_ml;

    // Train on a simple linear relationship using a small positive penalty.
    const Matrix features(4, 1, {1, 2, 3, 4});
    const Vector targets{3, 5, 7, 9};
    RidgeRegression model(0.01);

    // Prediction is only valid after the model has been fitted.
    bool rejected = false;
    try {
        (void)model.predict(features);
    } catch (const std::logic_error&) {
        rejected = true;
    }
    assert(rejected);

    // Fit and check predictions, stored lambda, and the ridge cost formula.
    model.fit(features, targets);
    const Vector predictions = model.predict(features);
    assert(predictions.size() == 4);
    assert(std::abs(predictions[0] - 3) < 0.1);
    assert(model.lambda() == 0.01);
    assert(std::abs(ridge_cost({1, 2}, {1, 2}, {0, 1}, 1) - 0.25) < 1e-12);

    // Negative regularization is not a valid model configuration.
    rejected = false;
    try {
        const RidgeRegression invalid(-1);
        (void)invalid;
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);

    // Prediction features must have the same number of columns used in fit().
    rejected = false;
    try {
        (void)model.predict(Matrix(2, 2));
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);

    // Ridge cost also rejects negative lambda values.
    rejected = false;
    try {
        (void)ridge_cost({1}, {1}, {0}, -1);
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);
}
