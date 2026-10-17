# Week 3 OOP Class Layouts — Reference for Hand Drawings

These layouts are based on the current shared source tree. Copy the relevant layout onto paper, add the actual member names and access labels, photograph it clearly, and insert the photo with the report. The layouts below are references, not photographs of a paper drawing.

**Repository status:** The current code demonstrates encapsulation in `Matrix`, `MinMaxScaler`, and several new module classes. `Matrix` and `DataLoader` have overloads (compile-time polymorphism). `Regressor` is a virtual interface; `LinearRegression` and `RidgeRegression` derive from it, and `GridSearchTuner` uses models through base-class pointers.

## Ayesiga Anslem — Matrix

Source: `include/Group-7-project-ridge-lib/matrix.hpp`, `src/matrix.cpp`.

```text
namespace ridge_ml

class Matrix
----------------------------------------
- rows_ : size_t
- cols_ : size_t
- values_ : vector<double>
- index(row, col) : size_t
----------------------------------------
+ Matrix()
+ Matrix(rows, cols, fill)
+ Matrix(rows, cols, values)
+ identity(size) : Matrix {static}
+ rows() : size_t
+ cols() : size_t
+ operator()(row, col) : double& / const double&
+ transpose() : Matrix
+ operator+(Matrix) : Matrix
+ operator-(Matrix) : Matrix
+ operator*(Matrix) : Matrix
+ operator*(scalar) : Matrix
+ multiply(Vector) : Vector
+ column(col) : Vector
+ row(row) : Vector

Free functions: operator*(scalar, Matrix), dot(Vector, Vector)
Inheritance: none     Protected members: none
Polymorphism: arithmetic operator overloading (compile-time)
```

## Wobusobozi Chrispus Owen — DataLoader

Source: `include/Group-7-project-ridge-lib/data_loader.hpp`, `src/data_loader.cpp`.

```text
namespace ridge_ml

class DataLoader
----------------------------------------
+ struct Dataset
    + features : vector<vector<double>>
    + targets : vector<double>
    + feature_names : vector<string>
+ struct SplitResult
    + X_train_raw : vector<vector<double>>
    + X_test_raw : vector<vector<double>>
    + y_train : vector<double>
    + y_test : vector<double>
----------------------------------------
+ loadCSV(filepath, has_header) const : Dataset
+ trainTestSplit(features, targets, train_size) const : SplitResult
+ trainTestSplit(dataset, train_size) const : SplitResult

Private/protected members: none in current declaration
Inheritance: none     Virtual polymorphism: none
Overloads: trainTestSplit has two argument forms (compile-time overload)
```

The nested structs expose their fields publicly, so describe encapsulation as limited rather than data-hiding those fields.

## Kyelanyi Martin Tom — MinMaxScaler

Source: `include/Group-7-project-ridge-lib/MinMaxScaler.hpp`, `src/MinMaxScaler.cpp`.

```text
namespace ridge_ml

class MinMaxScaler
----------------------------------------
- min_value_ : double
- max_value_ : double
- fitted_ : bool
----------------------------------------
+ fit(data : vector<double>) : void
+ transform(data : vector<double>) const : vector<double>
+ fit_transform(data : vector<double>) : vector<double>

Inheritance: none     Protected members: none
Polymorphism: none
```

## Khalid Taban Luate — Normal Equation / Solver

Source: `include/Group-7-project-ridge-lib/normal_equation.hpp`, `src/normal_equation.cpp`.

There is no class in this module yet. Draw a labelled function/API box (not a class box):

```text
namespace ridge_ml
+ gaussian_solve(matrix : const Matrix&, rhs : const Vector&) : Vector
+ fit_normal_equation(features : const Matrix&, targets : const Vector&) : Vector
Classes / inheritance / virtual polymorphism: none in this module
```

## Mandela Nickson — Ridge Cost

Source: `include/Group-7-project-ridge-lib/ridge_cost.hpp`, `src/ridge_regression_cost.cpp`.

The ridge-cost calculation itself is a free function; the member's new Ridge estimator class is documented below.

```text
namespace ridge_ml
+ ridge_cost(actual : const Vector&, predicted : const Vector&,
             theta : const Vector&, lambda : double) : double
Classes / inheritance / virtual polymorphism: none in this module
```

<a id="kamugisha-elias-linear-regression"></a>
## Kamugisha Elias — LinearRegression

Source: `include/Group-7-project-ridge-lib/linear_regression.hpp`, `src/linear_regression.cpp`.

```text
class LinearRegression
----------------------------------------
- coefficients_ : Vector
- fitted_ : bool
----------------------------------------
+ fit(features, targets) : void [override]
+ predict(features) const : Vector [override]
+ coefficients() const : const Vector&
Base class: Regressor
```

<a id="mutyaba-rashid-regressor-interface"></a>
## Mutyaba Rashid — Regressor interface

Source: `include/Group-7-project-ridge-lib/regressor.hpp`.

```text
class Regressor { abstract base }
----------------------------------------
----------------------------------------
+ virtual ~Regressor()
+ virtual fit(...) = 0
+ virtual predict(...) const = 0

Implemented derived relationships:
LinearRegression --|> Regressor
RidgeRegression  --|> Regressor
```

The overridden functions provide runtime polymorphism when models are used through `Regressor` references or pointers.

<a id="mandela-nickson-ridge-regression"></a>
## Mandela Nickson — RidgeRegression

Source: `include/Group-7-project-ridge-lib/ridge_regression.hpp`, `src/ridge_regression.cpp`.

```text
class RidgeRegression : public Regressor
----------------------------------------
- lambda_ : double
- coefficients_ : Vector
- fitted_ : bool
----------------------------------------
+ RidgeRegression(lambda = 1.0)
+ fit(features, targets) : void [override]
+ predict(features) const : Vector [override]
+ coefficients() const : const Vector&
+ lambda() const : double
```

<a id="tumweheire-desire-gradient-descent"></a>
## Tumweheire Desire — GradientDescent

Source: `include/Group-7-project-ridge-lib/gradient_descent.hpp`, `src/gradient_descent.cpp`.

```text
class GradientDescent
----------------------------------------
- learning_rate_ : double
- iterations_ : size_t
- lambda_ : double
----------------------------------------
+ GradientDescent(learning_rate, iterations, lambda = 0)
+ fit(design, targets, initial_parameters = {}) const : GradientDescentResult

struct GradientDescentResult
+ parameters : Vector
+ cost_history : Vector
Inheritance / protected state: none
```

<a id="ssemwogerere-othman-metrics"></a>
## Ssemwogerere Othman — RegressionMetrics

Source: `include/Group-7-project-ridge-lib/metrics.hpp`, `src/metrics.cpp`.

```text
class RegressionMetrics
+ mean_absolute_error(actual, predicted) : double {static}
+ mean_squared_error(actual, predicted) : double {static}
+ root_mean_squared_error(actual, predicted) : double {static}
+ r_squared(actual, predicted) : double {static}
No data members, inheritance, or virtual methods
```

<a id="ainemugabe-crisbert-hyperparameter-tuning"></a>
## Ainemugabe Crisbert — GridSearchTuner

Source: `include/Group-7-project-ridge-lib/tuning.hpp`, `src/tuning.cpp`.

```text
class GridSearchTuner
----------------------------------------
- factory_ : ModelFactory
----------------------------------------
+ ModelFactory : function<unique_ptr<Regressor>(double)>
+ GridSearchTuner(factory)
+ fit(train data, validation data, candidates) const : GridSearchResult

struct GridSearchResult
+ best_parameter : double
+ best_score : double
+ best_model : unique_ptr<Regressor>
Uses Regressor runtime polymorphism; GridSearchTuner has no base class
```

## Submission check

- Each member draws the layout that matches their actual source files, labels `+ public`, `- private`, and `# protected`, and shows inheritance arrows only when a real `: public Base` (or other access mode) exists.
- Take a well-lit, legible photo of the paper drawing and add the image file next to that member's Week 3 report. Then link/embed the image in the report. No paper-photo evidence is included in this repository yet.
- The added module files are AI-assisted drafts. Each member must review and understand their assigned code and adapt it as needed before submission.
