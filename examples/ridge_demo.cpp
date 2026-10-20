#include "Group-7-project-ridge-lib/matrix.hpp"
#include "Group-7-project-ridge-lib/normal_equation.hpp"
#include "Group-7-project-ridge-lib/ridge_cost.hpp"

#include <iostream>

int main() {
    // The first column is an intercept column.
    const ridge_ml::Matrix features(3, 2, {1.0, 0.0, 1.0, 1.0, 1.0, 2.0});
    const ridge_ml::Vector targets{1.0, 3.0, 5.0};

    const ridge_ml::Vector theta = ridge_ml::fit_normal_equation(features, targets);
    const ridge_ml::Vector predictions = features.multiply(theta);
    const double cost = ridge_ml::ridge_cost(targets, predictions, theta, 0.1);

    std::cout << "Intercept: " << theta[0] << '\n'
              << "Coefficient: " << theta[1] << '\n'
              << "Training cost: " << cost << '\n';
    return 0;
}
