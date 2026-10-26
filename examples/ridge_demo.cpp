#include "Group-7-project-ridge-lib/matrix.hpp"
#include "Group-7-project-ridge-lib/normal_equation.hpp"
#include "Group-7-project-ridge-lib/ridge_cost.hpp"

#include <iostream>

int main() {
    // This example supplies an intercept column explicitly to the normal equation.
    // Store three observations; the first feature column is the intercept.
    const ridge_ml::Matrix features(3, 2, {1.0, 0.0, 1.0, 1.0, 1.0, 2.0});
    const ridge_ml::Vector targets{1.0, 3.0, 5.0};

    // Estimate coefficients from the normal equation, then use them to predict.
    const ridge_ml::Vector theta = ridge_ml::fit_normal_equation(features, targets);
    const ridge_ml::Vector predictions = features.multiply(theta);
    // Evaluate predictions with a positive ridge penalty on the feature weight.
    const double cost = ridge_ml::ridge_cost(targets, predictions, theta, 0.1);

    std::cout << "Intercept: " << theta[0] << '\n'
              << "Coefficient: " << theta[1] << '\n'
              << "Training cost: " << cost << '\n';
    return 0;
}
