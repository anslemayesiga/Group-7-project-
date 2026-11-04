
#include "Group-7-project-ridge-lib/data_utils.hpp"

#include <cassert>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace ridge_ml;

// ==========================================
// TEST HELPER FUNCTIONS
// ==========================================

bool approximatelyEqual(
    double a,
    double b,
    double tolerance = 1e-6
) {
    return std::abs(a - b) < tolerance;
}


// Create a temporary CSV dataset
void createTestCSV(const std::string& filename) {

    std::ofstream file(filename);

    if (!file)
        throw std::runtime_error("Cannot create test CSV file");

    file << "Size,Bedrooms,Price\n";
    file << "100,2,200000\n";
    file << "150,3,300000\n";
    file << "200,4,400000\n";
    file << "250,5,500000\n";
    file << "300,6,600000\n";
    file << "350,7,700000\n";
    file.close();
}


// Create CSV containing missing feature values
void createMissingValueCSV(const std::string& filename) {

    std::ofstream file(filename);

    if (!file)
        throw std::runtime_error("Cannot create missing-value CSV");

    file << "Size,Bedrooms,Price\n";
    file << "100,2,200000\n";
    file << "150,,300000\n";
    file << "200,4,400000\n";
    file << "250,5,500000\n";

    file.close();
}


// Print test result
void printResult(
    const std::string& testName,
    bool passed
) {

    std::cout << (passed ? "[PASS] " : "[FAIL] ")
              << testName << '\n';
}


// ==========================================
// TEST 1: DATASET LOADING
// ==========================================

void testDatasetLoading() {

    std::cout << "\nTEST 1: DATASET LOADING\n";

    DataLoader loader;

    createTestCSV("test_dataset.csv");

    auto data = loader.loadCSV(
        "test_dataset.csv",
        true
    );

    bool rowsCorrect =
        loader.getRowCount(data) == 6;

    bool columnsCorrect =
        loader.getColumnCount(data) == 2;

    bool targetsCorrect =
        data.targets.size() == 6;

    bool headersCorrect =
        data.feature_names.size() == 2 &&
        data.feature_names[0] == "Size" &&
        data.feature_names[1] == "Bedrooms";

    printResult("CSV loading", rowsCorrect &&
                columnsCorrect &&
                targetsCorrect);

    printResult("Feature headers", headersCorrect);

    assert(rowsCorrect);
    assert(columnsCorrect);
    assert(targetsCorrect);
    assert(headersCorrect);
}


// ==========================================
// TEST 2: MISSING VALUE HANDLING
// ==========================================

void testMissingValues() {

    std::cout << "\nTEST 2: MISSING VALUE HANDLING\n";

    DataLoader loader;

    createMissingValueCSV("missing_dataset.csv");

    auto data = loader.loadCSV(
        "missing_dataset.csv",
        true,
        DataLoader::MissingValuePolicy::defer_to_training_mean
    );

    // Check that the missing value is retained
    bool missingDetected =
        std::isnan(data.features[1][1]);

    printResult("Missing value detection", missingDetected);

    assert(missingDetected);

    // Fit imputer using observed training rows
    std::vector<std::vector<double>> trainingData = {
        {100, 2},
        {150, std::numeric_limits<double>::quiet_NaN()},
        {200, 4}
    };

    auto parameters = loader.fitMeanImputer(trainingData);

    auto cleaned = loader.handleMissingValues(
        trainingData,
        parameters
    );

    // Mean of observed bedroom values = (2 + 4) / 2 = 3
    bool imputationCorrect =
        approximatelyEqual(cleaned[1][1], 3.0);

    printResult("Mean imputation", imputationCorrect);

    assert(imputationCorrect);

    // Check reject policy
    bool rejectWorks = false;

    try {

        loader.loadCSV("missing_dataset.csv", true);

    }
    catch (const std::runtime_error&) {

        rejectWorks = true;
    }

    printResult("Missing-value rejection policy", rejectWorks);

    assert(rejectWorks);
}


// ==========================================
// TEST 3: DUPLICATE REMOVAL
// ==========================================

void testDuplicateRemoval() {

    std::cout << "\nTEST 3: DUPLICATE REMOVAL\n";

    DataLoader loader;

    DataLoader::Dataset data;

    data.features = {
        {100, 2},
        {150, 3},
        {100, 2},
        {200, 4}
    };

    data.targets = {
        200000,
        300000,
        200000,
        400000
    };

    loader.removeDuplicates(data);

    bool duplicatesRemoved =
        data.features.size() == 3 &&
        data.targets.size() == 3;

    printResult("Duplicate removal", duplicatesRemoved);

    assert(duplicatesRemoved);
}


// ==========================================
// TEST 4: FEATURE AND TARGET EXTRACTION
// ==========================================

void testFeatureExtraction() {

    std::cout << "\nTEST 4: FEATURE AND TARGET EXTRACTION\n";

    DataLoader loader;

    createTestCSV("test_dataset.csv");

    auto data = loader.loadCSV("test_dataset.csv");

    auto X = loader.extractFeatures(data);

    auto y = loader.extractTargetColumn(data);

    bool featuresCorrect =
        X.size() == 6 &&
        X[0].size() == 2;

    bool targetsCorrect =
        y.size() == 6 &&
        approximatelyEqual(y[0], 200000);

    printResult("Feature extraction", featuresCorrect);

    printResult("Target extraction", targetsCorrect);

    assert(featuresCorrect);
    assert(targetsCorrect);
}


// ==========================================
// TEST 5: TRAIN-TEST SPLITTING
// ==========================================

void testTrainTestSplit() {

    std::cout << "\nTEST 5: TRAIN-TEST SPLITTING\n";

    DataLoader loader;

    createTestCSV("test_dataset.csv");

    auto data = loader.loadCSV("test_dataset.csv");

    auto split = loader.trainTestSplit(
        data,
        0.8,
        42
    );

    bool trainingCorrect =
        split.X_train_raw.size() == 4 &&
        split.y_train.size() == 4;

    bool testingCorrect =
        split.X_test_raw.size() == 2 &&
        split.y_test.size() == 2;

    printResult("80% training split", trainingCorrect);

    printResult("20% testing split", testingCorrect);

    assert(trainingCorrect);
    assert(testingCorrect);

    // Check reproducibility
    auto secondSplit = loader.trainTestSplit(
        data,
        0.8,
        42
    );

    bool reproducible =
        split.X_train_raw == secondSplit.X_train_raw &&
        split.X_test_raw == secondSplit.X_test_raw;

    printResult("Random split reproducibility", reproducible);

    assert(reproducible);
}


// ==========================================
// TEST 6: STANDARDIZATION
// ==========================================

void testStandardization() {

    std::cout << "\nTEST 6: STANDARDIZATION\n";

    DataLoader loader;

    std::vector<std::vector<double>> X_train = {
        {10, 100},
        {20, 200},
        {30, 300}
    };

    auto scaler = loader.fitStandardScaler(X_train);

    auto scaled = loader.transformStandardScaler(
        X_train,
        scaler
    );

    // Mean of standardized columns should be approximately zero
    double meanFirst = 0.0;
    double meanSecond = 0.0;

    for (const auto& row : scaled) {

        meanFirst += row[0];
        meanSecond += row[1];
    }

    meanFirst /= scaled.size();
    meanSecond /= scaled.size();

    bool meanCorrect =
        approximatelyEqual(meanFirst, 0.0) &&
        approximatelyEqual(meanSecond, 0.0);

    printResult("Standardization mean", meanCorrect);

    assert(meanCorrect);

    // Check that transformed values are finite
    bool finiteValues = true;

    for (const auto& row : scaled) {

        for (double value : row) {

            if (!std::isfinite(value))
                finiteValues = false;
        }
    }

    printResult("Standardized values are finite", finiteValues);

    assert(finiteValues);
}


// ==========================================
// TEST 7: MIN-MAX NORMALIZATION
// ==========================================

void testMinMaxNormalization() {

    std::cout << "\nTEST 7: MIN-MAX NORMALIZATION\n";

    DataLoader loader;

    std::vector<std::vector<double>> X_train = {
        {10, 100},
        {20, 200},
        {30, 300}
    };

    auto parameters = loader.fitMinMaxScaler(X_train);

    auto normalized = loader.transformMinMaxScaler(
        X_train,
        parameters
    );

    bool minimumCorrect =
        approximatelyEqual(normalized[0][0], 0.0) &&
        approximatelyEqual(normalized[0][1], 0.0);

    bool maximumCorrect =
        approximatelyEqual(normalized[2][0], 1.0) &&
        approximatelyEqual(normalized[2][1], 1.0);

    printResult("Min-Max minimum", minimumCorrect);

    printResult("Min-Max maximum", maximumCorrect);

    assert(minimumCorrect);
    assert(maximumCorrect);
}


// ==========================================
// TEST 8: CONSTANT FEATURE HANDLING
// ==========================================

void testConstantFeature() {

    std::cout << "\nTEST 8: CONSTANT FEATURE HANDLING\n";

    DataLoader loader;

    std::vector<std::vector<double>> X = {
        {10, 5},
        {20, 5},
        {30, 5}
    };

    auto scaler = loader.fitStandardScaler(X);

    auto scaled = loader.transformStandardScaler(
        X,
        scaler
    );

    bool standardConstant =
        approximatelyEqual(scaled[0][1], 0.0) &&
        approximatelyEqual(scaled[1][1], 0.0) &&
        approximatelyEqual(scaled[2][1], 0.0);

    auto minMax = loader.fitMinMaxScaler(X);

    auto normalized = loader.transformMinMaxScaler(
        X,
        minMax
    );

    bool normalizedConstant =
        approximatelyEqual(normalized[0][1], 0.0) &&
        approximatelyEqual(normalized[1][1], 0.0) &&
        approximatelyEqual(normalized[2][1], 0.0);

    printResult("Constant feature standardization", standardConstant);

    printResult("Constant feature normalization", normalizedConstant);

    assert(standardConstant);
    assert(normalizedConstant);
}


// ==========================================
// MAIN TEST PROGRAM
// ==========================================

int main() {

    std::cout << "====================================\n";
    std::cout << " RIDGE REGRESSION DATA LOADER TESTS\n";
    std::cout << "====================================\n";

    try {

        testDatasetLoading();

        testMissingValues();

        testDuplicateRemoval();

        testFeatureExtraction();

        testTrainTestSplit();

        testStandardization();

        testMinMaxNormalization();

        testConstantFeature();

        std::cout << "\n====================================\n";
        std::cout << " ALL DATA LOADER TESTS PASSED\n";
        std::cout << "====================================\n";

    }
    catch (const std::exception& e) {

        std::cerr << "\nTEST ERROR: "
                  << e.what() << '\n';

        return 1;
    }

    std::remove("test_dataset.csv");
    std::remove("missing_dataset.csv");

    return 0;
}
