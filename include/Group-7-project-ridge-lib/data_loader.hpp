#ifndef RIDGE_ML_DATA_LOADER_HPP
#define RIDGE_ML_DATA_LOADER_HPP

#include <string>
#include <vector>

namespace ridge_ml {

class DataLoader {
public:
    struct Dataset {
        std::vector<std::vector<double>> features;
        std::vector<double> targets;
        std::vector<std::string> feature_names;
    };

    struct SplitResult {
        std::vector<std::vector<double>> X_train_raw;
        std::vector<std::vector<double>> X_test_raw;
        std::vector<double> y_train;
        std::vector<double> y_test;
    };

    // Loads a numeric CSV whose final column is the target. Quoted CSV fields
    // are not supported; malformed or non-numeric rows are rejected.
    Dataset loadCSV(const std::string& filepath, bool has_header = true) const;

    // Returns a deterministic, contiguous train/test split.
    SplitResult trainTestSplit(
        const std::vector<std::vector<double>>& features,
        const std::vector<double>& targets,
        double train_size = 0.8
    ) const;

    SplitResult trainTestSplit(const Dataset& dataset, double train_size = 0.8) const;
};

} // namespace ridge_ml

#endif // RIDGE_ML_DATA_LOADER_HPP
