#include "Group-7-project-ridge-lib/matrix.hpp"

// Check matrix arithmetic, vector operations, and invalid-dimension handling.
#include <cassert>
#include <stdexcept>
#include <limits>

int main() {
    using namespace ridge_ml;

    // Store values row by row so the expected arithmetic is easy to inspect.
    const Matrix matrix(2, 2, {1, 2, 3, 4});
    const Matrix transposed = matrix.transpose();
    assert(transposed(1, 0) == 2);

    // Verify matrix-matrix, matrix-vector, and vector dot-product calculations.
    const Matrix product = matrix * matrix;
    assert(product(1, 1) == 22);
    assert((matrix + matrix)(0, 0) == 2);
    assert(matrix.multiply(Vector{1, 2}) == Vector({5, 11}));
    assert(dot(Vector{1, 2}, Vector{3, 4}) == 11);

    // Out-of-range element access should fail clearly.
    bool rejected = false;
    try {
        (void)matrix(2, 0);
    } catch (const std::out_of_range&) {
        rejected = true;
    }
    assert(rejected);

    // Addition requires matching shapes.
    rejected = false;
    try {
        (void)(matrix + Matrix(1, 2));
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);

    // Matrix-vector multiplication requires one vector value per column.
    rejected = false;
    try {
        (void)matrix.multiply(Vector{1});
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);

    // Supplied storage must contain exactly rows * columns elements.
    rejected = false;
    try {
        (void)Matrix(2, 2, Vector{1});
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);

    // Extremely large dimensions must be rejected before size arithmetic wraps.
    rejected = false;
    try {
        (void)Matrix(std::numeric_limits<std::size_t>::max(), 2);
    } catch (const std::length_error&) {
        rejected = true;
    }
    assert(rejected);
}
