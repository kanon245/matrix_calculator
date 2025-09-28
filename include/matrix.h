#pragma once
typedef struct {
 double** data; // Указатель на двумерный массив
 int rows; // Количество строк
 int cols; // Количество столбцов
} Matrix;
// Базовые функции
Matrix create_matrix(int rows, int cols);
void free_matrix(Matrix m);
Matrix matrix_add(Matrix a, Matrix b);
Matrix matrix_multiply(Matrix a, Matrix b);
Matrix matrix_transpose(Matrix m);
// Вспомогательные функции
void print_matrix(Matrix m);
Matrix matrix_from_array(double* data, int rows, int cols);
// Индивидуальное задание (нормализация матрицы)
Matrix matrix_normalize(Matrix m);
