#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <concepts>
#include <ostream>
#include <vector>
#include <iomanip>
#include <random>
#include <cassert>
#include <span>

#include "MatrixView.hpp"

namespace matrix {

// The type T can only be a number floating-point type
template <std::floating_point T>
class Matrix
{
private:
    std::vector<T> _matrix;
    size_t _rows;
    size_t _cols;

    // PseudoRandom engine, common to all instances
    static inline std::mt19937 _gen{std::random_device{}()};

public:
    // Def constructor
    Matrix() = delete;

    // Quadratic matrix constructor
    explicit Matrix(size_t size)
        : _matrix(size * size, 0.0), _rows(size), _cols(size)
    {
    }

    // Rectangular matrix constructor
    explicit Matrix(int num_rows, int num_cols)
        : _matrix(num_rows * num_cols, 0.0), _rows(num_rows), _cols(num_cols)
    {
    }

    // Descructor
    ~Matrix() = default;

    // Copy constructor
    Matrix(const Matrix& other)
        : _matrix(other._matrix), _rows(other._rows), _cols(other._cols)
    {
    }

    // Operator=
    Matrix& operator=(Matrix other) { // Value-Passing
        this->swap(other);
        return *this;
    }

    // Swap function
    void swap(Matrix& other) noexcept {
        using std::swap;
        swap(this->_matrix, other->_matrix);
        swap(this->_cols, other->_cols);
        swap(this->_rows, other->_rows);
    }

    // Operator() get only one member
    // It returns a reference of the "logic" cell
    // It transforms the 1D vector to a 2D logic
    // matrix, by indexing
    // IMP: it checks the bound only with an assert
    T& operator()(size_t i, size_t j) {
        assert(i < _rows && j < _cols && "Matrix indices out of bounds!");
        return _matrix[i * _cols + j];
    }

    // For const matrix
    // IMP: it checks the bound only with an assert
    const T& operator()(size_t i, size_t j) const {
        assert(i < _rows && j < _cols && "Matrix indices out of bounds!");
        return _matrix[i * _cols + j];
    }

    // Fill the matrix with pseudo-random number
    void fillMatrix(T min = 0.0, T max = 10.0) {
        std::uniform_real_distribution<T> dis(min, max);
        for (auto& x : _matrix) {
            x = dis(_gen);
        }
    }

    // size
    std::pair<size_t, size_t> size() const {
        return {_rows, _cols};
    }

    // getRow
    std::span<T> getRow(size_t index) {
        assert(index < _rows);

        // pointer + size constructor
        return std::span<T>(
                _matrix.data() + index * _cols,
                _cols
            );
    }

    // const
    std::span<const T> getRow(size_t index) const {
        assert(index < _rows);

        return std::span<const T>(
            _matrix.data() + index * _cols,
            _cols
            );
    }

    // getColumn
    matrix::MatrixView<T> getColumn(size_t index) {
        assert(index < _cols);

        return matrix::MatrixView<T>(_matrix.data() + index, _rows, 1, _cols);

    }

    matrix::MatrixView<const T> getColumn(size_t index) const {
        assert(index < _cols);

        return matrix::MatrixView<T>(_matrix.data() + index, _rows, 1, _cols);

    }

    // getBlock
    matrix::MatrixView<T> getBlock(size_t row_index, size_t col_index, size_t height, size_t width) {
        assert(row_index + height <= _rows);
        assert(col_index + width  <= _cols);

        return matrix::MatrixView<T>(_matrix.data() + row_index * _cols + col_index,
                             height, width, _cols);
    }

    matrix::MatrixView<const T> getBlock(size_t row_index, size_t col_index, size_t height, size_t width) const{
        assert(row_index + height <= _rows);
        assert(col_index + width  <= _cols);

        return matrix::MatrixView<T>(_matrix.data() + row_index * _cols + col_index,
                             height, width, _cols);
    }


    // operator+
    Matrix operator+(const Matrix& other) const {
        if (_cols != other._cols || _rows != other._rows) {
            throw std::invalid_argument("Matrix dimensions must be the same");
        }

        Matrix result(_rows, _cols);

        //Without parallelization
        for (size_t i = 0; i < _matrix.size(); ++i) {
            result._matrix[i] = _matrix[i] + other._matrix[i];
        }


        return result;

    }

    // operator*

    // transpose
    Matrix transpose(Matrix& matrix) {

    }

    // inverse

    // identity

    // tril

    // triu

    // Operator << directly inside the class
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
        // Save other cout precision to reset after
        auto old_precision = os.precision();

        os << "[" << std::fixed << std::setprecision(4); // 4 decimals

        for (size_t i = 0; i < matrix._rows; ++i) {
            os << "\n  ";
            for (size_t j = 0; j < matrix._cols; ++j) {
                // std::setw(10) create a 10 char column
                os << std::setw(10) << matrix(i, j) << " ";
            }
        }

        os << "\n]";

        // Reset precision
        os.precision(old_precision);
        os << std::defaultfloat;

        return os;
    }
};

} // namespace matrix

// To print row simply
template <typename T>
std::ostream& operator<<(std::ostream& os, std::span<T> s) {
    os << "[ ";
    for (const auto& x : s) {
        os << x << " ";
    }
    os << "]";
    return os;
}


#endif // MATRIX_HPP
