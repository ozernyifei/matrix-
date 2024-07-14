#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0)
    throw std::invalid_argument("Rows and columns can't be non-positive");
  this->matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
  }
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; ++j) matrix_[i][j] = other.matrix_[i][j];
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() noexcept {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

int S21Matrix::GetRows() const { return this->rows_; }

int S21Matrix::GetCols() const { return this->cols_; }

double **S21Matrix::GetMatrix() const { return this->matrix_; }

void S21Matrix::SetRows(int new_rows) {
  if (new_rows <= 0) throw std::invalid_argument("Rows can't be non-positive");
  if (new_rows == this->rows_) return;
  S21Matrix new_matrix(new_rows, this->cols_);
  int min_rows = std::min(new_rows, this->rows_);
  for (int i = 0; i < min_rows; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      new_matrix[i][j] = matrix_[i][j];
    }
  }
  for (int i = 0; i < this->rows_; ++i) {
    delete[] this->matrix_[i];
  }
  delete[] this->matrix_;
  this->rows_ = new_rows;
  this->matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    this->matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; ++j) this->matrix_[i][j] = new_matrix[i][j];
  }
}

void S21Matrix::SetCols(int new_cols) {
  if (new_cols <= 0)
    throw std::invalid_argument("Columns can't be non-positive");
  if (new_cols == this->cols_) return;
  S21Matrix new_matrix(this->rows_, new_cols);
  int min_cols = std::min(new_cols, this->cols_);
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < min_cols; ++j) {
      new_matrix[i][j] = matrix_[i][j];
    }
  }
  for (int i = 0; i < this->rows_; ++i) {
    delete[] this->matrix_[i];
  }
  // delete[] this->matrix_;
  this->cols_ = new_cols;
  // this->matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    this->matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; ++j) {
      this->matrix_[i][j] = new_matrix[i][j];
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if ((*this)[i][j] != other[i][j]) return false;
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::logic_error("Matrix sizes are different");
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::logic_error("Matrix sizes are different");
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->cols_ != other.rows_)
    throw std::logic_error(
        "The columns number of the first matrix is ​​not equal to the rows "
        "number of the second matrix");
  S21Matrix new_matrix(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      double sum = 0;
      for (int k = 0; k < this->cols_; ++k) {
        sum += this->matrix_[i][k] * other.matrix_[k][j];
      }
      new_matrix[i][j] = sum;
    }
  }
  *this = new_matrix;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix transpose_matrix(this->cols_, this->rows_);
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      transpose_matrix[j][i] = this->matrix_[i][j];
    }
  }
  return transpose_matrix;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (this->rows_ != this->cols_)
    throw std::logic_error("The matrix isn't square");
  S21Matrix complements_matrix(this->rows_, this->cols_);
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      S21Matrix minor_matrix = Minor(i, j);
      double minor_determinant = minor_matrix.Determinant();
      complements_matrix[i][j] =
          std::pow(-1, (i + 1 + j + 1)) * minor_determinant;
    }
  }
  return complements_matrix;
}

S21Matrix S21Matrix::Minor(int skip_row, int skip_colm) const {
  if (skip_row >= this->rows_ || skip_colm >= this->cols_)
    throw std::out_of_range("Index is out of range");
  S21Matrix minor_matrix(this->rows_ - 1, this->cols_ - 1);
  int minor_matrix_row = 0;
  for (int i = 0; i < this->rows_; ++i) {
    if (i == skip_row) continue;
    int minor_matrix_colm = 0;
    for (int j = 0; j < this->cols_; ++j) {
      if (j == skip_colm) continue;
      minor_matrix[minor_matrix_row][minor_matrix_colm] = matrix_[i][j];
      ++minor_matrix_colm;
    }
    ++minor_matrix_row;
  }
  return minor_matrix;
}

double S21Matrix::Determinant() const {
  if (this->rows_ != this->cols_)
    throw std::logic_error("The matrix isn't square");
  if (this->rows_ == 1) return matrix_[0][0];
  if (this->rows_ == 2)
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  else {
    double determinant = 0;
    for (int j = 0; j < this->cols_; ++j) {
      S21Matrix minor_matrix = Minor(0, j);
      double minor_determinant = minor_matrix.Determinant();
      determinant += matrix_[0][j] * std::pow(-1, j) * minor_determinant;
    }
    return determinant;
  }
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (this->rows_ != this->cols_)
    throw std::logic_error("The matrix isn't square");
  double determinant = Determinant();
  if (determinant == 0) throw std::logic_error("The determinant is zero");
  S21Matrix inverse_matrix = CalcComplements().Transpose();
  return inverse_matrix * (1 / determinant);
}

double *S21Matrix::operator[](int index) const {
  if (index >= rows_) {
    throw std::out_of_range("Index is out of range");
  }
  return matrix_[index];
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix new_matrix(*this);
  return new_matrix += other;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix new_matrix(*this);
  return new_matrix -= other;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix new_matrix(*this);
  return new_matrix *= other;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix new_matrix(*this);
  return new_matrix *= num;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return this->EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other)  //проверка на самоприсваивание
    return *this;
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

double &S21Matrix::operator()(int row_index, int col_index) const {
  if (row_index >= rows_ || col_index >= cols_) {
    throw std::out_of_range("Index is out of range");
  }
  return matrix_[row_index][col_index];
}