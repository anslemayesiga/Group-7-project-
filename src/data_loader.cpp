#include "Group-7-project-ridge-lib/data_loader.hpp"

#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
<<<<<<< HEAD
#include <cmath>
#include <limits>
=======
#include <string>
#include <utility>
>>>>>>> main

namespace ridge_ml {
namespace {

<<<<<<< HEAD
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
=======
std::string trim(const std::string& value) {
    const std::size_t first = value.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return {};
>>>>>>> main
    }
    const std::size_t last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

<<<<<<< HEAD
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

=======
std::vector<std::string> split_csv_row(const std::string& line) {
    std::vector<std::string> cells;
    std::size_t start = 0;
    while (true) {
        const std::size_t comma = line.find(',', start);
        cells.push_back(trim(line.substr(start, comma == std::string::npos
            ? std::string::npos : comma - start)));
        if (comma == std::string::npos) {
            break;
        }
        start = comma + 1;
    }
    return cells;
}

double parse_number(const std::string& cell, std::size_t row_number) {
    if (cell.empty()) {
        throw std::runtime_error("Empty CSV cell on row " + std::to_string(row_number));
    }
    std::size_t parsed = 0;
    double value = 0.0;
    try {
        value = std::stod(cell, &parsed);
    } catch (const std::exception&) {
        throw std::runtime_error("Invalid number on CSV row " + std::to_string(row_number));
    }
    if (parsed != cell.size() || !std::isfinite(value)) {
        throw std::runtime_error("Invalid number on CSV row " + std::to_string(row_number));
    }
    return value;
}

} // namespace

DataLoader::Dataset DataLoader::loadCSV(const std::string& filepath, bool has_header) const {
    std::ifstream file(filepath);
    if (!file) {
        throw std::runtime_error("Failed to open CSV file: " + filepath);
    }

    Dataset dataset;
    std::string line;
    std::size_t line_number = 0;
    std::size_t column_count = 0;

    if (has_header) {
        if (!std::getline(file, line)) {
            throw std::runtime_error("CSV file is empty: " + filepath);
        }
        ++line_number;
        const auto header = split_csv_row(line);
        if (header.size() < 2) {
            throw std::runtime_error("CSV must contain at least one feature and one target column");
        }
        column_count = header.size();
        dataset.feature_names.assign(header.begin(), header.end() - 1);
    }

    while (std::getline(file, line)) {
        ++line_number;
        if (trim(line).empty()) {
            continue;
        }
        const auto cells = split_csv_row(line);
        if (column_count == 0) {
            column_count = cells.size();
            if (column_count < 2) {
                throw std::runtime_error("CSV must contain at least one feature and one target column");
            }
        }
        if (cells.size() != column_count) {
            throw std::runtime_error("Inconsistent number of columns on CSV row "
                + std::to_string(line_number));
        }

        std::vector<double> row;
        row.reserve(column_count);
        for (const std::string& cell : cells) {
            row.push_back(parse_number(cell, line_number));
        }
        dataset.targets.push_back(row.back());
        row.pop_back();
        dataset.features.push_back(std::move(row));
    }

    if (dataset.features.empty()) {
        throw std::runtime_error("CSV file contains no data rows: " + filepath);
    }
    return dataset;
}

DataLoader::SplitResult DataLoader::trainTestSplit(
    const std::vector<std::vector<double>>& features,
    const std::vector<double>& targets,
    double train_size
) const {
    if (features.size() != targets.size()) {
        throw std::invalid_argument("Feature and target row counts must match");
    }
    if (features.size() < 2) {
        throw std::invalid_argument("Train/test split requires at least two rows");
    }
    if (!std::isfinite(train_size) || train_size <= 0.0 || train_size >= 1.0) {
        throw std::invalid_argument("Train size must be between 0 and 1");
    }

    const std::size_t feature_count = features.front().size();
    if (feature_count == 0) {
        throw std::invalid_argument("Feature rows must not be empty");
    }
    for (const auto& row : features) {
        if (row.size() != feature_count) {
            throw std::invalid_argument("Feature rows must have equal lengths");
        }
    }

    const std::size_t train_rows = static_cast<std::size_t>(features.size() * train_size);
    if (train_rows == 0 || train_rows >= features.size()) {
        throw std::invalid_argument("Train size leaves an empty train or test set");
    }

    SplitResult result;
    result.X_train_raw.assign(features.begin(), features.begin() + train_rows);
    result.X_test_raw.assign(features.begin() + train_rows, features.end());
    result.y_train.assign(targets.begin(), targets.begin() + train_rows);
    result.y_test.assign(targets.begin() + train_rows, targets.end());
>>>>>>> main
    return result;
}

DataLoader::SplitResult DataLoader::trainTestSplit(
    const Dataset& dataset,
    double train_size
) const {
    return trainTestSplit(dataset.features, dataset.targets, train_size);
}

} // namespace ridge_ml

