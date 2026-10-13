#pragma once                       // 1. include guard: prevents double inclusion
#include <cstddef>                 // 2. std::size_t
#include <vector>                  //    std::vector

namespace ridge {                  // 3. everything lives in the ridge namespace

using Vector = std::vector<double>;   // 4. a Vector is just a vector of doubles

class Matrix {
public:                            // 5. the public API users can call
    Matrix() = default;                                        // empty 0x0 matrix
    Matrix(std::size_t rows, std::size_t cols, double fill = 0.0);
    Matrix(std::size_t rows, std::size_t cols, std::vector<double> data);

    static Matrix identity(std::size_t n);                     // Matrix::identity(3)

    std::size_t rows() const;
    std::size_t cols() const;

    double& operator()(std::size_t r, std::size_t c);          // read and write: m(1,2) = 5
    const double& operator()(std::size_t r, std::size_t c) const;  // read-only version

    Matrix transpose() const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;               // matrix product
    Matrix operator*(double scalar) const;
    Vector multiply(const Vector& v) const;                    // matrix times vector

    Vector column(std::size_t c) const;
    Vector row(std::size_t r) const;

private:                           // 6. internal data, hidden from users
    std::size_t rows_ = 0, cols_ = 0;
    std::vector<double> data_;     // all elements in one flat array, row by row
};

double dot(const Vector& a, const Vector& b);   // 7. free function, outside the class

}  // namespace ridge