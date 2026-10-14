#include "ridge_ml/data_loader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace ridge_ml {

void DataLoader::loadCSV(const std::string& filepath, bool has_header) {
    std::ifstream file(filepath);
    
    // Explicit rule check: Handle missing or invalid inputs gracefully
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }

    std::string line;
    // Process top row header labels if present
    if (has_header && std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            headers.push_back(cell);
        }
    }

    // Process data rows line by line
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<double> row;

        while (std::getline(ss, cell, ',')) {
            if (!cell.empty()) {
                row.push_back(std::stod(cell));
            }
        }
        if (!row.empty()) {
            raw_data.push_back(row);
        }
    }
}

DataLoader::SplitResult DataLoader::trainTestSplit(const std::vector<std::vector<double>>& full_features, 
                                                   const std::vector<double>& full_targets, 
                                                   double train_size) {
    SplitResult result;
    size_t total_rows = full_features.size();
    size_t train_rows = static_cast<size_t>(total_rows * train_size);

    // Populate the training segments
    for (size_t i = 0; i < train_rows; ++i) {
        result.X_train_raw.push_back(full_features[i]);
        result.y_train.push_back(full_targets[i]);
    }

    // Populate the testing segments
    for (size_t i = train_rows; i < total_rows; ++i) {
        result.X_test_raw.push_back(full_features[i]);
        result.y_test.push_back(full_targets[i]);
    }

    return result;
}

} // namespace ridge_ml
