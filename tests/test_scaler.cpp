#include "Group-7-project-ridge-lib/MinMaxScaler.hpp"
#include <cassert>
#include <cmath>
#include <stdexcept>
#include <limits>

// Check min-max scaling, reuse of fitted bounds, and invalid input handling.
int main() {
    ridge_ml::MinMaxScaler scaler;

    // A scaler must learn bounds before it can transform values.
    bool rejected = false;
    try {
        (void)scaler.transform({1, 2});
    } catch (const std::logic_error&) {
        rejected = true;
    }
    assert(rejected);

    // Empty and non-finite training data cannot define a valid range.
    rejected = false;
    try {
        scaler.fit({});
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);
    rejected = false;
    try {
        scaler.fit({std::numeric_limits<double>::quiet_NaN()});
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);

    // The training minimum maps to zero and maximum maps to one.
    const auto scaled = scaler.fit_transform({2, 4, 6});
    assert(scaled.size() == 3);
    assert(scaled[0] == 0);
    assert(scaled[2] == 1);

    // Later values use the learned bounds instead of refitting.
    const auto transformed = scaler.transform({3});
    assert(std::abs(transformed[0] - 0.25) < 1e-12);

    // A constant training column maps any transformed value to zero.
    scaler.fit({5, 5});
    assert(scaler.transform({5, 6}) == std::vector<double>({0, 0}));
}
