#include "Group-7-project-ridge-lib/data_loader.hpp"
#include <cassert>
#include <cstdio>
#include <fstream>
#include <stdexcept>

int main() {
    const char* path = "ridgelib_test_data.csv";
    { std::ofstream file(path); file << "x1,x2,y\n1,2,5\n3,4,11\n5,6,17\n"; }
    ridge_ml::DataLoader loader;
    const auto data = loader.loadCSV(path);
    assert(data.features.size() == 3 && data.features[0].size() == 2);
    assert(data.targets.size() == 3 && data.feature_names.size() == 2);
    const auto split = loader.trainTestSplit(data, 0.66);
    assert(split.X_train_raw.size() == 1); // floor(3 * .66)
    assert(split.X_test_raw.size() == 2);
    bool rejected = false;
    try { (void)loader.trainTestSplit(data, 1.0); }
    catch (const std::invalid_argument&) { rejected = true; }
    assert(rejected);
    { std::ofstream file(path); file << "x,y\n1,2\n,4\n3,6\n"; }
    rejected = false;
    try { (void)loader.loadCSV(path); } catch (const std::runtime_error&) { rejected = true; }
    assert(rejected);
    const auto imputed = loader.loadCSV(path, true, ridge_ml::DataLoader::MissingValuePolicy::mean_impute_features);
    assert(imputed.features[1][0] == 2.0 && imputed.targets[1] == 4.0);
    { std::ofstream file(path); file << "x,y\n1,2,3\n"; }
    rejected = false;
    try { (void)loader.loadCSV(path); }
    catch (const std::runtime_error&) { rejected = true; }
    assert(rejected);
    { std::ofstream file(path); file << "x,y\n1,nan\n"; }
    rejected = false;
    try { (void)loader.loadCSV(path); }
    catch (const std::runtime_error&) { rejected = true; }
    assert(rejected);
    std::remove(path);
}
