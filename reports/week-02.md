
Week 2 Individual Progress Report

Member Name: Wobusobozi Chrispus Owen
Registration Number: 25/U/0860 BELE
Assigned Feature Group: Dataset Loading & Data Preprocessing
Reporting Period: 5th October to 12th October 2026

 1. Core Engineering Status

• Status: COMPLETED & VERIFIED 
• Assigned Modules Implemented:
	• include/ridgelib/dataset.hpp
	• src/dataset.cpp
	• include/ridgelib/preprocessing.hpp
	• src/preprocessing.cpp
	• tests/test_dataset.cpp

 2. Work Completed This Week


Data Loading Engine (dataset.cpp)

• Implemented a robust file stream parser using std::ifstream and std::stringstream to read external data records line by line.
• Designed a feature extraction loop utilizing std::getline and string-to-double conversion (std::stod) to separate raw training matrices from target prediction vectors (splitting the final column into array y).
• Developed a high-performance trainTestSplit feature module that shuffles inputs using a fixed-seed pseudorandom engine (std::mt19937) to guarantee consistent cross-validation sets across teammate environments.

Data Preprocessing Engine (preprocessing.cpp)

• Coded an automated imputation engine to handle dirty or corrupted matrix inputs safely.
• Designed a two-pass column scanning algorithm:
	• Pass 1: Iterates through individual features, screening for missing value elements, infinity limits, or placeholder anomalies (0.0), and calculates the true mean average of valid signals.
	• Pass 2: Dynamically overwrites data corruptions using the computed feature column average to prevent runtime matrix calculations from collapsing downstream.

Automated Unit Testing Suite (test_dataset.cpp)
• Created an autonomous test runner executable linked inside CMakeLists.txt to isolate and evaluate my modules.
• Built standard unit tests that explicitly verified structural mean replacements and invalid parameter input boundaries.
• Successfully compiled and ran the binary in the local VS Code workspace, with all layers resolving to a verified PASSED state.

 3. Challenges Addressed & Resolved

• Challenge: Encountered broken header search patterns (#include "ridgelib/preprocessing.hpp") due to an irregular local repository directory title string format (include \ ridge_ml).
• Resolution: Re-architected local files using a standard lowercase structure (include/ridgelib/), modified trailing file path strings, and updated target link pointers within CMakeLists.txt to successfully resolve IntelliSense and compiler flags.

 4. Objectives For Next Week (Week 3)

• Coordinate directly with Kyelanyi Martin Tom to pipe my clean, loaded feature matrices into the Feature Scaling Engine for Z-score and Min-Max standardization normalization loops.
• Support integration testing to ensure that the core data tracking containers pass seamlessly into the array-multiplication layers of the main linear algebra models.

 5. AI Use Declaration

• Tool: Gemini
• Purpose: Assisted in debugging the directory structural conflict and generating a boilerplate structural baseline blueprint for the row tokenization logic.
• Reason: Allowed rapid resolution of standard C++ standard-library file stream operations, ensuring the project directory format perfectly mirrors the course specification sheet.