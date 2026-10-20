#include "Group-7-project-ridge-lib/normal_solver.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

void test_standard_invertible_system() {
    std::cout << "Running test_standard_invertible_system... ";
    
    // Setup simple linear problem where y = 2*x1 + 3*x2
    // Setup small mock structures manually verifying calculations
    // dimensions: X (3x2), y (3x1)
    linear_ml::Matrix X(3, 2);
    X.set(0, 0, 1.0); X.set(0, 1, 1.0);
    X.set(1, 0, 1.0); X.set(1, 1, 2.0);
    X.set(2, 0, 1.0); X.set(2, 1, 3.0);

    linear_ml::Matrix y(3, 1);
    y.set(0, 0, 5.0); // 2(1) + 3(1)
    y.set(1, 0, 8.0); // 2(1) + 3(2)
    y.set(2, 0, 11.0); // 2(1) + 3(3)

    try {
        linear_ml::Matrix weights = linear_ml::NormalSolver::solve_normal_equation(X, y);
        
        // Assert true coefficients are precisely resolved within margins
        assert(std::abs(weights.get(0, 0) - 2.0) < 1e-5);
        assert(std::abs(weights.get(1, 0) - 3.0) < 1e-5);
        std::cout << "PASSED\n";
    } catch (const std::exception& e) {
        std::cout << "FAILED due to unexpected exception: " << e.what() << "\n";
        assert(false);
    }
}

void test_singular_matrix_throws_exception() {
    std::cout << "Running test_singular_matrix_throws_exception... ";

    // Setting up a linearly dependent matrix setup (rows are completely identical)
    linear_ml::Matrix X(2, 2);
    X.set(0, 0, 1.0); X.set(0, 1, 2.0);
    X.set(1, 0, 1.0); X.set(1, 1, 2.0); // Dependent row

    linear_ml::Matrix y(2, 1);
    y.set(0, 0, 4.0);
    y.set(1, 0, 4.0);

    bool exception_caught = false;
    try {
        linear_ml::Matrix weights = linear_ml::NormalSolver::solve_normal_equation(X, y);
    } catch (const linear_ml::SingularMatrixException& e) {
        exception_caught = true;
    }

    assert(exception_caught && "Error: Solver must throw SingularMatrixException for non-invertible data setups.");
    std::cout << "PASSED\n";
}

void test_dimension_mismatch_throws_exception() {
    std::cout << "Running test_dimension_mismatch_throws_exception... ";

    linear_ml::Matrix X(3, 2); // 3 samples
    linear_ml::Matrix y(2, 1); // Only 2 target values

    bool mismatch_caught = false;
    try {
        linear_ml::Matrix weights = linear_ml::NormalSolver::solve_normal_equation(X, y);
    } catch (const std::invalid_argument& e) {
        mismatch_caught = true;
    }

    assert(mismatch_caught && "Error: Pipeline must catch row count structural mismatches early.");
    std::cout << "PASSED\n";
}

int main() {
    std::cout << "=== STARTING PERSON 5 NORMAL SOLVER VERIFICATION RUNS ===\n";
    test_standard_invertible_system();
    test_singular_matrix_throws_exception();
    test_dimension_mismatch_throws_exception();
    std::cout << "=== ALL TEST PIPELINES COMPILED AND PASSED SUCCESSFULLY ===\n";
    return 0;
}
