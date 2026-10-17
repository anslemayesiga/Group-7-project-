#include "Group-7-project-ridge-lib/matrix.hpp"

#include <limits>
#include <stdexcept>
#include <utility>

namespace ridge_ml {

namespace {
std::size_t checked_element_count(std::size_t rows, std::size_t cols) {
    if (cols != 0 && rows > std::numeric_limits<std::size_t>::max() / cols) {
        throw std::length_error("Matrix dimensions are too large");
    }
    return rows * cols;
}
} // namespace

Matrix::Matrix(std::size_t rows, std::size_t cols, double fill)
    : rows_(rows), cols_(cols), values_(checked_element_count(rows, cols), fill) {}

Matrix::Matrix(std::size_t rows, std::size_t cols, std::vector<double> values)
    : rows_(rows), cols_(cols), values_(std::move(values)) {
    if (values_.size() != checked_element_count(rows_, cols_)) {
        throw std::invalid_argument("Matrix data size does not match its dimensions");
    }
}

Matrix Matrix::identity(std::size_t size) {
    Matrix result(size, size);
    for (std::size_t i = 0; i < size; ++i) {
        result(i, i) = 1.0;
    }
    return result;
}

std::size_t Matrix::rows() const noexcept { return rows_; }
std::size_t Matrix::cols() const noexcept { return cols_; }

std::size_t Matrix::index(std::size_t row, std::size_t col) const {
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Matrix index is out of range");
    }
    return row * cols_ + col;
}

double& Matrix::operator()(std::size_t row, std::size_t col) {
    return values_[index(row, col)];
}

const double& Matrix::operator()(std::size_t row, std::size_t col) const {
    return values_[index(row, col)];
}

Matrix Matrix::transpose() const {
    Matrix result(cols_, rows_);
    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t j = 0; j < cols_; ++j) {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrix addition requires equal dimensions");
    }
    Matrix result(rows_, cols_);
    for (std::size_t i = 0; i < values_.size(); ++i) {
        result.values_[i] = values_[i] + other.values_[i];
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrix subtraction requires equal dimensions");
    }
    Matrix result(rows_, cols_);
    for (std::size_t i = 0; i < values_.size(); ++i) {
        result.values_[i] = values_[i] - other.values_[i];
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Matrix multiplication dimension mismatch");
    }
    Matrix result(rows_, other.cols_);
    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t k = 0; k < cols_; ++k) {
            const double left = (*this)(i, k);
            for (std::size_t j = 0; j < other.cols_; ++j) {
                result(i, j) += left * other(k, j);
            }
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows_, cols_);
    for (std::size_t i = 0; i < values_.size(); ++i) {
        result.values_[i] = values_[i] * scalar;
    }
    return result;
}

Vector Matrix::multiply(const Vector& vector) const {
    if (cols_ != vector.size()) {
        throw std::invalid_argument("Matrix-vector multiplication dimension mismatch");
    }
    Vector result(rows_, 0.0);
    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t j = 0; j < cols_; ++j) {
            result[i] += (*this)(i, j) * vector[j];
        }
    }
    return result;
}

Vector Matrix::column(std::size_t col_index) const {
    if (col_index >= cols_) {
        throw std::out_of_range("Matrix column is out of range");
    }
    Vector result(rows_);
    for (std::size_t i = 0; i < rows_; ++i) {
        result[i] = (*this)(i, col_index);
    }
    return result;
}

Vector Matrix::row(std::size_t row_index) const {
    if (row_index >= rows_) {
        throw std::out_of_range("Matrix row is out of range");
    }
    Vector result(cols_);
    for (std::size_t j = 0; j < cols_; ++j) {
        result[j] = (*this)(row_index, j);
    }
    return result;
}

Matrix operator*(double scalar, const Matrix& matrix) {
    return matrix * scalar;
}

double dot(const Vector& left, const Vector& right) {
    if (left.size() != right.size()) {
        throw std::invalid_argument("Dot product requires vectors of equal length");
    }
    double result = 0.0;
    for (std::size_t i = 0; i < left.size(); ++i) {
        result += left[i] * right[i];
    }
    return result;
}

} // namespace ridge_ml




