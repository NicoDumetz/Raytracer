/*
** EPITECH PROJECT, 2025
** Matrix.hpp
** File description:
** Project
*/

#pragma once
#include <array>
#include <ostream>

namespace math
{
    template<unsigned int rows, unsigned int cols> class Matrix
    {
    public:
        std::array<std::array<double, cols>, rows> _matrix;

        Matrix(std::array<std::array<double, cols>, rows> matrix) {
            this->_matrix = matrix;
        };
        Matrix() {
            for (unsigned int i = 0; i < rows; i++)
                for (unsigned int j = 0; j < cols; j++)
                    if (i == j)
                        this->_matrix[i][j] = 1;
                    else
                        this->_matrix[i][j] = 0;
        }
        ~Matrix() = default;
        double operator()(unsigned int row, unsigned int col) const {
            return _matrix[row][col];
        }
        double &operator()(unsigned int row, unsigned int col) {
            return _matrix[row][col];
        }
        template <unsigned int c2>
        Matrix<rows, c2> operator*(const Matrix<cols, c2> &other) const {
            Matrix<rows, c2> newMatrix;
            for (unsigned int i = 0; i < rows; i++)
                for (unsigned int j = 0; j < c2; j++) {
                    for (unsigned int k = 0; k < cols; k++)
                        newMatrix._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
                }
            return newMatrix;
        }
        template <unsigned int c2>
        Matrix<rows, c2> &operator*=(const Matrix<cols, c2> &other) {
            Matrix<rows, c2> newMatrix;
    
            for (unsigned int i = 0; i < rows; i++)
                for (unsigned int j = 0; j < c2; j++) {
                    for (unsigned int k = 0; k < cols; k++)
                        newMatrix._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
                }
            *this = newMatrix;
            return *this;
        }
    };
    template <unsigned int rows, unsigned int cols>
    std::ostream &operator<<(std::ostream &os, const Matrix<rows, cols> &matrix) {
        os << "[";
        for (unsigned int i = 0; i < rows; i ++) {
            os << "[";
            for (unsigned int j = 0; j < cols; j ++) {
                os << matrix._matrix[i][j];
                if (j + 1 < cols)
                    os << ", ";
            }
            os << "]";
            if (i + 1 < rows)
                os << ", ";
        }
        os << "]";
        return os;
    };
} // namespace math
