#pragma once
#include <array>
#include <ostream>
#include <iomanip>
#include <cassert>

namespace math
{
    template<unsigned int rows, unsigned int cols>
    class Matrix {
    public:
        std::array<std::array<double, cols>, rows> _matrix{};

        Matrix(bool identity = false) {
            for (unsigned int i = 0; i < rows; i++)
                for (unsigned int j = 0; j < cols; j++)
                    _matrix[i][j] = 0.0;
        
            if (rows == cols && identity) {
                for (unsigned int i = 0; i < rows; i++)
                    _matrix[i][i] = 1.0;
            }
        }

        Matrix(const std::array<std::array<double, cols>, rows>& mat)
            : _matrix(mat) {}

        ~Matrix() = default;

        double operator()(unsigned int row, unsigned int col) const {
            assert(row < rows && col < cols);
            return _matrix[row][col];
        }

        double& operator()(unsigned int row, unsigned int col) {
            assert(row < rows && col < cols);
            return _matrix[row][col];
        }

        template <unsigned int c2>
        Matrix<rows, c2> operator*(const Matrix<cols, c2>& other) const {
            Matrix<rows, c2> result(false);
            for (unsigned int i = 0; i < rows; i++)
                for (unsigned int j = 0; j < c2; j++)
                    for (unsigned int k = 0; k < cols; k++)
                        result._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
            return result;
        }

        template <unsigned int c2>
        Matrix<rows, c2>& operator*=(const Matrix<cols, c2>& other) {
            *this = (*this) * other;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& os, const Matrix<rows, cols>& mat) {
            os << std::fixed << std::setprecision(3) << "[\n";
            for (unsigned int i = 0; i < rows; i++) {
                os << "  [ ";
                for (unsigned int j = 0; j < cols; j++)
                    os << mat._matrix[i][j] << (j + 1 < cols ? ", " : " ");
                os << "]\n";
            }
            os << "]";
            return os;
        }
    };
}
