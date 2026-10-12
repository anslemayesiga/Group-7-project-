
// Owner: Ayesiga Anslem (Matrix and vector operations)
#include <cstddef>
#include <vector>

namespace ridge {

/// Vectors are plain std::vector<double> (group decision: keep it simple).
using Vector = std::vector<double>;

/// Dense row-major matrix of doubles.
/// All operations must throw std::invalid_argument on dimension mismatch
/// and std::out_of_range on bad indices.
class Matrix {
public:
    Matrix() = default;
    Matrix(std::size_t rows, std::size_t cols, double fill = 0.0);
    /// data must have rows*cols elements, row-major order.
    Matrix(std::size_t rows, std::size_t cols, std::vector<double> data);

    static Matrix identity(std::size_t n);

    std::size_t rows() const;
    std::size_t cols() const;

    double& operator()(std::size_t r, std::size_t c);
    const double& operator()(std::size_t r, std::size_t c) const;

    Matrix transpose() const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;  // matrix product
    Matrix operator*(double scalar) const;
    Vector multiply(const Vector& v) const;       // matrix * vector

    Vector column(std::size_t c) const;
    Vector row(std::size_t r) const;

private:
    std::size_t rows_ = 0, cols_ = 0;
    std::vector<double> data_;
};

double dot(const Vector& a, const Vector& b);

}  // namespace ridge
