#include <iostream>
#include <vector>
using namespace std;
double ridgeCost(
    const vector<double>& actual,
    const vector<double>& predicted,
    const vector<double>& theta,
    double lambda
) {
    int m = actual.size();

    if (m == 0 || predicted.size() != actual.size()
        || theta.empty() || lambda < 0) {
        return -1.0;
    }

    double errorSum = 0.0;
    double penalty = 0.0;
    for (int i = 0; i < m; i++) {
        double error = predicted[i] - actual[i];
        errorSum += error * error;
    }

    // Calculate L2 penalty, excluding intercept theta[0]
    for (int j = 1; j < theta.size(); j++) {
        penalty += theta[j] * theta[j];
    }

    // Calculate total Ridge Regression cost
    return errorSum / (2.0 * m)
        + lambda * penalty / (2.0 * m);
}

int main() {
    vector<double> actual = {2, 4, 5};
    vector<double> predicted = {3, 5, 7};
    vector<double> theta = {1, 2};

    double lambda = 0.5;

    cout << "Ridge Cost = "
         << ridgeCost(actual, predicted, theta, lambda)
         << endl;

    return 0;
}