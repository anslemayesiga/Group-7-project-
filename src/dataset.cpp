#include "ridgelib/dataset.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>

namespace RidgeRegression {

bool Dataset::loadFromCSV(const std::string& filePath, bool hasHeader) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Runtime Error: Unable to open CSV file asset at: " << filePath << std::endl;
        return false;
    }

    // Reset current containers to prevent data appending overlaps
    X.clear();
    y.clear();

    std::string line;
    if (hasHeader && std::getline(file, line)) {
        // Successfully skipped header string tokens
    }

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string valueStr;
        std::vector<double> rowFeatures;

        while (std::getline(ss, valueStr, ',')) {
            try {
                rowFeatures.push_back(std::stod(valueStr));
            } catch (...) {
                // Token corrupted or empty space detected; insert fallback marker
                rowFeatures.push_back(0.0); 
            }
        }

        if (rowFeatures.empty()) continue;

        // Separate target y variable (assumed to be the absolute last column)
        double targetValue = rowFeatures.back();
        rowFeatures.pop_back();

        X.push_back(rowFeatures);
        y.push_back(targetValue);
    }

    file.close();
    return !X.empty();
}

std::pair<Dataset, Dataset> Dataset::trainTestSplit(double trainRatio) {
    if (trainRatio <= 0.0 || trainRatio >= 1.0) {
        throw std::invalid_argument("Split ratio bounds must fall strictly between 0.0 and 1.0");
    }

    size_t totalSamples = X.size();
    std::vector<size_t> indices(totalSamples);
    for (size_t i = 0; i < totalSamples; ++i) indices[i] = i;

    // Use a fixed seed to keep matrix validation reproducible across team members
    std::mt19937 rng(42); 
    std::shuffle(indices.begin(), indices.end(), rng);

    size_t trainSize = static_cast<size_t>(totalSamples * trainRatio);

    Dataset trainSet;
    Dataset testSet;

    for (size_t i = 0; i < totalSamples; ++i) {
        size_t idx = indices[i];
        if (i < trainSize) {
            trainSet.X.push_back(X[idx]);
            trainSet.y.push_back(y[idx]);
        } else {
            testSet.X.push_back(X[idx]);
            testSet.y.push_back(y[idx]);
        }
    }

    return {trainSet, testSet};
}

} // namespace RidgeRegression
