# Module Merge Plan

This plan follows the Week 1 responsibility split in the group report. The project-structure list in that report had several conflicting owners; the corrected ownership below follows the explicit responsibility list (Khalid: solver, Mandela: ridge cost/model, Othman: evaluation).

## Member-by-member merge checklist

| Member | Assigned module | Current repository state | Files to include in the next merge |
|---|---|---|---|
| Ayesiga Anslem | Matrix and vector operations | Matrix header/source and demo are present; Matrix tests are still missing. | include/Group-7-project-ridge-lib/matrix.hpp, src/matrix.cpp, tests/tests_matrix.cpp |
| Wobusobozi Chrispus Owen | Dataset loading and preprocessing | Data loader header/source/test are present; a separate preprocessing module and preprocessing tests remain missing. | include/Group-7-project-ridge-lib/data_loader.hpp, src/data_loader.cpp, tests/test_data_loader.cpp; add preprocessing files only after agreeing its API |
| Kyelanyi Martin Tom | Feature scaling and build setup | MinMaxScaler header/source are present; scaler tests are missing. StandardScaler remains a scope decision. | include/Group-7-project-ridge-lib/MinMaxScaler.hpp, src/MinMaxScaler.cpp, tests/test_min_max_scaler.cpp |
| Kamugisha Elias | Linear regression baseline | Codex-assisted draft implementation is present; normal-case and invalid-input tests are missing. | include/Group-7-project-ridge-lib/linear_regression.hpp, src/linear_regression.cpp, tests/test_linear_regression.cpp |
| Mutyaba Rashid | Regressor interface and prediction | Abstract Regressor interface is present; it has no separate CPP file or focused tests. | include/Group-7-project-ridge-lib/regressor.hpp, tests/test_regressor.cpp |
| Khalid Taban Luate | Normal equation and linear solver | Header/source are present and aligned with Matrix; focused solver tests are missing. | include/Group-7-project-ridge-lib/normal_equation.hpp, src/normal_equation.cpp, tests/test_normal_equation.cpp |
| Mandela Nickson | Ridge cost, L2 regularization, and ridge model | Cost API and Codex-assisted RidgeRegression draft are present; focused tests are missing. | include/Group-7-project-ridge-lib/ridge_cost.hpp, src/ridge_regression_cost.cpp, include/Group-7-project-ridge-lib/ridge_regression.hpp, src/ridge_regression.cpp, tests/test_ridge_regression.cpp |
| Tumweheire Desire | Gradient descent | Codex-assisted class and implementation draft are present; focused update/cost/validation tests are missing. | include/Group-7-project-ridge-lib/gradient_descent.hpp, src/gradient_descent.cpp, tests/test_gradient_descent.cpp |
| Ssemwogerere Othman | Evaluation metrics | Codex-assisted RegressionMetrics utility draft is present; focused metric tests are missing. | include/Group-7-project-ridge-lib/metrics.hpp, src/metrics.cpp, tests/test_metrics.cpp |
| Ainemugabe Crisbert | Hyperparameter tuning | Codex-assisted grid search draft using validation R-squared is present; candidate-selection tests are missing. | include/Group-7-project-ridge-lib/tuning.hpp, src/tuning.cpp, tests/test_tuning.cpp |

## Merge order

1. Matrix, data loading/preprocessing, and scaling APIs.
2. Regressor interface, normal-equation solver, ridge cost, and model APIs.
3. Linear regression, ridge regression, and gradient descent implementations.
4. Evaluation metrics and hyperparameter tuning.
5. Integrate each test target and example into CMake, then build and run the suite before submission.


