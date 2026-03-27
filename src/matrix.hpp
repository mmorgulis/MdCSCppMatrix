#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstring>
#include <ostream>
#include <vector>
#include <iomanip>
#include <random>
#include <cassert>
#include <span>
#include <type_traits>

#include "MatrixView.hpp"

namespace matrix {

template <typename T>
requires std::is_arithmetic_v<T>
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
        : Matrix(size, size)
    {
    }

    // Rectangular matrix constructor
    Matrix(size_t num_rows, size_t num_cols)
        : _matrix(num_rows * num_cols, T{0}), _rows(num_rows), _cols(num_cols)
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
    Matrix& operator=(Matrix other) noexcept { // Value-Passing
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

    // FACTORY METHODS
    // identity
    static Matrix identity(size_t n) {
        Matrix I(n, n);
        for (size_t i = 0; i < n; ++i) {
            I(i, i) = T{1};
        }
        return I;
    }

    static Matrix zeros(size_t rows, size_t cols) {
        Matrix m(rows, cols);
        m.fill(T{0});
        return m;
    }

    static Matrix ones(size_t rows, size_t cols) {
        Matrix m(rows, cols);
        m.fill(T{1});
        return m;
    }

    static Matrix random(size_t rows, size_t cols, T min = T{0}, T max = T{10}) {
        Matrix m(rows, cols);
        m.fillRandom(min, max);
        return m;
    }

    static Matrix zeros(size_t n) { return zeros(n, n); }
    static Matrix ones(size_t n)  { return ones(n, n); }
    static Matrix random(size_t n, T min = T{0}, T max = T{10}) {
        return random(n, n, min, max);
    }

    // Operator() get only one member
    // It returns a reference of the "logic" cell
    // It transforms the 1D vector to a 2D logic
    // matrix, by indexing
    // IMP: it checks the bound only with an assert
    T& operator()(size_t i, size_t j) noexcept {
        assert(i < _rows && j < _cols && "Matrix indices out of bounds!");
        return _matrix[i * _cols + j];
    }

    // For const matrix
    // IMP: it checks the bound only with an assert
    const T& operator()(size_t i, size_t j) const noexcept {
        assert(i < _rows && j < _cols && "Matrix indices out of bounds!");
        return _matrix[i * _cols + j];
    }

    // Fill the matrix with pseudo-random number
    void fillRandom(T min = T{0}, T max = T{10}) {
        if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> dis(min, max);
            for (auto& x : _matrix) x = dis(_gen);
        } else {
            std::uniform_int_distribution<T> dis(min, max);
            for (auto& x : _matrix) x = dis(_gen);
        }
    }

    // Fill the matrix with one value
    void fill(const T& value) {
        std::fill(_matrix.begin(), _matrix.end(), value);
    }

    // size
    std::pair<size_t, size_t> size() const noexcept {
        return {_rows, _cols};
    }

    // getRow
    std::span<T> getRow(size_t index) noexcept {
        assert(index < _rows);

        // pointer + size constructor
        return std::span<T>(
                _matrix.data() + index * _cols,
                _cols
            );
    }

    // const
    std::span<const T> getRow(size_t index) const noexcept {
        assert(index < _rows);

        return std::span<const T>(
            _matrix.data() + index * _cols,
            _cols
            );
    }

    // getColumn
    matrix::MatrixView<T> getColumn(size_t index) noexcept {
        assert(index < _cols);

        return matrix::MatrixView<T>(_matrix.data() + index, _rows, 1, _cols);

    }

    matrix::MatrixView<const T> getColumn(size_t index) const noexcept {
        assert(index < _cols);

        return matrix::MatrixView<const T>(_matrix.data() + index, _rows, 1, _cols);

    }

    // getBlock
    matrix::MatrixView<T> getBlock(size_t row_index, size_t col_index, size_t height, size_t width) noexcept {
        assert(row_index + height <= _rows);
        assert(col_index + width  <= _cols);

        return matrix::MatrixView<T>(_matrix.data() + row_index * _cols + col_index,
                             height, width, _cols);
    }

    matrix::MatrixView<const T> getBlock(size_t row_index, size_t col_index, size_t height, size_t width) const noexcept {
        assert(row_index + height <= _rows);
        assert(col_index + width  <= _cols);

        return matrix::MatrixView<const T>(_matrix.data() + row_index * _cols + col_index,
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
    // simple implementation (no parallelization, no simd
    // only the localitation trick with transpose)
    template <typename U>
    auto operator*(const Matrix<U>& other) const {
        // Choose beetween types
        using ResultType = std::common_type_t<T, U>;

        if (_cols != other._rows) {
            throw std::invalid_argument("Invalid matrix dimensions");
        }

        Matrix<ResultType> result(_rows, other._cols);
        auto transposed = other.transpose();

        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < other._cols; ++j) {

                T sum = T{0};

                for (size_t k = 0; k < _cols; ++k) {
                    sum += (*this)(i, k) * transposed(j, k);
                }

                result(i, j) = sum;
            }
        }

        return result;
    }

    // transpose
    Matrix transpose() const noexcept {
        Matrix transposed(_cols, _rows); // not really necessary
        for (size_t i = 0; i < _cols; ++i) {
            for (size_t j = 0; j < _rows; ++j) {
                transposed(i, j) = (*this)(j, i);
            }
        }
        return transposed;
    }

    /** The function returns the upper
     *  triangular of the matrix passed
     *  by this
     **/
    Matrix triu() const noexcept {
        // For every row
        Matrix result(*this);
        for (size_t i = 0; i < result._rows; ++i) {
            size_t limit = std::min(i, result._cols);
            std::fill(result._matrix.begin() + (i * result._cols),
                      result._matrix.begin() + (i * result._cols) + limit,
                      T{0});
        }
        return result;
    }

    /** The function returns the lower
     *  triangular of the matrix passed
     *  by this
     **/
    Matrix tril() const noexcept {
        Matrix result(*this);

        for (size_t i = 0; i < result._rows; ++i) {
            if (i + 1 < result._cols) {
                std::fill(result._matrix.begin() + (i * result._cols) + (i + 1),
                          result._matrix.begin() + (i * result._cols) + result._cols,
                          T{0});
            }
        }

        return result;
    }

    // INVERSE


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
