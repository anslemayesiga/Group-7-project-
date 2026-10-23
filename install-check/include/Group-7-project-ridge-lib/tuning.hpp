#ifndef GROUP_7_PROJECT_RIDGE_LIB_TUNING_HPP
#define GROUP_7_PROJECT_RIDGE_LIB_TUNING_HPP

#include "Group-7-project-ridge-lib/regressor.hpp"

#include <functional>
#include <memory>
#include <vector>

namespace ridge_ml {

struct GridSearchResult {
    double best_parameter = 0.0;
    double best_score = 0.0;
    std::unique_ptr<Regressor> best_model;
};

class GridSearchTuner {
public:
    using ModelFactory = std::function<std::unique_ptr<Regressor>(double)>;

    explicit GridSearchTuner(ModelFactory factory);
    GridSearchResult fit(const Matrix& training_features, const Vector& training_targets,
                        const Matrix& validation_features, const Vector& validation_targets,
                        const std::vector<double>& candidates) const;

private:
    ModelFactory factory_;
};

} // namespace ridge_ml

#endif // GROUP_7_PROJECT_RIDGE_LIB_TUNING_HPP
