# Week 2 Individual Progress Report

**Name:** Ssemwogerere Othman  
**Assigned module:** Model evaluation metrics  
**Reporting period:** 6–12 October 2026

## Completed

- The responsibility plan identifies model evaluation metrics as the assigned module.

## In progress / repository evidence

- No metrics header, implementation, or focused test is recorded in the repository for this reporting period.
- The planned API was `include/Group-7-project-ridge-lib/metrics.hpp` and `src/metrics.cpp`, with tests to follow.

## Challenges

- The metrics module depends on the shared vector type and prediction outputs being consistent across models.

 SSEMWOGERERE-OTHMAN
- The metrics API needs to agreed prediction/target types and must integrate with the baseline and ridge model outputs. Add evidence for any offline work.

## Next Week - files to merge

- include/ridge_ml/metrics.hpp, src/metrics.cpp, tests/test_metrics.cpp. Agree metric names and invalid-input behavior, then merge implementation and test
## Next workmain

- Implement and test MAE, MSE, RMSE, and R² using matching, non-empty target and prediction vectors.
