#ifndef S21_MATRIX_OOP
#define S21_MATRIX_OOP

#include <cmath>
#include <iostream>
#include <utility>

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;

 public:
  S21Matrix();                      //базовый конструктор
  S21Matrix(int rows_, int cols_);  //параметризированный конструктор
  S21Matrix(const S21Matrix &other);  //конструктор копирования
  S21Matrix(S21Matrix &&other) noexcept;  //конструктор перемещения
  ~S21Matrix() noexcept;                  //деструктор

  int GetRows() const;  //геттер строк
  int GetCols() const;  //геттер столбцов
  double **GetMatrix() const;
  void SetRows(int new_rows);  //сеттер строк
  void SetCols(int new_cols);  //сеттер столбцов

  bool EqMatrix(const S21Matrix &other) const;  //проверка на равенство матриц
  void SumMatrix(const S21Matrix &other);  //сложение двух матриц
  void SubMatrix(const S21Matrix &other);  //вычитание двух матриц
  void MulNumber(const double num);  //умножение матрицы на число
  void MulMatrix(const S21Matrix &other);  //умножение двух матриц
  S21Matrix Transpose() const;  //транспонирование матрицы
  S21Matrix CalcComplements() const;  //матрица алгебраических дополнений
  double Determinant() const;       //определитель матрицы
  S21Matrix InverseMatrix() const;  //обратная матрица
  S21Matrix Minor(int skip_row,
                  int skip_colm) const;  //высчитывания минора

  double *operator[](int index) const;
  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix operator*(const double num) const;
  bool operator==(const S21Matrix &other) const;
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);
  double &operator()(int row_index, int col_index) const;
};

#endif