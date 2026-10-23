#pragma once

#ifndef GROUP_7_PROJECT_RIDGE_LIB_MATRIX_HPP
#define GROUP_7_PROJECT_RIDGE_LIB_MATRIX_HPP

#include <cstddef>
#include <vector>

namespace ridge_ml {

using Vector = std::vector<double>;

class Matrix {
public:
    Matrix() = default;
    Matrix(std::size_t rows, std::size_t cols, double fill = 0.0);
    Matrix(std::size_t rows, std::size_t cols, std::vector<double> values);

    static Matrix identity(std::size_t size);

    std::size_t rows() const noexcept;
    std::size_t cols() const noexcept;

    double& operator()(std::size_t row, std::size_t col);
    const double& operator()(std::size_t row, std::size_t col) const;

    Matrix transpose() const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Vector multiply(const Vector& vector) const;

    Vector column(std::size_t col) const;
    Vector row(std::size_t row) const;

private:
    std::size_t rows_ = 0;
    std::size_t cols_ = 0;
    std::vector<double> values_;

    std::size_t index(std::size_t row, std::size_t col) const;
};

Matrix operator*(double scalar, const Matrix& matrix);
double dot(const Vector& left, const Vector& right);

} // namespace ridge_ml

#endif // GROUP_7_PROJECT_RIDGE_LIB_MATRIX_HPP

