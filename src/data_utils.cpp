
#include "Group-7-project-ridge-lib/data_utils.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <limits>
#include <numeric>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>

namespace ridge_ml {

namespace {



// Remove surrounding whitespace
std::string trim(const std::string& value) {

    const auto first = value.find_first_not_of(" \t\r\n");

    if (first == std::string::npos)
        return {};

    const auto last = value.find_last_not_of(" \t\r\n");

    return value.substr(first, last - first + 1);
}


// Split a CSV row into individual cells
std::vector<std::string> split_row(const std::string& line) {

    std::vector<std::string> cells;
    std::size_t start = 0;

    while (true) {

        const auto comma = line.find(',', start);

        cells.push_back(
            trim(line.substr(
                start,
                comma == std::string::npos
                    ? comma
                    : comma - start
            ))
        );

        if (comma == std::string::npos)
            break;

        start = comma + 1;
    }

    return cells;
}


// Convert a CSV cell into a numerical value
double parse_number(
    const std::string& cell,
    std::size_t line
) {

    // Empty cells represent missing values
    if (cell.empty())
        return std::numeric_limits<double>::quiet_NaN();

    std::size_t used = 0;
    double value;

    try {

        value = std::stod(cell, &used);

    }
    catch (...) {

        throw std::runtime_error(
            "Invalid numeric value on CSV line " +
            std::to_string(line)
        );
    }

    if (used != cell.size() || !std::isfinite(value)) {

        throw std::runtime_error(
            "Invalid numeric value on CSV line " +
            std::to_string(line)
        );
    }

    return value;
}


// Validate feature dimensions
std::size_t validate_features(
    const std::vector<std::vector<double>>& X
) {

    if (X.empty())
        throw std::invalid_argument(
            "Dataset cannot be empty"
        );

    const std::size_t cols = X.front().size();

    if (cols == 0)
        throw std::invalid_argument(
            "Feature rows cannot be empty"
        );

    for (const auto& row : X) {

        if (row.size() != cols)
            throw std::invalid_argument(
                "Feature rows must have equal lengths"
            );
    }

    return cols;
}


// Ensure feature values are valid before scaling
void require_finite(
    const std::vector<std::vector<double>>& X
) {

    for (const auto& row : X) {

        for (double value : row) {

            if (!std::isfinite(value))
                throw std::invalid_argument(
                    "Missing or invalid values found. "
                    "Handle missing values before scaling."
                );
        }
    }
}




} 

DataLoader::Dataset DataLoader::loadCSV(
    const std::string& filepath,
    bool has_header,
    MissingValuePolicy missing_policy
) const {

    std::ifstream input(filepath);

    if (!input)
        throw std::runtime_error(
            "Cannot open CSV file: " + filepath
        );

    Dataset data;

    std::string line;

    std::size_t line_no = 0;
    std::size_t columns = 0;


    // Read column headers
    if (has_header) {

        if (!std::getline(input, line))
            throw std::runtime_error(
                "CSV file is empty"
            );

        ++line_no;

        auto header = split_row(line);

        if (header.size() < 2)
            throw std::runtime_error(
                "CSV requires at least one feature "
                "and one target column"
            );

        columns = header.size();

        // The final header represents the target
        data.feature_names.assign(
            header.begin(),
            header.end() - 1
        );
    }


    // Read dataset rows
    while (std::getline(input, line)) {

        ++line_no;

        if (trim(line).empty())
            continue;

        auto cells = split_row(line);

        // Infer column count if there is no header
        if (!columns)
            columns = cells.size();

        if (columns < 2 || cells.size() != columns)
            throw std::runtime_error(
                "Invalid CSV column count on line " +
                std::to_string(line_no)
            );

        std::vector<double> row;

        row.reserve(columns);

        for (const auto& cell : cells) {

            row.push_back(
                parse_number(cell, line_no)
            );
        }


        // Target values cannot be missing
        if (!std::isfinite(row.back()))
            throw std::runtime_error(
                "Target value is missing on CSV line " +
                std::to_string(line_no)
            );


        // Separate target from features
        data.targets.push_back(row.back());

        row.pop_back();

        data.features.push_back(
            std::move(row)
        );
    }


    if (data.features.empty())
        throw std::runtime_error(
            "CSV file contains no data rows"
        );


    // Apply missing-value policy
    for (const auto& row : data.features) {

        for (double value : row) {

            if (!std::isfinite(value) &&
                missing_policy == MissingValuePolicy::reject) {

                throw std::runtime_error(
                    "Missing feature value found. "
                    "Use defer_to_training_mean to impute it."
                );
            }
        }
    }

    return data;
}


// Get number of observations
std::size_t DataLoader::getRowCount(
    const Dataset& data
) const {

    return data.features.size();
}


// Get number of feature columns
std::size_t DataLoader::getColumnCount(
    const Dataset& data
) const {

    if (data.features.empty())
        return 0;

    return data.features.front().size();
}


// Remove duplicate observations
void DataLoader::removeDuplicates(
    Dataset& data
) const {

    if (data.features.size() != data.targets.size())
        throw std::invalid_argument(
            "Feature and target row counts do not match"
        );

    if (!data.features.empty()) {

        const std::size_t cols =
            validate_features(data.features);

        for (double target : data.targets) {

            if (!std::isfinite(target))
                throw std::invalid_argument(
                    "Target values must be finite"
                );
        }

        (void)cols;
    }

    std::vector<std::vector<double>> unique_features;
    std::vector<double> unique_targets;

    for (std::size_t i = 0;
         i < data.features.size(); ++i) {

        bool duplicate = false;

        for (std::size_t j = 0;
             j < unique_features.size(); ++j) {

            if (data.targets[i] != unique_targets[j])
                continue;

            bool same_row = true;

            for (std::size_t k = 0;
                 k < data.features[i].size(); ++k) {

                const double a = data.features[i][k];
                const double b = unique_features[j][k];

                if (a == b)
                    continue;

                // Treat two missing values as equal
                if (std::isnan(a) && std::isnan(b))
                    continue;

                same_row = false;
                break;
            }

            if (same_row) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate) {

            unique_features.push_back(data.features[i]);
            unique_targets.push_back(data.targets[i]);
        }
    }

    data.features = std::move(unique_features);
    data.targets = std::move(unique_targets);
}





// Calculate means using training data only
DataLoader::ImputationParameters
DataLoader::fitMeanImputer(
    const std::vector<std::vector<double>>& X_train
) const {

    const std::size_t cols =
        validate_features(X_train);

    ImputationParameters parameters;

    parameters.means.resize(cols);

    for (std::size_t col = 0; col < cols; ++col) {

        double sum = 0.0;
        std::size_t count = 0;

        for (const auto& row : X_train) {

            if (std::isfinite(row[col])) {

                sum += row[col];
                ++count;
            }
        }

        if (count == 0)
            throw std::runtime_error(
                "Cannot impute a feature column "
                "with no observed values"
            );

        parameters.means[col] =
            sum / static_cast<double>(count);
    }

    return parameters;
}


// Replace missing values using training means
std::vector<std::vector<double>>
DataLoader::handleMissingValues(
    const std::vector<std::vector<double>>& X,
    const ImputationParameters& parameters
) const {

    const std::size_t cols =
        validate_features(X);

    if (parameters.means.size() != cols)
        throw std::invalid_argument(
            "Imputation parameter dimensions do not match"
        );

    for (double mean : parameters.means) {

        if (!std::isfinite(mean))
            throw std::invalid_argument(
                "Invalid imputation parameter"
            );
    }

    auto result = X;

    for (auto& row : result) {

        for (std::size_t col = 0; col < cols; ++col) {

            if (!std::isfinite(row[col]))
                row[col] = parameters.means[col];
        }
    }

    return result;
}





std::vector<std::vector<double>>
DataLoader::extractFeatures(
    const Dataset& data
) const {

    if (data.features.size() != data.targets.size())
        throw std::invalid_argument(
            "Feature and target row counts do not match"
        );

    return data.features;
}


std::vector<double>
DataLoader::extractTargetColumn(
    const Dataset& data
) const {

    if (data.features.size() != data.targets.size())
        throw std::invalid_argument(
            "Feature and target row counts do not match"
        );

    return data.targets;
}





DataLoader::SplitResult DataLoader::trainTestSplit(
    const std::vector<std::vector<double>>& features,
    const std::vector<double>& targets,
    double train_size,
    unsigned int random_seed
) const {

    if (features.size() != targets.size() ||
        features.size() < 2) {

        throw std::invalid_argument(
            "Split requires matching feature and target rows "
            "and at least two observations"
        );
    }

    if (!std::isfinite(train_size) ||
        train_size <= 0.0 ||
        train_size >= 1.0) {

        throw std::invalid_argument(
            "Train size must be between zero and one"
        );
    }

    validate_features(features);

    for (double target : targets) {

        if (!std::isfinite(target))
            throw std::invalid_argument(
                "Target values must be finite"
            );
    }


    // Create row indices
    std::vector<std::size_t> indices(features.size());

    std::iota(
        indices.begin(),
        indices.end(),
        0
    );


    // Shuffle indices randomly
    std::mt19937 generator(random_seed);

    std::shuffle(
        indices.begin(),
        indices.end(),
        generator
    );


    // Calculate training row count
    const std::size_t n =
        static_cast<std::size_t>(
            features.size() * train_size
        );

    if (n == 0 || n >= features.size())
        throw std::invalid_argument(
            "Split would create an empty partition"
        );


    SplitResult result;

    // Distribute rows into training and testing sets
    for (std::size_t i = 0;
         i < indices.size(); ++i) {

        const std::size_t index = indices[i];

        if (i < n) {

            result.X_train_raw.push_back(
                features[index]
            );

            result.y_train.push_back(
                targets[index]
            );

        } else {

            result.X_test_raw.push_back(
                features[index]
            );

            result.y_test.push_back(
                targets[index]
            );
        }
    }

    return result;
}


// Split an already loaded Dataset
DataLoader::SplitResult DataLoader::trainTestSplit(
    const Dataset& data,
    double train_size,
    unsigned int random_seed
) const {

    return trainTestSplit(
        data.features,
        data.targets,
        train_size,
        random_seed
    );
}



// Fit standard scaler using training data
DataLoader::ScalingParameters
DataLoader::fitStandardScaler(
    const std::vector<std::vector<double>>& X_train
) const {

    const std::size_t cols =
        validate_features(X_train);

    require_finite(X_train);

    ScalingParameters parameters;

    parameters.means.resize(cols);

    parameters.standard_deviations.resize(cols);


    for (std::size_t col = 0; col < cols; ++col) {

        double sum = 0.0;

        for (const auto& row : X_train)
            sum += row[col];

        const double mean =
            sum / static_cast<double>(X_train.size());


        // Calculate variance
        double squared_sum = 0.0;

        for (const auto& row : X_train) {

            const double difference =
                row[col] - mean;

            squared_sum +=
                difference * difference;
        }


        // Population standard deviation
        double standard_deviation = std::sqrt(
            squared_sum /
            static_cast<double>(X_train.size())
        );


        // Prevent division by zero
        if (standard_deviation == 0.0)
            standard_deviation = 1.0;


        parameters.means[col] = mean;

        parameters.standard_deviations[col] =
            standard_deviation;
    }

    return parameters;
}


// Transform features using fitted parameters
std::vector<std::vector<double>>
DataLoader::transformStandardScaler(
    const std::vector<std::vector<double>>& X,
    const ScalingParameters& parameters
) const {

    const std::size_t cols =
        validate_features(X);

    require_finite(X);

    if (parameters.means.size() != cols ||
        parameters.standard_deviations.size() != cols) {

        throw std::invalid_argument(
            "Standard scaler dimensions do not match"
        );
    }

    auto result = X;

    for (std::size_t col = 0; col < cols; ++col) {

        if (!std::isfinite(parameters.means[col]) ||
            !std::isfinite(parameters.standard_deviations[col]) ||
            parameters.standard_deviations[col] <= 0.0) {

            throw std::invalid_argument(
                "Invalid standardization parameters"
            );
        }
    }

    for (auto& row : result) {

        for (std::size_t col = 0; col < cols; ++col) {

            row[col] =
                (row[col] - parameters.means[col]) /
                parameters.standard_deviations[col];
        }
    }

    return result;
}





// Fit Min-Max scaler using training data
DataLoader::NormalizationParameters
DataLoader::fitMinMaxScaler(
    const std::vector<std::vector<double>>& X_train
) const {

    const std::size_t cols =
        validate_features(X_train);

    require_finite(X_train);

    NormalizationParameters parameters;

    parameters.minimums.resize(cols);
    parameters.maximums.resize(cols);


    for (std::size_t col = 0; col < cols; ++col) {

        double minimum = X_train[0][col];
        double maximum = X_train[0][col];

        for (const auto& row : X_train) {

            minimum = std::min(minimum, row[col]);

            maximum = std::max(maximum, row[col]);
        }

        parameters.minimums[col] = minimum;

        parameters.maximums[col] = maximum;
    }

    return parameters;
}


// Apply Min-Max normalization
std::vector<std::vector<double>>
DataLoader::transformMinMaxScaler(
    const std::vector<std::vector<double>>& X,
    const NormalizationParameters& parameters
) const {

    const std::size_t cols =
        validate_features(X);

    require_finite(X);

    if (parameters.minimums.size() != cols ||
        parameters.maximums.size() != cols) {

        throw std::invalid_argument(
            "Normalization parameter dimensions do not match"
        );
    }


    // Validate fitted parameters
    for (std::size_t col = 0; col < cols; ++col) {

        if (!std::isfinite(parameters.minimums[col]) ||
            !std::isfinite(parameters.maximums[col]) ||
            parameters.maximums[col] < parameters.minimums[col]) {

            throw std::invalid_argument(
                "Invalid Min-Max normalization parameters"
            );
        }
    }


    auto result = X;

    for (auto& row : result) {

        for (std::size_t col = 0; col < cols; ++col) {

            const double range =
                parameters.maximums[col] -
                parameters.minimums[col];


            // Handle constant feature columns
            if (range == 0.0) {

                row[col] = 0.0;

            } else {

                row[col] =
                    (row[col] - parameters.minimums[col]) /
                    range;
            }
        }
    }

    return result;
}

} // namespace ridge_ml
