#ifndef RIDGE_ML_DATA_LOADER_HPP
#define RIDGE_ML_DATA_LOADER_HPP

#include <string>
#include <vector>

namespace ridge_ml {

class DataLoader {
public:
    DataLoader() = default;

    // Structure to hold split train and test data matrices
    struct SplitResult {
        std::vector<std::vector<double>> X_train_raw;
        std::vector<std::vector<double>> X_test_raw;
        std::vector<double> y_train;
        std::vector<double> y_test;
    };

    // Reads a CSV file row by row and populates internal structures
    void loadCSV(const std::string& filepath, bool has_header = true);

    // Splits features matrix and target vectors based on a percentage size (e.g. 0.8)
    SplitResult trainTestSplit(const std::vector<std::vector<double>>& full_features, 
                               const std::vector<double>& full_targets, 
                               double train_size = 0.8);

private:
    std::vector<std::vector<double>> raw_data;
    std::vector<std::string> headers;
};

} // namespace ridge_ml

#endif // RIDGE_ML_DATA_LOADER_HPP
