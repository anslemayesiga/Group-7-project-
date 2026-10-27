# Week 2 Individual Progress Report

**Name:** Ayesiga Anslem  
**Assigned module:** Matrix and vector operations  
**Reporting period:** 6-12 October 2026  


## Completed / repository evidence

- Git records initial Matrix header, demo program, and test draft in commits 8104fec, a153e70, and 88dd54e on 11 October. The header declared matrix operations, but the source file at the Week 2 checkpoint was a demo with main(), not the Matrix method implementation. The test draft was later removed during the refactor; tests/tests_matrix.cpp in the latest upstream tree is empty.

## In Progress

- The API and demo were started. Matrix method definitions and durable unit tests were still required at the end of the period.

## Challenges/Blockers

- Dependent modules need a stable Matrix API. The header's legacy path and missing implementation/test file blocked integration.

## Next Week - files to merge

- include/ridge_ml/matrix.hpp; src/matrix.cpp with method definitions; tests/tests_matrix.cpp. Confirm the tests remain in the repository after merge.



## Transferred responsibilities previously assigned to Tumweheire Desire

The following note preserves the prior member record as a handover reference; it does not claim that Ayesiga Anslem completed the earlier work:

# Week 2 Individual Progress Report

**Name:** Tumweheire Desire  
**Assigned module:** Gradient descent  
**Reporting period:** 6-12 October 2026  
**Evidence basis:** available Git history and existing member notes through 17 October.

> Draft prepared from the available records. No commit in Git does not prove no offline work occurred. The named member should verify the record and add or correct any work done outside the repository before submission.

## Completed / repository evidence

- No Week 2 individual progress report or gradient-descent HPP/CPP/test commit is present in the available repository history.

## In Progress

- No code activity can be verified for the assigned optimizer during this period. This means the report is incomplete, not that the member did no work.

## Challenges/Blockers

- Gradient descent depends on stable matrix, cost, and model interfaces. The member should add evidence for any work done outside Git.

## Next Week - files to merge

- include/ridge_ml/gradient_descent.hpp, src/gradient_descent.cpp, tests/test_gradient_descent.cpp. Commit the update rule, convergence/stopping policy, and focused tests together.


