#include "Group-7-project-ridge-lib/StandardScaler.hpp"
#include <cassert>
#include <cmath>
#include <stdexcept>

// Check standardization around the training mean and handling of constants.
int main() {
    ridge_ml::StandardScaler scaler;

    // Transforming before fit has no learned mean or scale to use.
    bool rejected = false;
    try {
        (void)scaler.transform({1});
    } catch (const std::logic_error&) {
        rejected = true;
    }
    assert(rejected);

    // Fit on 1, 2, 3: the mean maps to zero and lower values to negatives.
    const auto standardized = scaler.fit_transform({1, 2, 3});
    assert(std::abs(standardized[1]) < 1e-12);
    assert(std::abs(standardized[0] + 1.22474487139) < 1e-8);

    // A constant training feature uses unit scale to avoid division by zero.
    scaler.fit({4, 4});
    assert(scaler.transform({4, 5}) == std::vector<double>({0, 1}));
}
