# Week 3 Individual Progress Report

**Name:** Ssemwogerere Othman  
**Assigned module:** Model evaluation metrics  
**Reporting period:** 13–19 October 2026

## Completed / shared code status

- The repository contains `RegressionMetrics` declarations in `include/Group-7-project-ridge-lib/metrics.hpp` and definitions in `src/metrics.cpp` for mean absolute error, mean squared error, root mean squared error, and R².
- The metric functions validate that vectors have equal, non-zero lengths.
- The available Git evidence does not establish which individual authored those shared files; this report records the current module state without attributing unverified authorship.

## In progress

- Dedicated tests for normal and edge cases were still needed at the end of the reporting period.

## Next work

- Add a CTest target covering numeric results, invalid lengths/empty inputs, and constant-target R² behavior.
