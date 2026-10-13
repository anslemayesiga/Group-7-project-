#include "ridgelib/dataset.hpp"
#include "ridgelib/preprocessing.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

int main() {
    std::cout << "     " << std::endl;
    std::cout << "RUNNING: Dataset & Preprocessing Unit Tests" << std::endl;
    std::cout << "     " << std::endl;

    // --- TEST CASE 1: Imputation Handling ---
    std::cout << "[Test 1] Testing Mean Value Imputation... ";
    
    // Create a mock feature matrix with an intentional missing element (0.0 acting as a hole)
    // Column 0 Mean: (10.0 + 20.0) / 2 = 15.0
    std::vector<std::vector<double>> mockMatrix = {
        {10.0, 5.0},
        {0.0,  5.0}, // The 0.0 value is missing/corrupted
        {20.0, 5.0}
    };

    RidgeRegression::Preprocessing::handleMissingValues(mockMatrix);

    // Verify the corrupted spot was successfully replaced with the column mean average (15.0)
    assert(std::abs(mockMatrix[1][0] - 15.0) < 1e-5);
    std::cout << "PASSED ✅" << std::endl;


    // --- TEST CASE 2: Train/Test Validation Split Boundaries ---
    std::cout << "[Test 2] Testing Dataset Split Boundaries... ";
    
    // Manually trigger a structural validation split exception test
    RidgeRegression::Dataset dummyDataset;
    bool exceptionThrown = false;
    try {
        dummyDataset.trainTestSplit(1.5); // Invalid ratio (must be between 0.0 and 1.0)
    } catch (const std::invalid_argument& e) {
        exceptionThrown = true;
    }
    
    assert(exceptionThrown == true);
    std::cout << "PASSED ✅" << std::endl;

    std::cout << "\nAll local preprocessing components passed validation tests successfully!" << std::endl;
    return 0;
}
