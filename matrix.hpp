#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <concepts>
#include <ostream>
#include <vector>
#include <iomanip>
#include <random>
#include <cassert>

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
    explicit Matrix(int size)
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
    T operator()(size_t i, size_t j) const {
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

    // getColumn

    // getBlock

    // getSize

    // operator+

    // operator*

    // transpose

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



#endif // MATRIX_HPP
