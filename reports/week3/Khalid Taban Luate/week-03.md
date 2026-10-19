# Week 3 Individual Progress Report

**Name:** Khalid Taban Luate  
**Assigned module:** Normal equation and linear solvers  
**Reporting period:** 13-19 October 2026 (status as of 17 October)

## Completed / repository evidence
- Commits `64a8043` and `77e547b` added the initial structural file implementations (`include/ridge_ml/normal_equation.hpp` and `src/normal_equation.cpp`).
- Completed the core mathematical logic for Gaussian elimination with partial pivoting layouts and the unregularized closed-form normal equation system.

## In Progress
- Refactoring the legacy free namespace functions into a structured, defensive Object-Oriented C++ Class model (`NormalSolver`). This change is required to properly support the library's master inheritance architecture and isolate internal helper logic.
- Building explicit validation loops protecting the solver from dimension-mismatched data arrays.

## Challenges/Blockers
- The original source used outdated header paths and a legacy Matrix namespace representation; this was resolved during the team's shared checkout integration phase.
- Adapting free function code blocks to cleanly leverage standard Object-Oriented paradigms (Inheritance and Encapsulation) requested by the course rubric.

## Next Week - files to merge
- Implement dedicated mock testing fixtures verifying triangulation calculations, row-swapping validations, and singular matrix exception handling behavior.
- Formally connect the refactored class boundaries to Person 4's regression base models.

## AI Use
- **OpenAI Codex (17 October):** Evaluated repository states and aligned global file structural routes across shared modules.
- **ChatGPT-4o (19 October):** Drafted defensive Class interface wrappers and structured the documentation mapping out Object-Oriented associations for the Week 3 report.

## Week 3 shared code status
The current working directory contains `include/Group-7-project-ridge-lib/normal_equation.hpp` and `src/normal_equation.cpp`. Code bases have been fully updated to bind directly with the centralized Matrix container API definitions.

## OOP Concepts and Class Layout (Week 3)

### 1. Encapsulation
The codebase is being migrated from free functions into a dedicated `NormalSolver` class pattern. This encapsulates the complex linear algebra loops:
- **Private Specifier (`private`):** Internal structural manipulations like row-swapping indices and pivoting factor evaluations are hidden from external view inside `solve_linear_system`.
- **Public Specifier (`public`):** Other group modules can access the solver safely through the single clean entry pipeline: `solve_normal_equation(X, y)`.

### 2. Polymorphism and Inheritance
While the solver works as a targeted mathematical processing block, it operates in direct service to the library's master polymorphism hierarchy:
- The base parent class (`Regressor`) outlines the abstract virtual function `virtual void fit(Matrix& X, Matrix& y) = 0;`.
- The child structures (`LinearRegression` and `RidgeRegression`) inherit from the parent and call your encapsulated solver class to resolve parameters based on their respective mathematical requirements (unregularized vs. L2-regularized criteria).
