#include "Group-7-project-ridge-lib/tuning.hpp"

#include "Group-7-project-ridge-lib/metrics.hpp"

#include <stdexcept>
#include <utility>

namespace ridge_ml {

GridSearchTuner::GridSearchTuner(ModelFactory factory) : factory_(std::move(factory)) {
    // A factory is needed to construct a fresh model for each candidate.
    if (!factory_) {
        throw std::invalid_argument("GridSearchTuner requires a model factory");
    }
}

GridSearchResult GridSearchTuner::fit(const Matrix& training_features,
                                     const Vector& training_targets,
                                     const Matrix& validation_features,
                                     const Vector& validation_targets,
                                     const std::vector<double>& candidates) const {
    // Validate the search request before constructing candidate models.
    if (candidates.empty()) {
        throw std::invalid_argument("Grid search requires at least one candidate value");
    }
    if (validation_features.rows() != validation_targets.size()) {
        throw std::invalid_argument("Validation rows and targets must match");
    }

    GridSearchResult result;
    bool have_best = false;
    // Fit each candidate independently and keep the model with the highest validation R².
    for (double value : candidates) {
        // Each candidate gets an independent model to avoid carrying fit state forward.
        std::unique_ptr<Regressor> model = factory_(value);
        if (!model) {
            throw std::runtime_error("Model factory returned a null model");
        }
        // Train only on training data; use validation data only for scoring.
        model->fit(training_features, training_targets);
        const Vector predictions = model->predict(validation_features);
        const double score = RegressionMetrics::r_squared(validation_targets, predictions);
        if (!have_best || score > result.best_score) {
            // Keep ownership of the highest-scoring fitted model in the result.
            result.best_parameter = value;
            result.best_score = score;
            result.best_model = std::move(model);
            have_best = true;
        }
    }
    return result;
}

} // namespace ridge_ml
