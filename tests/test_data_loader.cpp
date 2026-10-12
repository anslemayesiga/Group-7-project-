#include "ridge_ml/data_loader.hpp"
#include <iostream>
#include <cassert>

void testTrainTestSplitDistribution() {
    ridge_ml::DataLoader loader;

    // Construct a mock feature matrix containing 10 samples
    std::vector<std::vector<double>> mock_features = {
        {1.0, 2.0}, {2.0, 3.0}, {3.0, 4.0}, {4.0, 5.0}, {5.0, 6.0},
        {6.0, 7.0}, {7.0, 8.0}, {8.0, 9.0}, {9.0, 10.0}, {10.0, 11.0}
    };
    std::vector<double> mock_targets = {10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0};

    // Partition arrays with an 80/20 train/test distribution split ratio
    auto split = loader.trainTestSplit(mock_features, mock_targets, 0.8);

    // Assert row division distribution sizes are precise
    assert(split.X_train_raw.size() == 8);
    assert(split.X_test_raw.size() == 2);
    assert(split.y_train.size() == 8);
    assert(split.y_test.size() == 2);

    // Assert matrix row items line up with expectations 
    assert(split.y_train[0] == 10.0);
    assert(split.y_test[0] == 90.0);

    std::cout << "[SUCCESS] DataLoader split verification testing passed cleanly!" << std::endl;
}

int main() {
    try {
        testTrainTestSplitDistribution();
    } catch (const std::exception& e) {
        std::cerr << "[FAILURE] Testing failed: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
