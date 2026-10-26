#ifndef RIDGE_ML_DATA_LOADER_HPP
#define RIDGE_ML_DATA_LOADER_HPP

#include <string>
#include <vector>

namespace ridge_ml {

// Loads numeric CSV data and makes deterministic train/test partitions.
class DataLoader {
public:
    // Missing feature cells are rejected unless mean imputation is requested.
    enum class MissingValuePolicy { reject, mean_impute_features };

    // Features contain all columns except the final target column.
    struct Dataset {
        std::vector<std::vector<double>> features;
        std::vector<double> targets;
        std::vector<std::string> feature_names;
    };

    // Rows and targets are paired in order in each partition.
    struct SplitResult {
        std::vector<std::vector<double>> X_train_raw;
        std::vector<std::vector<double>> X_test_raw;
        std::vector<double> y_train;
        std::vector<double> y_test;
    };

    // Load numeric CSV whose final column is the target. Quoted fields and
    // malformed or non-numeric rows are not supported.
    Dataset loadCSV(const std::string& filepath, bool has_header = true,
                    MissingValuePolicy missing_policy = MissingValuePolicy::reject) const;

    // Split rows in order; train_size is the fraction assigned to training.
    SplitResult trainTestSplit(
        const std::vector<std::vector<double>>& features,
        const std::vector<double>& targets,
        double train_size = 0.8
    ) const;

    SplitResult trainTestSplit(const Dataset& dataset, double train_size = 0.8) const;
};

} // namespace ridge_ml

#endif // RIDGE_ML_DATA_LOADER_HPP
