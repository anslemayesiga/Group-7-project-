# RidgeLib

RidgeLib (Project 14) is a reusable C++17 library implementing matrix operations and a ridge-regression workflow without a machine-learning dependency in its core.

## Features and module APIs

- Matrix and vector arithmetic: `matrix.hpp`
- Numeric CSV loading, feature/target separation, deterministic split, and explicit optional mean imputation for feature blanks: `data_loader.hpp`
- Min-max and standard feature scaling: `MinMaxScaler.hpp`, `StandardScaler.hpp`
- Linear baseline and common polymorphic model interface: `linear_regression.hpp`, `regressor.hpp`
- Gaussian elimination and normal equation: `normal_equation.hpp`
- Ridge estimator and objective, batch gradient descent, and grid search: `ridge_cost_function.hpp`, `gradient_descent.hpp`, `tuning.hpp`
- MAE, MSE, RMSE, and R²: `metrics.hpp`

Missing feature values are rejected by default; callers may explicitly select column-mean imputation. Missing targets and nonnumeric values are rejected. Scalers currently operate on one feature vector at a time. Gradient descent has a maximum iteration count and optional absolute change-in-cost tolerance and returns cost history, iterations run, and convergence status. Grid search uses a caller-provided validation set and R²; do not pass the final test set as validation data.

## Build

Requirements: CMake 3.16 or newer and a C++17 compiler. The default build enables examples, tests, and library warnings. Use `-DRIDGELIB_BUILD_EXAMPLES=OFF` to omit examples and `-DBUILD_TESTING=OFF` to omit tests.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

On Windows with MSYS2 MinGW, configure with `-G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=g++`.

VS Code users should install a C++17 toolchain (such as MSYS2 MinGW-w64), ensure `cmake` and `g++` are on `PATH`, then run the commands above in the project root. Linux users can use their distribution's CMake and GCC/Clang packages.

## Use as a library

Add this repository as a CMake subdirectory and link the exported build target:

```cmake
add_subdirectory(path/to/Group-7-project)
target_link_libraries(my_app PRIVATE ridgelib::ridgelib)
```

Include public headers through the stable project include prefix:

```cpp
#include <Group-7-project-ridge-lib/matrix.hpp>
#include <Group-7-project-ridge-lib/ridge_cost_function.hpp>
```

Example:

```cpp
ridge_ml::Matrix x(4, 1);
x(0, 0) = 1.0; x(1, 0) = 2.0; x(2, 0) = 3.0; x(3, 0) = 4.0;
ridge_ml::Vector y{3.0, 5.0, 7.0, 9.0};
ridge_ml::RidgeRegression model(0.1);
model.fit(x, y);
const auto predictions = model.predict(x);
```

`RidgeRegression` adds an intercept automatically. Its regularization parameter must be finite and non-negative. Call `fit` before `predict`. `DataLoader::loadCSV` expects numeric, unquoted comma-separated fields with the target in the final column; malformed rows are rejected. `trainTestSplit` uses a deterministic contiguous split.

## Mathematical conventions

For a design matrix that already contains an intercept column, `ridge_cost` and `GradientDescent` use

`J(theta) = (||X theta - y||² + lambda * ||theta_features||²) / (2n)`.

The first parameter is treated as the intercept and excluded from the L2 penalty. `fit_normal_equation` solves the unregularized system `XᵀX theta = Xᵀy`; callers include an intercept column themselves. `LinearRegression` adds an intercept internally. `RidgeRegression` also adds an intercept internally and uses the regularized normal equation while leaving that intercept unpenalized. The current normal-equation solver uses Gaussian elimination with partial pivoting; it does not yet use QR, so ill-conditioned designs may be numerically sensitive. Scale features using training-set-only fit, then reuse the learned scaler for validation/test data.

## Dataset assumptions and limitations

CSV must contain at least one numeric feature and one numeric target in its final column. Quoted fields and categorical values are unsupported. Missing feature cells may be rejected or column-mean imputed; missing targets and other invalid values are rejected. Train/test splitting is contiguous rather than randomized. Constant-target R² is defined as 1 for a perfect prediction and 0 otherwise. The checked-in suite has eleven CTest targets. Fuzzing, sanitizers, broad ill-conditioning studies, and cross-platform CI have not been completed.

## Group responsibilities

The current module plan assigns: Ayesiga Anslem—matrix/vector; Wobusobozi Chrispus Owen—dataset loading; preprocessing—group scope, currently incomplete; Kyelanyi Martin Tom—scaling/build; Kamugisha Elias—linear regression; Khalid Taban Luate—normal equation; Mandela Nickson—ridge cost/model; gradient descent—transferred from Tumweheire Desire to Ayesiga Anslem; Ainemugabe Crisbert—tuning; Ssemwogerere Othman—metrics. These are assignment areas, not claims of independently authored code. Confirm current ownership with the group before submission. The planned review rotation is member 1 reviews 2, continuing cyclically, with member 10 reviewing member 1.

## Reference comparison and AI disclosure

No scikit-learn comparison has been run or recorded yet. A reproducible comparison should use identical numeric data, intercept handling, scaling, and lambda/objective conventions before reporting coefficients or scores. AI assistance disclosure should be completed by members according to their course rules and actual use; this README does not attribute AI use to individuals.

## Project layout

- `include/Group-7-project-ridge-lib/`: public headers
- `src/`: library implementation
- `examples/`: runnable examples
- `tests/`: CTest test programs
- `reports/`: weekly group and member reports

The library target is `ridgelib::ridgelib`; set `RIDGELIB_BUILD_EXAMPLES=OFF` to omit examples. CTest targets are controlled by `BUILD_TESTING`.
