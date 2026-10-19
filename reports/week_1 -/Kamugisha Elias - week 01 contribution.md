KAMUGISHA ELIAS (25/U/26715 BBIO)
• Assigned Targets: linear_regression.hpp, linear_regression.cpp, test_linear_regression.cpp (Baseline Model)
• Week 1 Activity: Constructed core linear prediction structural stubs mapping plain unregularized hypothesis configurations to verify operational consistency.

# Linear Regression

## Overview

I will implement the **Linear Regression model** as a class derived from the `BaseRegressor` interface. This model will provide the baseline regression algorithm that can be used to make predictions from the input features.

## What I Will Implement

The `LinearRegression` class will:

- Inherit from `BaseRegressor`.
- Implement the `fit()` function.
- Calculate the model coefficients during training.
- Store the learned coefficients and intercept.
- Implement the `predict()` function.
- Use the learned parameters to predict target values for new input data.
- Handle cases where prediction is attempted before the model has been trained.

## Basic Model

Linear Regression models the relationship between the input features and the target value. The prediction can be represented as:

$$
\hat{y} = X\beta
$$

where:

- `X` is the feature/input matrix.
- `β` is the vector of learned coefficients.
- `ŷ` is the predicted output.

## Expected Structure

```cpp
class LinearRegression : public BaseRegressor {
private:
    Vector coefficients;
    double intercept;
    bool fitted;

public:
    LinearRegression();

    void fit(const Matrix& X, const Vector& y) override;

    Vector predict(const Matrix& X) const override;
};
```

## Purpose in the Project

The Linear Regression implementation will serve as the **baseline model** for the project. Its results can later be compared with Ridge Regression to understand the effect of regularization and determine whether Ridge Regression improves the model's performance.


• Next Week Plan: Build data logging trackers to output complete loss evaluation traces across active development steps.

## Week 1 repository-to-code cross-check

**Reporting period:** 28 September-5 October 2026.  
**Assigned area:** Linear regression baseline.

The available Git history contains no project commits during this reporting period; its earliest project commits are dated 11 October. This report therefore preserves the member's original Week 1 note as a record of the activity they reported, but does not attribute an HPP, CPP, or test implementation to Week 1 based on Git evidence. Add any work completed offline with the matching file or other evidence before submission.

## Files to prepare for the next merge

- include/ridge_ml/linear_regression.hpp, src/linear_regression.cpp, tests/test_linear_regression.cpp
- The member should commit the header, implementation, and focused tests together when the module is ready, then request review from the dependent module owners.

## AI Use

- Tool: OpenAI Codex.
- Purpose: organize this repository cross-check and proposed file list.
- Reason: make the report distinguish member-reported activity from tracked code evidence. This does not assert that the named member used AI for their Week 1 work; the member should verify and complete their own AI declaration.

