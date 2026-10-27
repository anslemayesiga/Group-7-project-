#pragma once

#ifndef GROUP_7_PROJECT_RIDGE_LIB_MATRIX_HPP
#define GROUP_7_PROJECT_RIDGE_LIB_MATRIX_HPP

#include <cstddef>
#include <vector>

namespace ridge_ml {

using Vector = std::vector<double>;

// A bounds-checked, row-major matrix used by the regression algorithms.
class Matrix {
public:
    // Empty default matrix; use a dimensioned constructor for storage.
    Matrix() = default;
    // Create a filled matrix or take ownership of row-major values.
    Matrix(std::size_t rows, std::size_t cols, double fill = 0.0);
    Matrix(std::size_t rows, std::size_t cols, std::vector<double> values);

    // Build a square matrix with ones on its diagonal.
    static Matrix identity(std::size_t size);

    // Report the stored shape without modifying the matrix.
    std::size_t rows() const noexcept;
    std::size_t cols() const noexcept;

    // Access one element; both overloads throw when indices are out of range.
    double& operator()(std::size_t row, std::size_t col);
    const double& operator()(std::size_t row, std::size_t col) const;

    // Return new matrices; the original operands are left unchanged.
    Matrix transpose() const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    // Multiply this matrix by a vector whose length equals cols().
    Vector multiply(const Vector& vector) const;

    // Return copies of one row or column.
    Vector column(std::size_t col) const;
    Vector row(std::size_t row) const;

private:
    std::size_t rows_ = 0;
    std::size_t cols_ = 0;
    std::vector<double> values_;

    std::size_t index(std::size_t row, std::size_t col) const;
};

Matrix operator*(double scalar, const Matrix& matrix);
// Compute the sum of elementwise products after checking equal vector lengths.
double dot(const Vector& left, const Vector& right);

} // namespace ridge_ml

#endif // GROUP_7_PROJECT_RIDGE_LIB_MATRIX_HPP
