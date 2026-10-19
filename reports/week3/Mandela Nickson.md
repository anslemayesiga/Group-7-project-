 Week 3 Individual Progress Report
Name: Mandela Nickson  
Assigned module: Ridge cost function and L2 regularization  
Reporting period: 13-19 October 2026 (status as of 17 October)



 Completed / repository evidence

- Commit 11df2c1 on 13 October adds src/ridge_regression_cost.cpp. It contained a standalone main() and had no public cost header or focused test.

 In Progress

- The cost formula was drafted; the public API, error handling, intercept convention, and tests were not integrated at the Week 3 checkpoint.

 CHALLENGES

- A source file with main() cannot be linked into a reusable library. The intercept-exclusion rule needs to match the ridge model's parameter layout.

 Next Week - files to merge

- Add tests for ridge cost and for `RidgeRegression` fit/predict, non-negative lambda validation, intercept handling, and polymorphic use through `Regressor`. Review the model files. No tests were run during this follow-up.


 Week 3 shared code status 

The current checkout contains `ridge_cost.hpp`, `ridge_regression_cost.cpp`, `ridge_regression.hpp`, and `ridge_regression.cpp` under the project include/source folders. 

 OOP Concepts and Class Layout (Week 3)
Code files prepared for the assigned module: `include/Group-7-project-ridge-lib/ridge_cost.hpp`, `src/ridge_regression_cost.cpp`, `include/Group-7-project-ridge-lib/ridge_regression.hpp`, and `src/ridge_regression.cpp`.

- Encapsulation: `RidgeRegression` keeps `lambda_`, fitted coefficients, and fitted state private. Public methods expose fitting, prediction, and read-only accessors.
- Inheritance and runtime polymorphism: `RidgeRegression` publicly derives from abstract `Regressor` and overrides virtual `fit` and `predict`. The separate `ridge_cost` helper remains a free function.
- Layout to draw: `RidgeRegression` derives from `Regressor`; private `lambda_`, `coefficients_`, `fitted_`; public constructor, `fit`, `predict`, `coefficients`, `lambda`.


