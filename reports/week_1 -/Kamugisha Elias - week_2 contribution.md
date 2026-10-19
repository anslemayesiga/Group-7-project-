## Building Logging Trackers for Complete Loss-Evaluation Traces

I will build a **logging tracker** for the Linear Regression training and evaluation process. The tracker will record important values produced at each active development or training step so that we can follow how the model behaves, identify errors, and compare results as the implementation develops.

The tracker will record, where applicable:

- **Step or iteration number** — identifies the training or evaluation step.
- **Model status** — indicates whether the model is being fitted, evaluated, or has completed training.
- **Loss value** — records the selected loss metric, such as mean squared error (MSE), for the current step.
- **Parameter updates** — records relevant coefficient and intercept values when the implementation updates them.
- **Prediction and target summaries** — helps compare predicted values with actual target values.
- **Validation and error messages** — records invalid dimensions, non-finite values, singular-system errors, or attempts to predict before fitting.
- **Final evaluation summary** — reports the final loss and other evaluation metrics calculated by the project.

The logs should be consistent and easy to read, preferably including a step number and clearly labelled values. If training uses a closed-form solution rather than iterative optimization, the tracker should log the fitting start and completion, the calculated parameters, and the loss before and after fitting where meaningful. It should not invent intermediate optimization steps that do not occur in the algorithm.

## Example of a Log Trace

```text
[LinearRegression] Fit started
[LinearRegression] Samples: 100, Features: 3
[LinearRegression] Parameters calculated
[LinearRegression] Training MSE: 0.0241
[LinearRegression] Evaluation MSE: 0.0318
[LinearRegression] Fit completed successfully
```

*The values above are illustrative examples, not results from an actual dataset.*

## Purpose in the Project

These logging trackers will make the model easier to debug, test, and evaluate. They will help the team trace loss evaluation throughout development, detect unexpected results, and compare the Linear Regression baseline with Ridge Regression using the same evaluation metrics and dataset splits.


The logging functionality can be implemented inside the training and evaluation workflow or through a separate logger utility, depending on the project's shared code structure.
