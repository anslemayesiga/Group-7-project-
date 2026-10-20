#include "Group-7-project-ridge-lib/data_loader.hpp"
#include <iostream>
#include <cassert>
#include <cmath>
#include <limits>

// Inheritance hack to safely seed mock records into private data slots for test evaluation
struct TestDataLoaderWrapper : public ridge_ml::DataLoader {
    void forceSeedData(const std::vector<std::vector<double>>& mock_matrix) {
        *(reinterpret_cast<std::vector<std::vector<double>>*>(this)) = mock_matrix;
    }
};

void runComprehensiveLibraryTests() {
    TestDataLoaderWrapper loader;

    // Seed mock matrix data matching clean/dirty columns
    // Column 0 Missing Test element: 1.0, NaN, 4.0 -> Expected Mean calculation is (1+4)/2 = 2.5
    // Column 2 acts as our target regression element row profile
    std::vector<std::vector<double>> mock_csv_rows = {
        {1.0, 10.0, 100.0},
        {std::numeric_limits<double>::quiet_NaN(), 20.0, 200.0},
        {4.0, 30.0, 300.0}
    };

    loader.forceSeedData(mock_csv_rows);

    // Test 1: Handle Missing Values (Imputation Verification)
    loader.handleMissingValues();
    auto preprocessed_grid = loader.getData();
    assert(std::abs(preprocessed_grid[1][0] - 2.5) < 1e-5); 

    // Test 2: Matrix Column Separation Extraction Checks
    std::vector<std::vector<double>> X = loader.extractFeatures(2); 
    std::vector<double> y = loader.extractTargetColumn(2);

    assert(X.size() == 3);
    assert(X[0].size() == 2); // Stripped target column out successfully
    assert(y.size() == 3);
    assert(std::abs(y[0] - 100.0) < 1e-5);    

    // Test 3: Train/Test Distribution Splitting Cuts
    auto split = loader.trainTestSplit(X, y, 0.66);
    assert(split.X_train_raw.size() == 2);
    assert(split.X_test_raw.size() == 1);
    assert(split.y_train.size() == 2);
    assert(split.y_test.size() == 1);

    std::cout << "\n" << std::endl;
    std::cout << "[SUCCESS] All individual library module tests passed!" << std::endl;
    std::cout << "\n" << std::endl;
}

int main() {
    try {
        runComprehensiveLibraryTests();
    } catch (const std::exception& e) {
        std::cerr << "[FAILURE] Production assertion checks collapsed: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
