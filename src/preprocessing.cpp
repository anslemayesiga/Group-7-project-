#include "ridgelib/preprocessing.hpp"
#include <cmath>
#include <iostream>

namespace RidgeRegression {

void Preprocessing::handleMissingValues(std::vector<std::vector<double>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return;

    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    // Iterate feature column by column
    for (size_t c = 0; c < cols; ++c) {
        double columnSum = 0.0;
        size_t validCount = 0;

        // Pass 1: Compute cumulative mean of valid elements in the feature column
        for (size_t r = 0; r < rows; ++r) {
            double val = matrix[r][c];
            // Check for missing data markers (such as NaN, infinity, or your fallback 0.0)
            if (!std::isnan(val) && !std::isinf(val) && val != 0.0) {
                columnSum += val;
                validCount++;
            }
        }

        double columnMean = (validCount > 0) ? (columnSum / validCount) : 0.0;

        // Pass 2: Impute column mean average into broken or empty data positions
        for (size_t r = 0; r < rows; ++r) {
            double val = matrix[r][c];
            if (std::isnan(val) || std::isinf(val) || val == 0.0) {
                matrix[r][c] = columnMean;
            }
        }
    }
}

} // namespace RidgeRegression
