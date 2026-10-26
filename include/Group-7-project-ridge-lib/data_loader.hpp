#ifndef RIDGE_ML_DATA_LOADER_HPP
#define RIDGE_ML_DATA_LOADER_HPP

#include <string>
#include <vector>

namespace ridge_ml {

class DataLoader {
public:
    DataLoader() = default;

    struct SplitResult {
        std::vector<std::vector<double>> X_train_raw;
        std::vector<std::vector<double>> X_test_raw;
        std::vector<double> y_train;
        std::vector<double> y_test;
    };

    void loadCSV(const std::string& filepath, bool has_header = true);
    void handleMissingValues();
    std::vector<std::vector<double>> extractFeatures(size_t target_column_idx);
    std::vector<double> extractTargetColumn(size_t column_idx);
    SplitResult trainTestSplit(const std::vector<std::vector<double>>& full_features, 
                               const std::vector<double>& full_targets, 
                               double train_size = 0.8);

    const std::vector<std::vector<double>>& getData() const { return raw_data; }

private:
    std::vector<std::vector<double>> raw_data; 
    std::vector<std::string> headers;          
};

} // namespace ridge_ml

#endif // RIDGE_ML_DATA_LOADER_HPP
