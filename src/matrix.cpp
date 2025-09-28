#include "matrix.h"
#include <iostream>
#include <stdexcept>
// Создание матрицы заданного размера
Matrix create_matrix(int rows, int cols) {
 if (rows <= 0 || cols <= 0) {
 throw std::invalid_argument("Matrix dimensions must be positive");
 }

 Matrix mat;
 mat.rows = rows;
 mat.cols = cols;
 mat.data = new double*[rows];

 for (int i = 0; i < rows; i++) {
 mat.data[i] = new double[cols](); // () инициализирует нулями
 }

 return mat;
}
// Освобождение памяти матрицы
void free_matrix(Matrix m) {
 if (m.data == nullptr) return;

 for (int i = 0; i < m.rows; i++) {
 delete[] m.data[i];
 }
 delete[] m.data;
}
void print_matrix(Matrix m) {
 if (m.data == nullptr) {
 std::cout << "[Empty matrix]" << std::endl;
 return;
 }

 std::cout << "Matrix " << m.rows << "x" << m.cols << ":" << std::endl;
 for (int i = 0; i < m.rows; i++) {
 std::cout << "[ ";
 for (int j = 0; j < m.cols; j++) {
 std::cout << m.data[i][j] << " ";
 }
 std::cout << "]" << std::endl;
 }
}
// Сложение двух матриц
Matrix matrix_add(Matrix a, Matrix b) {
 // Проверка совпадения размеров
 if (a.rows != b.rows || a.cols != b.cols) {
 throw std::invalid_argument("Matrix dimensions must match foraddition");
 }

 Matrix result = create_matrix(a.rows, a.cols);

 for (int i = 0; i < a.rows; i++) {
 for (int j = 0; j < a.cols; j++) {
 result.data[i][j] = a.data[i][j] + b.data[i][j];
 }
 }

 return result;
}
// Умножение матриц
Matrix matrix_multiply(Matrix a, Matrix b) {
 // Проверка совместимости размеров
 if (a.cols != b.rows) {
 throw std::invalid_argument("Number of columns in A must equalnumber of rows in B");
 }

 Matrix result = create_matrix(a.rows, b.cols);

 for (int i = 0; i < a.rows; i++) {
 for (int j = 0; j < b.cols; j++) {
 result.data[i][j] = 0;
 for (int k = 0; k < a.cols; k++) {
 result.data[i][j] += a.data[i][k] * b.data[k][j];
 }
 }
 }

 return result;
}
// Транспонирование матрицы
Matrix matrix_transpose(Matrix m) {
 Matrix result = create_matrix(m.cols, m.rows);

 for (int i = 0; i < m.rows; i++) {
 for (int j = 0; j < m.cols; j++) {
 result.data[j][i] = m.data[i][j];
 }
 }

 return result;
}
// Создание матрицы из одномерного массива
Matrix matrix_from_array(double* data, int rows, int cols) {
 Matrix result = create_matrix(rows, cols);

 for (int i = 0; i < rows; i++) {
 for (int j = 0; j < cols; j++) {
 result.data[i][j] = data[i * cols + j];
 }
 }

 return result;
}
// Нормализация матрицы (приведение к диапазону 0-1)
Matrix matrix_normalize(Matrix m) {
    if (m.data == nullptr || m.rows == 0 || m.cols == 0) {
        throw std::invalid_argument("Matrix cannot be empty");
    }

    Matrix result = create_matrix(m.rows, m.cols);

    double min_val = m.data[0][0];
    double max_val = m.data[0][0];

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            if (m.data[i][j] < min_val) {
                min_val = m.data[i][j];
            }
            if (m.data[i][j] > max_val) {
                max_val = m.data[i][j];
            }
        }
    }

    if (min_val == max_val) {
        for (int i = 0; i < m.rows; i++) {
            for (int j = 0; j < m.cols; j++) {
                result.data[i][j] = 0.5;
            }
        }
        return result;
    }

    double range = max_val - min_val;
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            result.data[i][j] = (m.data[i][j] - min_val) / range;
        }
    }

    return result;
}
