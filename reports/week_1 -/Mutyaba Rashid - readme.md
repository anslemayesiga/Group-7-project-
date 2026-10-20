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
