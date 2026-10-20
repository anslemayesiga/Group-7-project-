#include "Group-7-project-ridge-lib/tuning.hpp"

#include "Group-7-project-ridge-lib/metrics.hpp"

#include <stdexcept>
#include <utility>

namespace ridge_ml {

GridSearchTuner::GridSearchTuner(ModelFactory factory) : factory_(std::move(factory)) {
    if (!factory_) {
        throw std::invalid_argument("GridSearchTuner requires a model factory");
    }
}

GridSearchResult GridSearchTuner::fit(const Matrix& training_features,
                                     const Vector& training_targets,
                                     const Matrix& validation_features,
                                     const Vector& validation_targets,
                                     const std::vector<double>& candidates) const {
    if (candidates.empty()) {
        throw std::invalid_argument("Grid search requires at least one candidate value");
    }
    if (validation_features.rows() != validation_targets.size()) {
        throw std::invalid_argument("Validation rows and targets must match");
    }

    GridSearchResult result;
    bool have_best = false;
    for (double value : candidates) {
        std::unique_ptr<Regressor> model = factory_(value);
        if (!model) {
            throw std::runtime_error("Model factory returned a null model");
        }
        model->fit(training_features, training_targets);
        const Vector predictions = model->predict(validation_features);
        const double score = RegressionMetrics::r_squared(validation_targets, predictions);
        if (!have_best || score > result.best_score) {
            result.best_parameter = value;
            result.best_score = score;
            result.best_model = std::move(model);
            have_best = true;
        }
    }
    return result;
}

} // namespace ridge_ml
