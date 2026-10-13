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
