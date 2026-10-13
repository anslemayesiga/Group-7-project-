#ifndef DATASET_HPP
#define DATASET_HPP

#include <string>
#include <vector>

namespace RidgeRegression {

class Dataset {
private:
    std::vector<std::vector<double>> X; // Stores features
    std::vector<double> y;              // Stores targets

public:
    Dataset() = default;

    // Parses raw CSV rows
    bool loadFromCSV(const std::string& filePath, bool hasHeader = true);

    // Splits into distinct training and testing segments
    std::pair<Dataset, Dataset> trainTestSplit(double trainRatio);

    // Public getters so other teammates can access the parsed data matrices
    const std::vector<std::vector<double>>& getFeatures() const { return X; }
    const std::vector<double>& getTargets() const { return y; }
};

} // namespace RidgeRegression

#endif // DATASET_HPP
