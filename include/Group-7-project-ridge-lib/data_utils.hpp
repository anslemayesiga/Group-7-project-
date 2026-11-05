
#ifndef RIDGE_ML_DATA_LOADER_HPP
#define RIDGE_ML_DATA_LOADER_HPP

#include <string>
#include <vector>
#include <cstddef>

namespace ridge_ml {

class DataLoader {
public:

    // Missing-value handling options
    enum class MissingValuePolicy {
        reject,
        defer_to_training_mean
    };

    // Complete dataset
    struct Dataset {
        std::vector<std::vector<double>> features;
        std::vector<double> targets;
        std::vector<std::string> feature_names;
    };

    // Training and testing datasets
    struct SplitResult {
        std::vector<std::vector<double>> X_train_raw;
        std::vector<std::vector<double>> X_test_raw;
        std::vector<double> y_train;
        std::vector<double> y_test;
    };

    // Mean imputation parameters
    struct ImputationParameters {
        std::vector<double> means;
    };

    // Standardization parameters
    struct ScalingParameters {
        std::vector<double> means;
        std::vector<double> standard_deviations;
    };

    // Min-Max normalization parameters
    struct NormalizationParameters {
        std::vector<double> minimums;
        std::vector<double> maximums;
    };


    

    Dataset loadCSV(
        const std::string& filepath,
        bool has_header = true,
        MissingValuePolicy missing_policy =
            MissingValuePolicy::reject
    ) const;

    std::size_t getRowCount(const Dataset& data) const;

    std::size_t getColumnCount(const Dataset& data) const;

    void removeDuplicates(Dataset& data) const;


    

    ImputationParameters fitMeanImputer(
        const std::vector<std::vector<double>>& X_train
    ) const;

    std::vector<std::vector<double>> handleMissingValues(
        const std::vector<std::vector<double>>& X,
        const ImputationParameters& parameters
    ) const;


    std::vector<std::vector<double>> extractFeatures(
        const Dataset& data
    ) const;

    std::vector<double> extractTargetColumn(
        const Dataset& data
    ) const;


    

    SplitResult trainTestSplit(
        const std::vector<std::vector<double>>& features,
        const std::vector<double>& targets,
        double train_size = 0.8,
        unsigned int random_seed = 42
    ) const;

    SplitResult trainTestSplit(
        const Dataset& data,
        double train_size = 0.8,
        unsigned int random_seed = 42
    ) const;



    ScalingParameters fitStandardScaler(
        const std::vector<std::vector<double>>& X_train
    ) const;

    std::vector<std::vector<double>> transformStandardScaler(
        const std::vector<std::vector<double>>& X,
        const ScalingParameters& parameters
    ) const;


    

    NormalizationParameters fitMinMaxScaler(
        const std::vector<std::vector<double>>& X_train
    ) const;

    std::vector<std::vector<double>> transformMinMaxScaler(
        const std::vector<std::vector<double>>& X,
        const NormalizationParameters& parameters
    ) const;

};

} // namespace ridge_ml

#endif // RIDGE_ML_DATA_LOADER_HPP
