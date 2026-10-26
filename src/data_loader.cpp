#include "Group-7-project-ridge-lib/data_loader.hpp"

#include <cmath>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <utility>

namespace ridge_ml {
namespace {
// This loader intentionally handles simple numeric CSV, not quoted CSV syntax.
std::string trim(const std::string& value) {
    // Ignore surrounding whitespace so values such as " 2.5 " parse normally.
    const auto first = value.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return {};
    const auto last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

std::vector<std::string> split_row(const std::string& line) {
    std::vector<std::string> cells;
    std::size_t start = 0;
    while (true) {
        // Preserve empty cells so missing values can be rejected or imputed later.
        const auto comma = line.find(',', start);
        cells.push_back(trim(line.substr(start, comma == std::string::npos ? comma : comma - start)));
        if (comma == std::string::npos) break;
        start = comma + 1;
    }
    return cells;
}

double parse_number(const std::string& cell, std::size_t line) {
    if (cell.empty()) return std::numeric_limits<double>::quiet_NaN();
    std::size_t used = 0;
    double value;
    try { value = std::stod(cell, &used); }
    catch (...) { throw std::runtime_error("Invalid numeric value on CSV line " + std::to_string(line)); }
    if (used != cell.size() || !std::isfinite(value))
        throw std::runtime_error("Invalid numeric value on CSV line " + std::to_string(line));
    return value;
}
}

DataLoader::Dataset DataLoader::loadCSV(const std::string& filepath, bool has_header,
                                        MissingValuePolicy missing_policy) const {
    // Open first so errors identify the requested path immediately.
    std::ifstream input(filepath);
    if (!input) throw std::runtime_error("Cannot open CSV file: " + filepath);
    Dataset data;
    std::string line;
    std::size_t line_no = 0, columns = 0;
    if (has_header) {
        // Header names describe feature columns; the final header is the target name.
        if (!std::getline(input, line)) throw std::runtime_error("CSV file is empty");
        ++line_no;
        auto header = split_row(line);
        if (header.size() < 2) throw std::runtime_error("CSV needs at least one feature and one target column");
        columns = header.size();
        data.feature_names.assign(header.begin(), header.end() - 1);
    }
    // The last column is always the target; all earlier columns are features.
    while (std::getline(input, line)) {
        ++line_no;
        // Ignore blank lines without changing the reported physical line numbers.
        if (trim(line).empty()) continue;
        auto cells = split_row(line);
        // Infer column count from the first data row when there is no header.
        if (!columns) columns = cells.size();
        if (columns < 2 || cells.size() != columns)
            throw std::runtime_error("Invalid CSV column count on line " + std::to_string(line_no));
        std::vector<double> row;
        row.reserve(columns);
        // Parse each cell before separating target from feature values.
        for (const auto& cell : cells) row.push_back(parse_number(cell, line_no));
        if (!std::isfinite(row.back())) throw std::runtime_error("Target value is missing on CSV line " + std::to_string(line_no));
        data.targets.push_back(row.back());
        row.pop_back();
        data.features.push_back(std::move(row));
    }
    if (data.features.empty()) throw std::runtime_error("CSV file contains no data rows");
    // Imputation statistics are computed per feature column across loaded rows.
    for (std::size_t col = 0; col < data.features.front().size(); ++col) {
        // Count observed entries so missing-value policy can be applied per column.
        double sum = 0.0; std::size_t count = 0;
        for (const auto& row : data.features) if (std::isfinite(row[col])) { sum += row[col]; ++count; }
        const bool has_missing = count != data.features.size();
        if (has_missing && missing_policy == MissingValuePolicy::reject)
            throw std::runtime_error("Missing feature value; select mean_impute_features to impute it");
        if (has_missing && count == 0) throw std::runtime_error("Cannot impute a feature column with no observed values");
        if (has_missing) {
            // Use only observed values to fill missing feature cells.
            const double mean = sum / static_cast<double>(count);
            for (auto& row : data.features) if (!std::isfinite(row[col])) row[col] = mean;
        }
    }
    return data;
}

DataLoader::SplitResult DataLoader::trainTestSplit(
    const std::vector<std::vector<double>>& features,
    const std::vector<double>& targets, double train_size) const {
    // Validate the row relationship before taking iterator ranges.
    if (features.size() != targets.size() || features.size() < 2)
        throw std::invalid_argument("Split requires matching feature/target rows and at least two rows");
    if (!std::isfinite(train_size) || train_size <= 0.0 || train_size >= 1.0)
        throw std::invalid_argument("Train size must be between zero and one");
    const auto cols = features.front().size();
    // Every row must have the same, non-zero feature count.
    if (!cols) throw std::invalid_argument("Feature rows cannot be empty");
    for (const auto& row : features)
        if (row.size() != cols) throw std::invalid_argument("Feature rows must have equal lengths");
    const auto n = static_cast<std::size_t>(features.size() * train_size);
    // Converting to size_t floors the requested fraction to a whole row count.
    if (!n || n >= features.size()) throw std::invalid_argument("Split would create an empty partition");
    SplitResult result;
    // The split is deliberately deterministic: the first rows train the model.
    result.X_train_raw.assign(features.begin(), features.begin() + n);
    result.X_test_raw.assign(features.begin() + n, features.end());
    result.y_train.assign(targets.begin(), targets.begin() + n);
    result.y_test.assign(targets.begin() + n, targets.end());
    return result;
}

DataLoader::SplitResult DataLoader::trainTestSplit(const Dataset& data, double train_size) const {
    // Reuse the same checks and split behavior for a loaded Dataset.
    return trainTestSplit(data.features, data.targets, train_size);
}
} // namespace ridge_ml
