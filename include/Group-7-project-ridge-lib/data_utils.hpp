
#ifndef RIDGE_ML_DATA_LOADER_HPP
#define RIDGE_ML_DATA_LOADER_HPP

#include <string>
#include <vector>
#include <cstddef>

namespace ridge_ml {

class DataLoader {
public:

    DataLoader() = default;

    // Stores training and testing datasets
    struct SplitResult {
        std::vector<std::vector<double>> X_train_raw;
        std::vector<std::vector<double>> X_test_raw;

        std::vector<double> y_train;
        std::vector<double> y_test;
    };

    // Stores scaling parameters
    struct ScalingParameters {
        std::vector<double> means;
        std::vector<double> standard_deviations;
    };

    

    // Load dataset from a CSV file
    void loadCSV(const std::string& filepath,
                 bool has_header = true);

    // Retrieve loaded dataset
    const std::vector<std::vector<double>>& getData() const {
        return raw_data;
    }

    // Retrieve column headers
    const std::vector<std::string>& getHeaders() const {
        return headers;
    }

    // Get dataset dimensions
    size_t getRowCount() const;
    size_t getColumnCount() const;


  

    // Handle missing values
    void handleMissingValues();

    // Remove duplicate rows
    void removeDuplicates();

    // Extract input features (X)
    std::vector<std::vector<double>>
    extractFeatures(size_t target_column_idx);

    // Extract target variable (y)
    std::vector<double>
    extractTargetColumn(size_t column_idx);


  

    // Split dataset into training and testing sets
    SplitResult trainTestSplit(
        const std::vector<std::vector<double>>& full_features,
        const std::vector<double>& full_targets,
        double train_size = 0.8,
        unsigned int random_seed = 42
    );


    // ==========================================
    // 4. FEATURE SCALING
    // ==========================================

    // Fit scaler using training features
    ScalingParameters fitStandardScaler(
        const std::vector<std::vector<double>>& X_train
    );

    // Apply standardization using fitted parameters
    std::vector<std::vector<double>> transformStandardScaler(
        const std::vector<std::vector<double>>& X,
        const ScalingParameters& parameters
    );

    // Normalize features to range [0, 1]
    std::vector<std::vector<double>> normalizeFeatures(
        const std::vector<std::vector<double>>& X
    );


private:

    // Raw dataset storage
    std::vector<std::vector<double>> raw_data;

    // Dataset column names
    std::vector<std::string> headers;

};

} // namespace ridge_ml

#endif // RIDGE_ML_DATA_LOADER_HPP
