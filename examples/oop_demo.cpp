#include "Group-7-project-ridge-lib/linear_regression.hpp"
#include "Group-7-project-ridge-lib/metrics.hpp"
#include "Group-7-project-ridge-lib/ridge_cost_function.hpp"
#include "Group-7-project-ridge-lib/tuning.hpp"

#include <iostream>
#include <memory>
#include <vector>

int main() {
    // Both estimators share the Regressor interface and can be handled uniformly.
    const ridge_ml::Matrix features(4, 1, std::vector<double>{1.0, 2.0, 3.0, 4.0});
    const ridge_ml::Vector targets{3.0, 5.0, 7.0, 9.0};

    // Build a small training set for y = 1 + 2x.
    std::vector<std::unique_ptr<ridge_ml::Regressor>> models;
    models.push_back(std::make_unique<ridge_ml::LinearRegression>());
    models.push_back(std::make_unique<ridge_ml::RidgeRegression>(0.1));

    // Train and score every model through the shared interface.
    for (auto& model : models) {
        model->fit(features, targets);
        const ridge_ml::Vector predictions = model->predict(features);
        std::cout << "R-squared: "
                  << ridge_ml::RegressionMetrics::r_squared(targets, predictions) << '\n';
    }

    // Let grid search create a fresh ridge model for each lambda candidate.
    const ridge_ml::GridSearchTuner tuner([](double lambda) {
        return std::make_unique<ridge_ml::RidgeRegression>(lambda);
    });
    const auto result = tuner.fit(features, targets, features, targets,
                                  std::vector<double>{0.0, 0.1, 1.0});
    // Report the selected parameter and its validation score.
    std::cout << "Best lambda: " << result.best_parameter
              << ", validation R-squared: " << result.best_score << '\n';
}
