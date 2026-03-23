#ifndef MATRIXVIEW_HPP
#define MATRIXVIEW_HPP
#include <concepts>
#include <memory>

namespace matrix {

template<std::floating_point T>
class MatrixView {
private:
    T* _data; // starting_point to read the data
    size_t _rows;
    size_t _cols;
    // # original matrix column,
    // so the distance between vertical elements
    size_t _stride;


public:
    MatrixView() = delete;

    explicit MatrixView(T* data, size_t rows, size_t cols, size_t stride)
        : _data(data), _rows(rows), _cols(cols), _stride(stride)
    {
    }

    T& operator()(size_t i, size_t j) {
        return _data[i * _stride + j];
    }

    const T& operator()(size_t i, size_t j) const {
        return _data[i * _stride + j];
    }

    size_t rows() const { return _rows; }
    size_t cols() const { return _cols; }

    // Operator << directly inside the class
    friend std::ostream& operator<<(std::ostream& os, const MatrixView<T>& matrixView) {
        // Save other cout precision to reset after
        auto old_precision = os.precision();

        os << "[" << std::fixed << std::setprecision(4); // 4 decimals

        for (size_t i = 0; i < matrixView._rows; ++i) {
            os << "\n  ";
            for (size_t j = 0; j < matrixView._cols; ++j) {
                // std::setw(10) create a 10 char column
                os << std::setw(10) << matrixView(i, j) << " ";
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

#endif // MATRIXVIEW_HPP
