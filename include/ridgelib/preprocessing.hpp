#ifndef PREPROCESSING_HPP
#define PREPROCESSING_HPP

#include <vector>

namespace RidgeRegression {

class Preprocessing {
public:
    // Identifies NaN / blank inputs and overwrites them with structural feature column means
    static void handleMissingValues(std::vector<std::vector<double>>& matrix);
};

} // namespace RidgeRegression

#endif // PREPROCESSING_HPP
