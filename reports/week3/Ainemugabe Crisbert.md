# Week 3 Individual Progress Report

**Name:** Ainemugabe Crisbert  
**Assigned module:** Hyperparameter tuning  
**Reporting period:** 13-19 October 2026 (status as of 17 October)



## Completed / repository evidence

- The Week 3 history contains updates to the Week 2 report on 13 October. No tuning HPP/CPP/test commit is present.

## In Progress

- The Week 2 note describes grid-search activity, but the tuning controller and tests are not in the repository. Treat the activity as member-reported until the files or branch are linked.

## Challenges/blockers

- Tuning depends on a working ridge estimator and evaluation metric API.

## Next Week - files to merge

- Add tests for candidate selection, empty candidates, null model factories, and validation shapes; confirm that validation R-squared is the agreed selection metric. Review the tuner. No tests were run during this follow-up.


## OOP Concepts and Class Layout (Week 3)

**Code files prepared for the assigned module:** `include/Group-7-project-ridge-lib/tuning.hpp`, `src/tuning.cpp`.

- **Encapsulation:** `GridSearchTuner` stores its model factory privately and exposes a public search method. `GridSearchResult` returns the best parameter, score, and model using public fields.
- **Runtime polymorphism:** The tuner creates and uses models through `std::unique_ptr<Regressor>`, calling virtual `fit` and `predict`. It has no inheritance relationship itself.
- **Layout to draw:** `GridSearchTuner` private `factory_`; public `ModelFactory`, constructor, and `fit`. `GridSearchResult` public `best_parameter`, `best_score`, and `best_model`. The model base is `Regressor`.
