#include "Group-7-project-ridge-lib/tuning.hpp"
#include "Group-7-project-ridge-lib/ridge_cost_function.hpp"
#include "Group-7-project-ridge-lib/metrics.hpp"
#include <cassert>
#include <memory>

// Check candidate selection, retained fitted model, and tuner error handling.
int main() {
    using namespace ridge_ml;

    // Build one ridge model per candidate regularization strength.
    const GridSearchTuner tuner([](double lambda) {
        return std::make_unique<RidgeRegression>(lambda);
    });
    const Matrix features(4, 1, {1, 2, 3, 4});
    const Vector targets{3, 5, 7, 9};

    // With matching training and validation data, zero penalty should fit best.
    const auto result = tuner.fit(features, targets, features, targets, {0.0, 0.1, 1.0});
    assert(result.best_model);
    assert(result.best_parameter == 0.0);
    const Vector predictions = result.best_model->predict(features);
    assert(RegressionMetrics::mean_squared_error(targets, predictions) < 1e-10);

    // Validation rows and target values must have matching counts.
    bool rejected = false;
    try {
        (void)tuner.fit(features, targets, features, {3}, {0.1});
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);

    // At least one candidate value is required for a search.
    rejected = false;
    try {
        (void)tuner.fit(features, targets, features, targets, {});
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);

    // A factory that returns no model must produce an explicit error.
    const GridSearchTuner null_factory([](double) -> std::unique_ptr<Regressor> {
        return {};
    });
    rejected = false;
    try {
        (void)null_factory.fit(features, targets, features, targets, {1});
    } catch (const std::runtime_error&) {
        rejected = true;
    }
    assert(rejected);
}
