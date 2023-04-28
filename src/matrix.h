#ifndef MATRIX_MATRIX_H_
#define MATRIX_MATRIX_H_

class Matrix {
 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();

  void SetRows(int rows);
  void SetCols(int cols);
  int GetRows();
  int GetCols();
  bool EqMatrix(const Matrix& other);
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(const double& num);
  void MulMatrix(const Matrix& other);
  double Determinant();
  Matrix Transpose();
  Matrix CalcComplements();
  Matrix InverseMatrix();

  void operator=(const Matrix& right);
  void operator+=(const Matrix& right);
  void operator-=(const Matrix& right);
  void operator*=(const Matrix& other);
  void operator*=(const double);
  double& operator()(int i, int j);
  double operator()(int i, int j) const;
  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const Matrix& other);
  Matrix operator*(double);

  friend Matrix operator*(double, const Matrix& matrix);
  friend bool operator==(const Matrix& left, const Matrix& right);
  friend bool operator!=(const Matrix& left, const Matrix& right);

 private:
  void CreateMatrix();
  void RemoveMatrix();
  void CreateMinorMatrix(int, int, Matrix&);
  double Fabs(double);

  int rows_;
  int cols_;
  double** matrix_;
};

Matrix operator*(double, const Matrix& matrix);
bool operator==(const Matrix& left, const Matrix& right);
bool operator!=(const Matrix& left, const Matrix& right);

#endif  // MATRIX_MATRIX_H_
