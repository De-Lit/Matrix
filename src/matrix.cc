#include <stdexcept>

#include "matrix.h"

Matrix::Matrix() : Matrix(1, 1) {}

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::runtime_error("Error");
  }
  this->CreateMatrix();
}

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
  this->CreateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

Matrix::Matrix(Matrix&& other) : rows_(0), cols_(0), matrix_(nullptr) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}

Matrix::~Matrix() { this->RemoveMatrix(); }

void Matrix::SetRows(int rows) {
  if (rows <= 0) {
    throw std::runtime_error("Error");
  }
  if (rows_ != rows) {
    Matrix TMP(rows, cols_);
    for (int i = 0; i < std::min(rows_, rows); i++) {
      for (int j = 0; j < cols_; j++) {
        TMP.matrix_[i][j] = matrix_[i][j];
      }
    }
    std::swap(matrix_, TMP.matrix_);
    std::swap(rows_, TMP.rows_);
  }
}

void Matrix::SetCols(int cols) {
  if (cols <= 0) {
    throw std::runtime_error("Error");
  }
  if (cols_ != cols) {
    Matrix TMP(rows_, cols);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < std::min(cols_, cols); j++) {
        TMP.matrix_[i][j] = matrix_[i][j];
      }
    }
    std::swap(matrix_, TMP.matrix_);
    std::swap(cols_, TMP.cols_);
  }
}

int Matrix::GetRows() { return rows_; }

int Matrix::GetCols() { return cols_; }

bool Matrix::EqMatrix(const Matrix& other) {
  if (rows_ != other.rows_) {
    return false;
  }
  if (cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if ((double)Fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
        return false;
      }
    }
  }
  return true;
}

void Matrix::SumMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::runtime_error("Error");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

void Matrix::SubMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::runtime_error("Error");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

void Matrix::MulNumber(const double& num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void Matrix::MulMatrix(const Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::runtime_error("Error");
  }
  Matrix TMP(rows_, other.cols_);
  for (int i = 0; i < TMP.rows_; i++) {
    for (int j = 0; j < TMP.cols_; j++) {
      for (int r = 0; r < cols_; r++) {
        TMP.matrix_[i][j] += matrix_[i][r] * other.matrix_[r][j];
      }
    }
  }
  *this = TMP;
}

double Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::runtime_error("Error");
  }
  if (rows_ == 1) {
    return matrix_[0][0];
  } else if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else if (rows_ == 3) {
    return matrix_[0][0] * matrix_[1][1] * matrix_[2][2] +
           matrix_[0][1] * matrix_[1][2] * matrix_[2][0] +
           matrix_[0][2] * matrix_[1][0] * matrix_[2][1] -
           matrix_[0][2] * matrix_[1][1] * matrix_[2][0] -
           matrix_[0][0] * matrix_[1][2] * matrix_[2][1] -
           matrix_[0][1] * matrix_[1][0] * matrix_[2][2];
  } else {
    double result = 0;
    if (rows_ == 2) {
      result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
    } else {
      Matrix M(rows_ - 1, cols_ - 1);
      for (int j = 0, sign = 1; j < cols_; j++, sign = 1) {
        this->CreateMinorMatrix(0, j, M);
        if ((1 + j) & 1) {
          sign *= -1;
        }
        result += sign * matrix_[0][j] * M.Determinant();
      }
    }
    return result;
  }
}

Matrix Matrix::Transpose() {
  Matrix TransposeMatrix = Matrix(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      TransposeMatrix.matrix_[j][i] = matrix_[i][j];
    }
  }
  return TransposeMatrix;
}

Matrix Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::runtime_error("Error");
  }
  Matrix Result = Matrix(rows_, cols_);
  if (rows_ == 1) {
    Result.matrix_[0][0] = 1;
  } else {
    Matrix TMP(rows_ - 1, cols_ - 1);
    double determinant = 0;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0, sign = 1; j < cols_; j++, sign = 1) {
        this->CreateMinorMatrix(i, j, TMP);
        determinant = TMP.Determinant();
        if ((i + j) & 1) {
          sign *= -1;
        }
        Result.matrix_[i][j] = sign * determinant;
      }
    }
  }
  return Result;
}

Matrix Matrix::InverseMatrix() {
  double determinant = this->Determinant();
  if (determinant == 0) {
    throw std::runtime_error("Error");
  }
  Matrix TMP = Matrix(rows_, cols_);
  TMP = this->CalcComplements();
  TMP = TMP.Transpose();
  TMP.MulNumber(1. / determinant);
  return TMP;
}

void Matrix::operator+=(const Matrix& matrix) { this->SumMatrix(matrix); }

void Matrix::operator-=(const Matrix& matrix) { this->SubMatrix(matrix); }

double& Matrix::operator()(int i, int j) {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_) {
    throw std::runtime_error("Error");
  }
  return matrix_[i][j];
}

void Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    if (matrix_ != nullptr) {
      this->RemoveMatrix();
    }
    rows_ = other.rows_;
    cols_ = other.cols_;
    CreateMatrix();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
}

Matrix Matrix::operator+(const Matrix& other) {
  Matrix TMP = *this;
  TMP.SumMatrix(other);
  return TMP;
}

Matrix Matrix::operator-(const Matrix& other) {
  Matrix TMP = *this;
  TMP.SubMatrix(other);
  return TMP;
}

Matrix Matrix::operator*(const Matrix& other) {
  Matrix TMP = *this;
  TMP.MulMatrix(other);
  return TMP;
}

Matrix Matrix::operator*(double x) {
  Matrix TMP = *this;
  TMP.MulNumber(x);
  return TMP;
}

Matrix operator*(double x, const Matrix& matrix) {
  Matrix TMP = matrix;
  TMP.MulNumber(x);
  return TMP;
}

void Matrix::operator*=(const Matrix& other) { this->MulMatrix(other); }

void Matrix::operator*=(const double x) { this->MulNumber(x); }

bool operator==(const Matrix& left, const Matrix& right) {
  Matrix TMP = left;
  return TMP.EqMatrix(right);
}

bool operator!=(const Matrix& left, const Matrix& right) {
  Matrix TMP = left;
  return TMP.EqMatrix(right);
}

void Matrix::CreateMatrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0.;
    }
  }
}

void Matrix::RemoveMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

void Matrix::CreateMinorMatrix(int row, int column, Matrix& Minor) {
  for (int i = 0, k = 0; i < rows_; i++, k++) {
    if (i == row) {
      i++;
    }
    if (i == rows_) {
      continue;
    }
    for (int j = 0, l = 0; j < cols_; j++, l++) {
      if (j == column) {
        j++;
      }
      if (j == cols_) {
        continue;
      }
      Minor.matrix_[k][l] = matrix_[i][j];
    }
  }
}

double Matrix::Fabs(double x) { return x < 0 ? -x : x; }
