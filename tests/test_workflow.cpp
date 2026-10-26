#include "Group-7-project-ridge-lib/data_loader.hpp"
#include "Group-7-project-ridge-lib/MinMaxScaler.hpp"
#include "Group-7-project-ridge-lib/ridge_cost_function.hpp"
#include "Group-7-project-ridge-lib/metrics.hpp"
#include <cassert>
#include <cmath>

// Exercise a full path from feature scaling through ridge prediction and scoring.
int main() {
    using namespace ridge_ml;

    // Start with one feature column and a matching vector for the scaler.
    const Vector raw_values{1, 2, 3, 4, 5};

    // Learn scaling bounds, then put transformed values back into a Matrix.
    MinMaxScaler scaler;
    const Vector scaled_values = scaler.fit_transform(raw_values);
    Matrix scaled_features(5, 1);
    for (std::size_t row = 0; row < scaled_values.size(); ++row) {
        scaled_features(row, 0) = scaled_values[row];
    }

    // Fit ridge regression to targets that follow a linear pattern.
    const Vector targets{3, 5, 7, 9, 11};
    RidgeRegression model(0.0);
    model.fit(scaled_features, targets);

    // Predict and confirm the end-to-end workflow has very small error.
    const Vector predictions = model.predict(scaled_features);
    assert(RegressionMetrics::mean_squared_error(targets, predictions) < 1e-10);
}
