#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <concepts>
#include <vector>

// The type T can only be a number floating-point type
template <std::floating_point T>
class Matrix
{
private:
    std::vector<T> _matrix;
    int _rows;
    int _cols;

public:
    // Def constructor
    Matrix() = delete;

    // Descructor
    ~Matrix(){

    }

    // Copy constructor
    Matrix(Matrix<T>& other) {

    }

    // Operator=
    Matrix<T>& operator=(Matrix<T>& other) {

    }

    // Operator() get only one member
    // It returns a reference of the "logic" cell
    // It transforms the 1D vector to a 2D logic
    // matrix, by indexing
    T& operator()(T first_index, T second_index) {
        return _matrix[first_index * _cols + second_index];
    }

    // Quadratic matrix constructor
    explicit Matrix(int size) {
        _rows = size;
        _cols = size;
        _matrix.reserve(size * size);
    }

    // Rectangular matrix constructor
    explicit Matrix(int num_rows, int num_cols) {
        _rows = num_rows;
        _cols = num_cols;
        _matrix.reserve(num_rows * num_cols);
    }

    // Fill the matrix with pseudo-random number
    void fillMatrix(Matrix<T>& matrix) {

    }

    // getRow

    // getColumn

    // getBlock

    // getSize


};
// Operator <<


#endif // MATRIX_HPP
