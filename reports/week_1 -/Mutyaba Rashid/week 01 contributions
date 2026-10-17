MUTYABA RASHID (20/U/19699/PSA BELE)
• Assigned Targets: regressor.hpp, regressor.cpp, test_regressor.cpp (High-Level Model Wrapper)
• Week 1 Activity: Mapped structural data movement pipelines within the parent regressor class to accept array-based input properties cleanly.


# Base Regressor Interface

## Overview

I will develop the **Base Regressor interface** for the machine learning project. This interface will provide the common structure that different regression models can follow, making the code organized, reusable, and easy to extend.

## What I Will Implement

The `BaseRegressor` class will define the basic operations required by a regression model:

- A `fit()` function for training the model.
- A `predict()` function for making predictions.
- Virtual functions so that individual regression models can provide their own implementations.
- A common interface that can be inherited by models such as **Linear Regression** and **Ridge Regression**.

## Expected Structure

```cpp
class BaseRegressor {
public:
    virtual void fit(const Matrix& X, const Vector& y) = 0;

    virtual Vector predict(const Matrix& X) const = 0;

    virtual ~BaseRegressor() {}
};
```

## Purpose in the Project

The main purpose of this interface is to ensure that all regression models follow the same structure. This will make it easier for the team to add, test, and compare different regression algorithms.

In the overall Ridge Regression project, the `BaseRegressor` interface will act as the foundation for the regression models, including the Linear Regression baseline and Ridge Regression.

 Next Week Plan: Code primary model prediction routines executing targeted mathematical dot product transformations (ŷ = Xθ + b).
## Week 1 repository-to-code cross-check

**Reporting period:** 28 September-5 October 2026.  
**Assigned area:** Regressor interface and prediction.

The available Git history contains no project commits during this reporting period; its earliest project commits are dated 11 October. This report therefore preserves the member's original Week 1 note as a record of the activity they reported, but does not attribute an HPP, CPP, or test implementation to Week 1 based on Git evidence. Add any work completed offline with the matching file or other evidence before submission.

## Files to prepare for the next merge

- include/ridge_ml/regressor.hpp, src/regressor.cpp, tests/test_regressor.cpp
- The member should commit the header, implementation, and focused tests together when the module is ready, then request review from the dependent module owners.

## AI Use

- Tool: OpenAI Codex.
- Purpose: organize this repository cross-check and proposed file list.
- Reason: make the report distinguish member-reported activity from tracked code evidence. This does not assert that the named member used AI for their Week 1 work; the member should verify and complete their own AI declaration.

