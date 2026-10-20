#include "ridge_ml/data_loader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <limits>

namespace ridge_ml {

// 1. Dataset Loading
void DataLoader::loadCSV(const std::string& filepath, bool has_header) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }

    raw_data.clear();
    headers.clear();
    std::string line;

    if (has_header && std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            headers.push_back(cell);
        }
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<double> row;

        while (std::getline(ss, cell, ',')) {
            if (cell.empty()) {
                row.push_back(std::numeric_limits<double>::quiet_NaN());
            } else {
                row.push_back(std::stod(cell));
            }
        }
        if (!row.empty()) {
            raw_data.push_back(row);
        }
    }
}

// 2. Data Preprocessing: Mean Imputation
void DataLoader::handleMissingValues() {
    if (raw_data.empty()) return;

    size_t num_rows = raw_data.size();
    size_t num_cols = raw_data[0].size();

    for (size_t col = 0; col < num_cols; ++col) {
        double sum = 0.0;
        size_t valid_count = 0;

        for (size_t row = 0; row < num_rows; ++row) {
            if (col < raw_data[row].size() && !std::isnan(raw_data[row][col])) {
                sum += raw_data[row][col];
                valid_count++;
            }
        }

        double mean = (valid_count > 0) ? (sum / valid_count) : 0.0;

        for (size_t row = 0; row < num_rows; ++row) {
            if (col < raw_data[row].size() && std::isnan(raw_data[row][col])) {
                raw_data[row][col] = mean;
            }
        }
    }
}

// 3. Data Preprocessing: Feature Matrix Extraction
std::vector<std::vector<double>> DataLoader::extractFeatures(size_t target_column_idx) {
    std::vector<std::vector<double>> features;
    for (const auto& row : raw_data) {
        std::vector<double> feature_row;
        for (size_t col = 0; col < row.size(); ++col) {
            if (col != target_column_idx) {
                feature_row.push_back(row[col]);
            }
        }
        features.push_back(feature_row);
    }
    return features;
}

// 4. Data Preprocessing: Target Vector Extraction
std::vector<double> DataLoader::extractTargetColumn(size_t column_idx) {
    std::vector<double> target;
    for (const auto& row : raw_data) {
        if (column_idx < row.size()) {
            target.push_back(row[column_idx]);
        } else {
            target.push_back(0.0);
        }
    }
    return target;
}

// 5. Data Preprocessing: Train/Test Partitions Split
DataLoader::SplitResult DataLoader::trainTestSplit(const std::vector<std::vector<double>>& full_features, 
                                                   const std::vector<double>& full_targets, 
                                                   double train_size) {
    SplitResult result;
    size_t total_rows = full_features.size();
    size_t train_rows = static_cast<size_t>(total_rows * train_size);

    for (size_t i = 0; i < train_rows; ++i) {
        result.X_train_raw.push_back(full_features[i]);
        result.y_train.push_back(full_targets[i]);
    }

    for (size_t i = train_rows; i < total_rows; ++i) {
        result.X_test_raw.push_back(full_features[i]);
        result.y_test.push_back(full_targets[i]);
    }

    return result;
}

} // namespace ridge_ml
