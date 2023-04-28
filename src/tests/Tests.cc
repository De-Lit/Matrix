#include <gtest/gtest.h>

#include "../matrix.h"

TEST(DefaultConstructor, 1) {
  // Arrange
  // Act
  Matrix A;
  // Assert
  ASSERT_EQ(A(0, 0), 0);
  ASSERT_EQ(A.GetRows(), 1);
  ASSERT_EQ(A.GetCols(), 1);
}

TEST(ParameterizedConstructor, 1) {
  // Arrange
  int rows = 2;
  int cols = 2;
  // Act
  Matrix A(rows, cols);
  // Assert
  for (int i = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++) {
      ASSERT_EQ(A(i, j), 0);
    }
  }
  ASSERT_EQ(A.GetRows(), rows);
  ASSERT_EQ(A.GetCols(), cols);
}

TEST(ParameterizedConstructor, 2) {
  // Arrange
  int rows = 2;
  int cols = 0;
  // Act
  // Assert
  ASSERT_THROW(Matrix A(rows, cols), std::runtime_error);
}

TEST(ParameterizedConstructor, 3) {
  // Arrange
  int rows = 2;
  int cols = -2;
  // Act
  // Assert
  ASSERT_THROW(Matrix A(rows, cols), std::runtime_error);
}

TEST(CopyConstructor, 1) {
  // Arrange
  int rows = 1;
  int cols = 9;
  Matrix A(rows, cols);
  for (int i = 0, k = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++, k++) {
      A(i, j) = k;
    }
  }
  // Act
  Matrix B(A);
  // Assert
  ASSERT_EQ(B.GetRows(), A.GetRows());
  ASSERT_EQ(B.GetCols(), A.GetCols());
  for (int i = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++) {
      ASSERT_EQ(B(i, j), A(i, j));
    }
  }
}

TEST(MoveConstructor, 1) {
  // Arrange
  int rows = 3;
  int cols = 7;
  Matrix A(rows, cols);
  for (int i = 0, k = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++, k++) {
      A(i, j) = k;
    }
  }
  // Act
  Matrix B = std::move(A);
  // Assert
  ASSERT_EQ(B.GetRows(), rows);
  ASSERT_EQ(B.GetCols(), cols);
  for (int i = 0, k = 0; i < B.GetRows(); i++) {
    for (int j = 0; j < B.GetCols(); j++, k++) {
      ASSERT_EQ(B(i, j), k);
    }
  }
  ASSERT_EQ(A.GetRows(), 0);
  ASSERT_EQ(A.GetCols(), 0);
}

TEST(SetRows, 1) {
  // Arrange
  int rows = 3;
  int cols = 1;
  Matrix A;
  // Act
  A.SetRows(rows);
  // Assert
  for (int i = 0; i < A.GetRows(); i++) {
    ASSERT_EQ(A(i, 0), 0);
  }
  ASSERT_EQ(A.GetRows(), rows);
  ASSERT_EQ(A.GetCols(), cols);
}

TEST(SetRows, 2) {
  // Arrange
  int rows = 3;
  int cols = 1;
  int rowsNew = 1;
  Matrix A(rows, cols);
  // Act
  A.SetRows(rowsNew);
  // Assert
  for (int i = 0; i < A.GetRows(); i++) {
    ASSERT_EQ(A(i, 0), 0);
  }
  ASSERT_EQ(A.GetRows(), rowsNew);
  ASSERT_EQ(A.GetCols(), cols);
}

TEST(SetRows, 3) {
  // Arrange
  int rows = 3;
  int cols = 1;
  int rowsNew = -1;
  Matrix A(rows, cols);
  // Act
  // Assert
  ASSERT_THROW(A.SetRows(rowsNew), std::runtime_error);
}

TEST(SetRows, 4) {
  // Arrange
  int rows = 3;
  int cols = 1;
  int rowsNew = 0;
  Matrix A(rows, cols);
  // Act
  // Assert
  ASSERT_THROW(A.SetRows(rowsNew), std::runtime_error);
}

TEST(SetCols, 1) {
  // Arrange
  int rows = 1;
  int cols = 3;
  Matrix A;
  // Act
  A.SetCols(cols);
  // Assert
  for (int j = 0; j < A.GetCols(); j++) {
    ASSERT_EQ(A(0, j), 0);
  }
  ASSERT_EQ(A.GetRows(), rows);
  ASSERT_EQ(A.GetCols(), cols);
}

TEST(SetCols, 2) {
  // Arrange
  int rows = 1;
  int cols = 3;
  int colsNew = 1;
  Matrix A(rows, cols);
  // Act
  A.SetCols(colsNew);
  // Assert
  for (int j = 0; j < A.GetCols(); j++) {
    ASSERT_EQ(A(0, j), 0);
  }
  ASSERT_EQ(A.GetRows(), rows);
  ASSERT_EQ(A.GetCols(), colsNew);
}

TEST(SetCols, 3) {
  // Arrange
  int rows = 1;
  int cols = 3;
  int colsErr = -1;
  Matrix A(rows, cols);
  // Act
  // Assert
  ASSERT_THROW(A.SetRows(colsErr), std::runtime_error);
}

TEST(SetCols, 4) {
  // Arrange
  int rows = 1;
  int cols = 3;
  int colsErr = 0;
  Matrix A(rows, cols);
  // Act
  // Assert
  ASSERT_THROW(A.SetCols(colsErr), std::runtime_error);
}

TEST(GetRows, 1) {
  // Arrange
  int rows = 1;
  Matrix A;
  // Act
  // Assert
  ASSERT_EQ(A.GetRows(), rows);
}

TEST(GetRows, 2) {
  // Arrange
  int rows = 3;
  int cols = 3;
  Matrix A(rows, cols);
  // Act
  // Assert
  ASSERT_EQ(A.GetRows(), rows);
}

TEST(GetCols, 1) {
  // Arrange
  int cols = 1;
  Matrix A;
  // Act
  // Assert
  ASSERT_EQ(A.GetCols(), cols);
}

TEST(GetCols, 2) {
  // Arrange
  int rows = 3;
  int cols = 3;
  Matrix A(rows, cols);
  // Act
  // Assert
  ASSERT_EQ(A.GetCols(), cols);
}

TEST(EqMatrix, 1) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(2, 2);
  B(0, 0) = 6.7;
  B(0, 1) = 5;
  B(1, 0) = -4;
  B(1, 1) = 99;
  // Act
  // Assert
  ASSERT_TRUE(A.EqMatrix(B));
}

TEST(EqMatrix, 3) {
  // Arrange
  Matrix A(1, 1);
  A(0, 0) = -6.7;
  Matrix B(1, 1);
  B(0, 0) = -6.7;
  // Act
  // Assert
  ASSERT_TRUE(A.EqMatrix(B));
}

TEST(EqMatrix, 2) {
  // Arrange
  Matrix A(1, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  Matrix B(1, 2);
  B(0, 0) = 6.7;
  B(0, 1) = 5;
  // Act
  // Assert
  ASSERT_TRUE(A.EqMatrix(B));
}

TEST(EqMatrix, 4) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(2, 2);
  B(0, 0) = 6.7;
  B(0, 1) = 5;
  B(1, 0) = -4;
  B(1, 1) = 99;
  // Act
  // Assert
  ASSERT_FALSE(A.EqMatrix(B));
}

TEST(EqMatrix, 5) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(2, 3);
  B(0, 0) = 6.7;
  B(0, 1) = 5;
  B(1, 0) = -4;
  B(1, 1) = 99;
  // Act
  // Assert
  ASSERT_FALSE(A.EqMatrix(B));
}

TEST(SumMatrix, 1) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(2, 2);
  B(0, 0) = 99;
  B(0, 1) = 4;
  B(1, 0) = -5;
  B(1, 1) = 6.7;
  Matrix C(2, 2);
  C(0, 0) = 105.7;
  C(0, 1) = 9;
  C(1, 0) = -9;
  C(1, 1) = 105.7;
  // Act
  A.SumMatrix(B);
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(SumMatrix, 2) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 99;
  A(0, 1) = 4;
  A(1, 0) = -5;
  A(1, 1) = 6.7;
  Matrix B(2, 2);
  B(0, 0) = 0;
  B(0, 1) = 0;
  B(1, 0) = 0;
  B(1, 1) = 0;
  Matrix C(2, 2);
  C(0, 0) = 99;
  C(0, 1) = 4;
  C(1, 0) = -5;
  C(1, 1) = 6.7;
  // Act
  A.SumMatrix(B);
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(SumMatrix, 3) {
  // Arrange
  Matrix A(3, 5);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(0, 3) = 6;
  A(0, 4) = 9;

  A(1, 0) = 9;
  A(1, 1) = 1;
  A(1, 2) = 6;
  A(1, 3) = 8;
  A(1, 4) = 0;

  A(2, 0) = 5;
  A(2, 1) = 0;
  A(2, 2) = 2;
  A(2, 3) = 4;
  A(2, 4) = 7;

  Matrix B(3, 5);
  B(0, 0) = 34;
  B(0, 1) = 4;
  B(0, 2) = 21;
  B(0, 3) = 34;
  B(0, 4) = 30;

  B(1, 0) = 48;
  B(1, 1) = 19;
  B(1, 2) = 45;
  B(1, 3) = 86;
  B(1, 4) = 123;

  B(2, 0) = 15;
  B(2, 1) = 10;
  B(2, 2) = 19;
  B(2, 3) = 38;
  B(2, 4) = 59;

  Matrix C(3, 5);
  C(0, 0) = 35;
  C(0, 1) = 6;
  C(0, 2) = 24;
  C(0, 3) = 40;
  C(0, 4) = 39;

  C(1, 0) = 57;
  C(1, 1) = 20;
  C(1, 2) = 51;
  C(1, 3) = 94;
  C(1, 4) = 123;

  C(2, 0) = 20;
  C(2, 1) = 10;
  C(2, 2) = 21;
  C(2, 3) = 42;
  C(2, 4) = 66;
  // Act
  A.SumMatrix(B);
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(SumMatrix, 4) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(2, 4);
  B(0, 0) = 99;
  B(0, 1) = 4;
  B(1, 0) = -5;
  B(1, 1) = 6.7;
  // Act
  // Assert
  ASSERT_THROW(A.SumMatrix(B), std::runtime_error);
}

TEST(SubMatrix, 1) {
  // Arrange
  Matrix A(3, 5);
  A(0, 0) = 35;
  A(0, 1) = 6;
  A(0, 2) = 24;
  A(0, 3) = 40;
  A(0, 4) = 39;

  A(1, 0) = 57;
  A(1, 1) = 20;
  A(1, 2) = 51;
  A(1, 3) = 94;
  A(1, 4) = 123;

  A(2, 0) = 20;
  A(2, 1) = 10;
  A(2, 2) = 21;
  A(2, 3) = 42;
  A(2, 4) = 66;
  Matrix B(3, 5);
  B(0, 0) = 34;
  B(0, 1) = 4;
  B(0, 2) = 21;
  B(0, 3) = 34;
  B(0, 4) = 30;

  B(1, 0) = 48;
  B(1, 1) = 19;
  B(1, 2) = 45;
  B(1, 3) = 86;
  B(1, 4) = 123;

  B(2, 0) = 15;
  B(2, 1) = 10;
  B(2, 2) = 19;
  B(2, 3) = 38;
  B(2, 4) = 59;
  Matrix C(3, 5);
  C(0, 0) = 1;
  C(0, 1) = 2;
  C(0, 2) = 3;
  C(0, 3) = 6;
  C(0, 4) = 9;

  C(1, 0) = 9;
  C(1, 1) = 1;
  C(1, 2) = 6;
  C(1, 3) = 8;
  C(1, 4) = 0;

  C(2, 0) = 5;
  C(2, 1) = 0;
  C(2, 2) = 2;
  C(2, 3) = 4;
  C(2, 4) = 7;
  // Act
  A.SubMatrix(B);
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(SubMatrix, 2) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 105.7;
  A(0, 1) = 9;
  A(1, 0) = -9;
  A(1, 1) = 105.7;
  Matrix B(2, 2);
  B(0, 0) = 0;
  B(0, 1) = 0;
  B(1, 0) = 0;
  B(1, 1) = 0;
  Matrix C(2, 2);
  C(0, 0) = 105.7;
  C(0, 1) = 9;
  C(1, 0) = -9;
  C(1, 1) = 105.7;
  // Act
  A.SubMatrix(B);
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(SubMatrix, 3) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 105.7;
  A(0, 1) = 9;
  A(1, 0) = -9;
  A(1, 1) = 105.7;
  Matrix B(2, 2);
  B(0, 0) = 0;
  B(0, 1) = 0;
  B(1, 0) = 0;
  B(1, 1) = 0;
  Matrix C(2, 2);
  C(0, 0) = 105.7;
  C(0, 1) = 9;
  C(1, 0) = -9;
  C(1, 1) = 105.7;
  // Act
  A.SubMatrix(B);
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(SubMatrix, 4) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(2, 4);
  B(0, 0) = 99;
  B(0, 1) = 4;
  B(1, 0) = -5;
  B(1, 1) = 6.7;
  // Act
  // Assert
  ASSERT_THROW(A.SubMatrix(B), std::runtime_error);
}

TEST(MulNumber, 1) {
  // Arrange
  Matrix A(1, 1);
  A(0, 0) = 0;
  double d = 123.123;
  Matrix C(1, 1);
  C(0, 0) = 0;
  // Act
  A.MulNumber(d);
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(MulNumber, 2) {
  // Arrange
  Matrix A(1, 1);
  A(0, 0) = 1;
  double d = 123.123;
  Matrix C(1, 1);
  C(0, 0) = 123.123;
  // Act
  A.MulNumber(d);
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(MulNumber, 3) {
  // Arrange
  Matrix A(5, 3);
  A(0, 0) = 34;
  A(0, 1) = 48;
  A(0, 2) = 15;

  A(1, 0) = 4;
  A(1, 1) = 19;
  A(1, 2) = 10;

  A(2, 0) = 21;
  A(2, 1) = 45;
  A(2, 2) = 19;

  A(3, 0) = 34;
  A(3, 1) = 86;
  A(3, 2) = 38;

  A(4, 0) = 30;
  A(4, 1) = 123;
  A(4, 2) = 59;
  double d = -325.7;
  Matrix C(5, 3);
  C(0, 0) = -11073.8;
  C(0, 1) = -15633.6;
  C(0, 2) = -4885.5;

  C(1, 0) = -1302.8;
  C(1, 1) = -6188.3;
  C(1, 2) = -3257;

  C(2, 0) = -6839.7;
  C(2, 1) = -14656.5;
  C(2, 2) = -6188.3;

  C(3, 0) = -11073.8;
  C(3, 1) = -28010.2;
  C(3, 2) = -12376.6;

  C(4, 0) = -9771;
  C(4, 1) = -40061.1;
  C(4, 2) = -19216.3;
  // Act
  A.MulNumber(d);
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(MulMatrix, 1) {
  // Arrange
  Matrix A(1, 1);
  A(0, 0) = 0;
  Matrix B(1, 1);
  B(0, 0) = -5;
  Matrix C(1, 1);
  C(0, 0) = 0;
  // Act
  A.MulMatrix(B);
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(MulMatrix, 2) {
  // Arrange
  Matrix A(3, 5);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(0, 3) = 6;
  A(0, 4) = 9;

  A(1, 0) = 9;
  A(1, 1) = 1;
  A(1, 2) = 6;
  A(1, 3) = 8;
  A(1, 4) = 0;

  A(2, 0) = 5;
  A(2, 1) = 0;
  A(2, 2) = 2;
  A(2, 3) = 4;
  A(2, 4) = 7;
  Matrix B(5, 3);
  B(0, 0) = 34;
  B(0, 1) = 48;
  B(0, 2) = 15;

  B(1, 0) = 4;
  B(1, 1) = 19;
  B(1, 2) = 10;

  B(2, 0) = 21;
  B(2, 1) = 45;
  B(2, 2) = 19;

  B(3, 0) = 34;
  B(3, 1) = 86;
  B(3, 2) = 38;

  B(4, 0) = 30;
  B(4, 1) = 123;
  B(4, 2) = 59;
  Matrix C(3, 3);
  C(0, 0) = 579;
  C(0, 1) = 1844;
  C(0, 2) = 851;

  C(1, 0) = 708;
  C(1, 1) = 1409;
  C(1, 2) = 563;

  C(2, 0) = 558;
  C(2, 1) = 1535;
  C(2, 2) = 678;
  // Act
  A.MulMatrix(B);
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(MulMatrix, 3) {
  // Arrange
  Matrix A(5, 3);
  A(0, 0) = 34;
  A(0, 1) = 48;
  A(0, 2) = 15;

  A(1, 0) = 4;
  A(1, 1) = 19;
  A(1, 2) = 10;

  A(2, 0) = 21;
  A(2, 1) = 45;
  A(2, 2) = 19;

  A(3, 0) = 34;
  A(3, 1) = 86;
  A(3, 2) = 38;

  A(4, 0) = 30;
  A(4, 1) = 123;
  A(4, 2) = 59;
  Matrix B(3, 5);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 6;
  B(0, 4) = 9;

  B(1, 0) = 9;
  B(1, 1) = 1;
  B(1, 2) = 6;
  B(1, 3) = 8;
  B(1, 4) = 0;

  B(2, 0) = 5;
  B(2, 1) = 0;
  B(2, 2) = 2;
  B(2, 3) = 4;
  B(2, 4) = 7;
  Matrix C(5, 5);
  C(0, 0) = 541;
  C(0, 1) = 116;
  C(0, 2) = 420;
  C(0, 3) = 648;
  C(0, 4) = 411;

  C(1, 0) = 225;
  C(1, 1) = 27;
  C(1, 2) = 146;
  C(1, 3) = 216;
  C(1, 4) = 106;

  C(2, 0) = 521;
  C(2, 1) = 87;
  C(2, 2) = 371;
  C(2, 3) = 562;
  C(2, 4) = 322;

  C(3, 0) = 998;
  C(3, 1) = 154;
  C(3, 2) = 694;
  C(3, 3) = 1044;
  C(3, 4) = 572;

  C(4, 0) = 1432;
  C(4, 1) = 183;
  C(4, 2) = 946;
  C(4, 3) = 1400;
  C(4, 4) = 683;
  // Act
  A.MulMatrix(B);
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(MulMatrix, 4) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(4, 4);
  B(0, 0) = 99;
  B(0, 1) = 4;
  B(1, 0) = -5;
  B(1, 1) = 6.7;
  // Act
  // Assert
  ASSERT_THROW(A.MulMatrix(B), std::runtime_error);
}

TEST(Determinant, 1) {
  // Arrange
  Matrix A(1, 1);
  A(0, 0) = 7;

  double result = 0;
  double ethlon = 7;
  // Act
  result = A.Determinant();
  // Assert
  ASSERT_NEAR(result, ethlon, 1e-7);
}

TEST(Determinant, 2) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 99;
  A(0, 1) = 4;
  A(1, 0) = -5;
  A(1, 1) = 6.7;

  double result = 0;
  double ethlon = 683.3;
  // Act
  result = A.Determinant();
  // Assert
  ASSERT_NEAR(result, ethlon, 1e-7);
}

TEST(Determinant, 3) {
  // Arrange
  Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;

  A(1, 0) = 9;
  A(1, 1) = 1;
  A(1, 2) = 6;

  A(2, 0) = 5;
  A(2, 1) = 0;
  A(2, 2) = 2;

  double result = 0;
  double ethlon = 11;
  // Act
  result = A.Determinant();
  // Assert
  ASSERT_NEAR(result, ethlon, 1e-7);
}

TEST(Determinant, 4) {
  // Arrange
  Matrix A(5, 5);
  A(0, 0) = 541;
  A(0, 1) = 116;
  A(0, 2) = 420;
  A(0, 3) = 648;
  A(0, 4) = 411;

  A(1, 0) = 225;
  A(1, 1) = 27;
  A(1, 2) = 146;
  A(1, 3) = 216;
  A(1, 4) = 106;

  A(2, 0) = 521;
  A(2, 1) = 87;
  A(2, 2) = 371;
  A(2, 3) = 562;
  A(2, 4) = 322;

  A(3, 0) = 998;
  A(3, 1) = 154;
  A(3, 2) = 694;
  A(3, 3) = 1044;
  A(3, 4) = 572;

  A(4, 0) = 1432;
  A(4, 1) = 183;
  A(4, 2) = 946;
  A(4, 3) = 1400;
  A(4, 4) = 683;

  double result = 0;
  double ethlon = 0;
  // Act
  result = A.Determinant();
  // Assert
  ASSERT_NEAR(result, ethlon, 1e-7);
}

TEST(Determinant, 5) {
  // Arrange
  Matrix A(2, 4);
  A(0, 0) = 99;
  A(0, 1) = 4;
  A(1, 0) = -5;
  A(1, 1) = 6.7;
  // Act
  // Assert
  ASSERT_THROW(double result = A.Determinant(), std::runtime_error);
}

TEST(Transpose, 1) {
  // Arrange
  Matrix A(3, 5);
  A(0, 0) = 34;
  A(0, 1) = 4;
  A(0, 2) = 21;
  A(0, 3) = 34;
  A(0, 4) = 30;

  A(1, 0) = 48;
  A(1, 1) = 19;
  A(1, 2) = 45;
  A(1, 3) = 86;
  A(1, 4) = 123;

  A(2, 0) = 15;
  A(2, 1) = 10;
  A(2, 2) = 19;
  A(2, 3) = 38;
  A(2, 4) = 59;

  Matrix C(5, 3);
  C(0, 0) = 34;
  C(0, 1) = 48;
  C(0, 2) = 15;

  C(1, 0) = 4;
  C(1, 1) = 19;
  C(1, 2) = 10;

  C(2, 0) = 21;
  C(2, 1) = 45;
  C(2, 2) = 19;

  C(3, 0) = 34;
  C(3, 1) = 86;
  C(3, 2) = 38;

  C(4, 0) = 30;
  C(4, 1) = 123;
  C(4, 2) = 59;
  // Act
  Matrix B = A.Transpose();
  // Assert
  ASSERT_TRUE(B == C);
}

TEST(Transpose, 2) {
  // Arrange
  Matrix A(5, 3);
  A(0, 0) = 34;
  A(0, 1) = 48;
  A(0, 2) = 15;

  A(1, 0) = 4;
  A(1, 1) = 19;
  A(1, 2) = 10;

  A(2, 0) = 21;
  A(2, 1) = 45;
  A(2, 2) = 19;

  A(3, 0) = 34;
  A(3, 1) = 86;
  A(3, 2) = 38;

  A(4, 0) = 30;
  A(4, 1) = 123;
  A(4, 2) = 59;

  Matrix C(3, 5);
  C(0, 0) = 34;
  C(0, 1) = 4;
  C(0, 2) = 21;
  C(0, 3) = 34;
  C(0, 4) = 30;

  C(1, 0) = 48;
  C(1, 1) = 19;
  C(1, 2) = 45;
  C(1, 3) = 86;
  C(1, 4) = 123;

  C(2, 0) = 15;
  C(2, 1) = 10;
  C(2, 2) = 19;
  C(2, 3) = 38;
  C(2, 4) = 59;
  // Act
  Matrix B = A.Transpose();
  // Assert
  ASSERT_TRUE(B == C);
}

TEST(Transpose, 3) {
  // Arrange
  Matrix A(1, 1);
  A(0, 0) = 7;
  Matrix C(1, 1);
  C(0, 0) = 7;
  // Act
  Matrix B = A.Transpose();
  // Assert
  ASSERT_TRUE(B == C);
}

TEST(CalcComplements, 1) {
  // Arrange
  Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;

  A(1, 0) = 9;
  A(1, 1) = 1;
  A(1, 2) = 6;

  A(2, 0) = 5;
  A(2, 1) = 0;
  A(2, 2) = 2;

  Matrix C(3, 3);
  C(0, 0) = 2;
  C(0, 1) = 12;
  C(0, 2) = -5;

  C(1, 0) = -4;
  C(1, 1) = -13;
  C(1, 2) = 10;

  C(2, 0) = 9;
  C(2, 1) = 21;
  C(2, 2) = -17;

  // Act
  Matrix B = A.CalcComplements();
  // Assert
  ASSERT_TRUE(B == C);
}

TEST(CalcComplements, 2) {
  // Arrange
  Matrix A(3, 4);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;

  A(1, 0) = 9;
  A(1, 1) = 1;
  A(1, 2) = 6;

  A(2, 0) = 5;
  A(2, 1) = 0;
  A(2, 2) = 2;

  // Act
  // Assert
  ASSERT_THROW(Matrix B = A.CalcComplements(), std::runtime_error);
}

TEST(InverseMatrix, 1) {
  // Arrange
  Matrix A(1, 1);
  A(0, 0) = 1;

  Matrix C(1, 1);
  C(0, 0) = 1;

  // Act
  Matrix B = A.InverseMatrix();
  // Assert
  ASSERT_TRUE(A * B == C);
}

TEST(InverseMatrix, 2) {
  // Arrange
  Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;

  A(1, 0) = 9;
  A(1, 1) = 1;
  A(1, 2) = 6;

  A(2, 0) = 5;
  A(2, 1) = 0;
  A(2, 2) = 2;

  Matrix C(3, 3);
  C(0, 0) = 1;
  C(0, 1) = 0;
  C(0, 2) = 0;

  C(1, 0) = 0;
  C(1, 1) = 1;
  C(1, 2) = 0;

  C(2, 0) = 0;
  C(2, 1) = 0;
  C(2, 2) = 1;

  // Act
  Matrix B = A.InverseMatrix();
  // Assert
  ASSERT_TRUE(A * B == C);
}

TEST(InverseMatrix, 3) {
  // Arrange
  Matrix A(3, 4);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;

  A(1, 0) = 9;
  A(1, 1) = 1;
  A(1, 2) = 6;

  A(2, 0) = 5;
  A(2, 1) = 0;
  A(2, 2) = 2;
  // Act
  // Assert
  ASSERT_THROW(Matrix B = A.InverseMatrix(), std::runtime_error);
}

TEST(InverseMatrix, 4) {
  // Arrange
  Matrix A(5, 5);
  A(0, 0) = 541;
  A(0, 1) = 116;
  A(0, 2) = 420;
  A(0, 3) = 648;
  A(0, 4) = 411;

  A(1, 0) = 225;
  A(1, 1) = 27;
  A(1, 2) = 146;
  A(1, 3) = 216;
  A(1, 4) = 106;

  A(2, 0) = 521;
  A(2, 1) = 87;
  A(2, 2) = 371;
  A(2, 3) = 562;
  A(2, 4) = 322;

  A(3, 0) = 998;
  A(3, 1) = 154;
  A(3, 2) = 694;
  A(3, 3) = 1044;
  A(3, 4) = 572;

  A(4, 0) = 1432;
  A(4, 1) = 183;
  A(4, 2) = 946;
  A(4, 3) = 1400;
  A(4, 4) = 683;
  // Act
  // Assert
  ASSERT_THROW(Matrix B = A.InverseMatrix(), std::runtime_error);
}

TEST(AssignmentOverritenOperator, 1) {
  // Arrange
  int rows = 5;
  int cols = 3;
  Matrix A(rows, cols);
  for (int i = 0, k = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++, k++) {
      A(i, j) = k;
    }
  }
  // Act
  Matrix B = A;
  // Assert
  for (int i = 0, k = 0; i < B.GetRows(); i++) {
    for (int j = 0; j < B.GetCols(); j++, k++) {
      ASSERT_EQ(B(i, j), k);
    }
  }
  ASSERT_EQ(B.GetRows(), rows);
  ASSERT_EQ(B.GetCols(), cols);
}

TEST(AssignmentSumOverritenOperator, 1) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(2, 2);
  B(0, 0) = 99;
  B(0, 1) = 4;
  B(1, 0) = -5;
  B(1, 1) = 6.7;
  Matrix C(2, 2);
  C(0, 0) = 105.7;
  C(0, 1) = 9;
  C(1, 0) = -9;
  C(1, 1) = 105.7;
  // Act
  A += B;
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(AssignmentSumOverritenOperator, 2) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 99;
  A(0, 1) = 4;
  A(1, 0) = -5;
  A(1, 1) = 6.7;
  Matrix B(2, 2);
  B(0, 0) = 0;
  B(0, 1) = 0;
  B(1, 0) = 0;
  B(1, 1) = 0;
  Matrix C(2, 2);
  C(0, 0) = 99;
  C(0, 1) = 4;
  C(1, 0) = -5;
  C(1, 1) = 6.7;
  // Act
  A += B;
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(AssignmentSumOverritenOperator, 3) {
  // Arrange
  Matrix A(3, 5);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(0, 3) = 6;
  A(0, 4) = 9;

  A(1, 0) = 9;
  A(1, 1) = 1;
  A(1, 2) = 6;
  A(1, 3) = 8;
  A(1, 4) = 0;

  A(2, 0) = 5;
  A(2, 1) = 0;
  A(2, 2) = 2;
  A(2, 3) = 4;
  A(2, 4) = 7;

  Matrix B(3, 5);
  B(0, 0) = 34;
  B(0, 1) = 4;
  B(0, 2) = 21;
  B(0, 3) = 34;
  B(0, 4) = 30;

  B(1, 0) = 48;
  B(1, 1) = 19;
  B(1, 2) = 45;
  B(1, 3) = 86;
  B(1, 4) = 123;

  B(2, 0) = 15;
  B(2, 1) = 10;
  B(2, 2) = 19;
  B(2, 3) = 38;
  B(2, 4) = 59;

  Matrix C(3, 5);
  C(0, 0) = 35;
  C(0, 1) = 6;
  C(0, 2) = 24;
  C(0, 3) = 40;
  C(0, 4) = 39;

  C(1, 0) = 57;
  C(1, 1) = 20;
  C(1, 2) = 51;
  C(1, 3) = 94;
  C(1, 4) = 123;

  C(2, 0) = 20;
  C(2, 1) = 10;
  C(2, 2) = 21;
  C(2, 3) = 42;
  C(2, 4) = 66;
  // Act
  A += B;
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(AssignmentSumOverritenOperator, 4) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(4, 4);
  B(0, 0) = 99;
  B(0, 1) = 4;
  B(1, 0) = -5;
  B(1, 1) = 6.7;
  // Act
  // Assert
  ASSERT_THROW(A += B, std::runtime_error);
}

TEST(AssignmentSubOverritenOperator, 1) {
  // Arrange
  Matrix A(3, 5);
  A(0, 0) = 35;
  A(0, 1) = 6;
  A(0, 2) = 24;
  A(0, 3) = 40;
  A(0, 4) = 39;

  A(1, 0) = 57;
  A(1, 1) = 20;
  A(1, 2) = 51;
  A(1, 3) = 94;
  A(1, 4) = 123;

  A(2, 0) = 20;
  A(2, 1) = 10;
  A(2, 2) = 21;
  A(2, 3) = 42;
  A(2, 4) = 66;
  Matrix B(3, 5);
  B(0, 0) = 34;
  B(0, 1) = 4;
  B(0, 2) = 21;
  B(0, 3) = 34;
  B(0, 4) = 30;

  B(1, 0) = 48;
  B(1, 1) = 19;
  B(1, 2) = 45;
  B(1, 3) = 86;
  B(1, 4) = 123;

  B(2, 0) = 15;
  B(2, 1) = 10;
  B(2, 2) = 19;
  B(2, 3) = 38;
  B(2, 4) = 59;
  Matrix C(3, 5);
  C(0, 0) = 1;
  C(0, 1) = 2;
  C(0, 2) = 3;
  C(0, 3) = 6;
  C(0, 4) = 9;

  C(1, 0) = 9;
  C(1, 1) = 1;
  C(1, 2) = 6;
  C(1, 3) = 8;
  C(1, 4) = 0;

  C(2, 0) = 5;
  C(2, 1) = 0;
  C(2, 2) = 2;
  C(2, 3) = 4;
  C(2, 4) = 7;
  // Act
  A -= B;
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(AssignmentSubOverritenOperator, 2) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 105.7;
  A(0, 1) = 9;
  A(1, 0) = -9;
  A(1, 1) = 105.7;
  Matrix B(2, 2);
  B(0, 0) = 0;
  B(0, 1) = 0;
  B(1, 0) = 0;
  B(1, 1) = 0;
  Matrix C(2, 2);
  C(0, 0) = 105.7;
  C(0, 1) = 9;
  C(1, 0) = -9;
  C(1, 1) = 105.7;
  // Act
  A -= B;
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(AssignmentSubOverritenOperator, 3) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 105.7;
  A(0, 1) = 9;
  A(1, 0) = -9;
  A(1, 1) = 105.7;
  Matrix B(2, 2);
  B(0, 0) = 0;
  B(0, 1) = 0;
  B(1, 0) = 0;
  B(1, 1) = 0;
  Matrix C(2, 2);
  C(0, 0) = 105.7;
  C(0, 1) = 9;
  C(1, 0) = -9;
  C(1, 1) = 105.7;
  // Act
  A -= B;
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(AssignmentSubOverritenOperator, 4) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(4, 4);
  B(0, 0) = 99;
  B(0, 1) = 4;
  B(1, 0) = -5;
  B(1, 1) = 6.7;
  // Act
  // Assert
  ASSERT_THROW(A -= B, std::runtime_error);
}

TEST(SumOverritenOperator, 1) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(2, 2);
  B(0, 0) = 99;
  B(0, 1) = 4;
  B(1, 0) = -5;
  B(1, 1) = 6.7;
  Matrix C(2, 2);
  C(0, 0) = 105.7;
  C(0, 1) = 9;
  C(1, 0) = -9;
  C(1, 1) = 105.7;
  // Act
  Matrix D = A + B;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(SumOverritenOperator, 2) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 99;
  A(0, 1) = 4;
  A(1, 0) = -5;
  A(1, 1) = 6.7;
  Matrix B(2, 2);
  B(0, 0) = 0;
  B(0, 1) = 0;
  B(1, 0) = 0;
  B(1, 1) = 0;
  Matrix C(2, 2);
  C(0, 0) = 99;
  C(0, 1) = 4;
  C(1, 0) = -5;
  C(1, 1) = 6.7;
  // Act
  Matrix D = A + B;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(SumOverritenOperator, 3) {
  // Arrange
  Matrix A(3, 5);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(0, 3) = 6;
  A(0, 4) = 9;

  A(1, 0) = 9;
  A(1, 1) = 1;
  A(1, 2) = 6;
  A(1, 3) = 8;
  A(1, 4) = 0;

  A(2, 0) = 5;
  A(2, 1) = 0;
  A(2, 2) = 2;
  A(2, 3) = 4;
  A(2, 4) = 7;

  Matrix B(3, 5);
  B(0, 0) = 34;
  B(0, 1) = 4;
  B(0, 2) = 21;
  B(0, 3) = 34;
  B(0, 4) = 30;

  B(1, 0) = 48;
  B(1, 1) = 19;
  B(1, 2) = 45;
  B(1, 3) = 86;
  B(1, 4) = 123;

  B(2, 0) = 15;
  B(2, 1) = 10;
  B(2, 2) = 19;
  B(2, 3) = 38;
  B(2, 4) = 59;

  Matrix C(3, 5);
  C(0, 0) = 35;
  C(0, 1) = 6;
  C(0, 2) = 24;
  C(0, 3) = 40;
  C(0, 4) = 39;

  C(1, 0) = 57;
  C(1, 1) = 20;
  C(1, 2) = 51;
  C(1, 3) = 94;
  C(1, 4) = 123;

  C(2, 0) = 20;
  C(2, 1) = 10;
  C(2, 2) = 21;
  C(2, 3) = 42;
  C(2, 4) = 66;
  // Act
  Matrix D = A + B;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(SumOverritenOperator, 4) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(4, 4);
  B(0, 0) = 99;
  B(0, 1) = 4;
  B(1, 0) = -5;
  B(1, 1) = 6.7;
  // Act
  // Assert
  ASSERT_THROW(Matrix D = A + B, std::runtime_error);
}

TEST(SubOverritenOperator, 1) {
  // Arrange
  Matrix A(3, 5);
  A(0, 0) = 35;
  A(0, 1) = 6;
  A(0, 2) = 24;
  A(0, 3) = 40;
  A(0, 4) = 39;

  A(1, 0) = 57;
  A(1, 1) = 20;
  A(1, 2) = 51;
  A(1, 3) = 94;
  A(1, 4) = 123;

  A(2, 0) = 20;
  A(2, 1) = 10;
  A(2, 2) = 21;
  A(2, 3) = 42;
  A(2, 4) = 66;
  Matrix B(3, 5);
  B(0, 0) = 34;
  B(0, 1) = 4;
  B(0, 2) = 21;
  B(0, 3) = 34;
  B(0, 4) = 30;

  B(1, 0) = 48;
  B(1, 1) = 19;
  B(1, 2) = 45;
  B(1, 3) = 86;
  B(1, 4) = 123;

  B(2, 0) = 15;
  B(2, 1) = 10;
  B(2, 2) = 19;
  B(2, 3) = 38;
  B(2, 4) = 59;
  Matrix C(3, 5);
  C(0, 0) = 1;
  C(0, 1) = 2;
  C(0, 2) = 3;
  C(0, 3) = 6;
  C(0, 4) = 9;

  C(1, 0) = 9;
  C(1, 1) = 1;
  C(1, 2) = 6;
  C(1, 3) = 8;
  C(1, 4) = 0;

  C(2, 0) = 5;
  C(2, 1) = 0;
  C(2, 2) = 2;
  C(2, 3) = 4;
  C(2, 4) = 7;
  // Act
  Matrix D = A - B;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(SubOverritenOperator, 2) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 105.7;
  A(0, 1) = 9;
  A(1, 0) = -9;
  A(1, 1) = 105.7;
  Matrix B(2, 2);
  B(0, 0) = 0;
  B(0, 1) = 0;
  B(1, 0) = 0;
  B(1, 1) = 0;
  Matrix C(2, 2);
  C(0, 0) = 105.7;
  C(0, 1) = 9;
  C(1, 0) = -9;
  C(1, 1) = 105.7;
  // Act
  Matrix D = A - B;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(SubOverritenOperator, 3) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 105.7;
  A(0, 1) = 9;
  A(1, 0) = -9;
  A(1, 1) = 105.7;
  Matrix B(2, 2);
  B(0, 0) = 0;
  B(0, 1) = 0;
  B(1, 0) = 0;
  B(1, 1) = 0;
  Matrix C(2, 2);
  C(0, 0) = 105.7;
  C(0, 1) = 9;
  C(1, 0) = -9;
  C(1, 1) = 105.7;
  // Act
  Matrix D = A - B;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(SubOverritenOperator, 4) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(4, 4);
  B(0, 0) = 99;
  B(0, 1) = 4;
  B(1, 0) = -5;
  B(1, 1) = 6.7;
  // Act
  // Assert
  ASSERT_THROW(Matrix D = A - B, std::runtime_error);
}

TEST(MulOverritenOperator, MatrixMatrix1) {
  // Arrange
  Matrix A(1, 1);
  A(0, 0) = 0;
  Matrix B(1, 1);
  B(0, 0) = -5;
  Matrix C(1, 1);
  C(0, 0) = 0;
  // Act
  Matrix D = A * B;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(MulOverritenOperator, MatrixMatrix2) {
  // Arrange
  Matrix A(3, 5);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(0, 3) = 6;
  A(0, 4) = 9;

  A(1, 0) = 9;
  A(1, 1) = 1;
  A(1, 2) = 6;
  A(1, 3) = 8;
  A(1, 4) = 0;

  A(2, 0) = 5;
  A(2, 1) = 0;
  A(2, 2) = 2;
  A(2, 3) = 4;
  A(2, 4) = 7;
  Matrix B(5, 3);
  B(0, 0) = 34;
  B(0, 1) = 48;
  B(0, 2) = 15;

  B(1, 0) = 4;
  B(1, 1) = 19;
  B(1, 2) = 10;

  B(2, 0) = 21;
  B(2, 1) = 45;
  B(2, 2) = 19;

  B(3, 0) = 34;
  B(3, 1) = 86;
  B(3, 2) = 38;

  B(4, 0) = 30;
  B(4, 1) = 123;
  B(4, 2) = 59;
  Matrix C(3, 3);
  C(0, 0) = 579;
  C(0, 1) = 1844;
  C(0, 2) = 851;

  C(1, 0) = 708;
  C(1, 1) = 1409;
  C(1, 2) = 563;

  C(2, 0) = 558;
  C(2, 1) = 1535;
  C(2, 2) = 678;
  // Act
  Matrix D = A * B;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(MulOverritenOperator, MatrixMatrix3) {
  // Arrange
  Matrix A(5, 3);
  A(0, 0) = 34;
  A(0, 1) = 48;
  A(0, 2) = 15;

  A(1, 0) = 4;
  A(1, 1) = 19;
  A(1, 2) = 10;

  A(2, 0) = 21;
  A(2, 1) = 45;
  A(2, 2) = 19;

  A(3, 0) = 34;
  A(3, 1) = 86;
  A(3, 2) = 38;

  A(4, 0) = 30;
  A(4, 1) = 123;
  A(4, 2) = 59;
  Matrix B(3, 5);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 6;
  B(0, 4) = 9;

  B(1, 0) = 9;
  B(1, 1) = 1;
  B(1, 2) = 6;
  B(1, 3) = 8;
  B(1, 4) = 0;

  B(2, 0) = 5;
  B(2, 1) = 0;
  B(2, 2) = 2;
  B(2, 3) = 4;
  B(2, 4) = 7;
  Matrix C(5, 5);
  C(0, 0) = 541;
  C(0, 1) = 116;
  C(0, 2) = 420;
  C(0, 3) = 648;
  C(0, 4) = 411;

  C(1, 0) = 225;
  C(1, 1) = 27;
  C(1, 2) = 146;
  C(1, 3) = 216;
  C(1, 4) = 106;

  C(2, 0) = 521;
  C(2, 1) = 87;
  C(2, 2) = 371;
  C(2, 3) = 562;
  C(2, 4) = 322;

  C(3, 0) = 998;
  C(3, 1) = 154;
  C(3, 2) = 694;
  C(3, 3) = 1044;
  C(3, 4) = 572;

  C(4, 0) = 1432;
  C(4, 1) = 183;
  C(4, 2) = 946;
  C(4, 3) = 1400;
  C(4, 4) = 683;
  // Act
  Matrix D = A * B;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(MulOverritenOperator, MatrixMatrix4) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(4, 4);
  B(0, 0) = 99;
  B(0, 1) = 4;
  B(1, 0) = -5;
  B(1, 1) = 6.7;
  // Act
  // Assert
  ASSERT_THROW(Matrix D = A * B, std::runtime_error);
}

TEST(MulOverritenOperator, MatrixNumber1) {
  // Arrange
  Matrix A(1, 1);
  A(0, 0) = 0;
  double d = 123.123;
  Matrix C(1, 1);
  C(0, 0) = 0;
  // Act
  Matrix D = A * d;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(MulOverritenOperator, MatrixNumber2) {
  // Arrange
  Matrix A(1, 1);
  A(0, 0) = 1;
  double d = 123.123;
  Matrix C(1, 1);
  C(0, 0) = 123.123;
  // Act
  Matrix D = A * d;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(MulOverritenOperator, MatrixNumber3) {
  // Arrange
  Matrix A(5, 3);
  A(0, 0) = 34;
  A(0, 1) = 48;
  A(0, 2) = 15;

  A(1, 0) = 4;
  A(1, 1) = 19;
  A(1, 2) = 10;

  A(2, 0) = 21;
  A(2, 1) = 45;
  A(2, 2) = 19;

  A(3, 0) = 34;
  A(3, 1) = 86;
  A(3, 2) = 38;

  A(4, 0) = 30;
  A(4, 1) = 123;
  A(4, 2) = 59;
  double d = -325.7;
  Matrix C(5, 3);
  C(0, 0) = -11073.8;
  C(0, 1) = -15633.6;
  C(0, 2) = -4885.5;

  C(1, 0) = -1302.8;
  C(1, 1) = -6188.3;
  C(1, 2) = -3257;

  C(2, 0) = -6839.7;
  C(2, 1) = -14656.5;
  C(2, 2) = -6188.3;

  C(3, 0) = -11073.8;
  C(3, 1) = -28010.2;
  C(3, 2) = -12376.6;

  C(4, 0) = -9771;
  C(4, 1) = -40061.1;
  C(4, 2) = -19216.3;
  // Act
  Matrix D = A * d;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(MulOverritenOperator, NumberMatrix1) {
  // Arrange
  Matrix A(1, 1);
  A(0, 0) = 0;
  double d = 123.123;
  Matrix C(1, 1);
  C(0, 0) = 0;
  // Act
  Matrix D = d * A;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(MulOverritenOperator, NumberMatrix2) {
  // Arrange
  Matrix A(1, 1);
  A(0, 0) = 1;
  double d = 123.123;
  Matrix C(1, 1);
  C(0, 0) = 123.123;
  // Act
  Matrix D = d * A;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(MulOverritenOperator, NumberMatrix3) {
  // Arrange
  Matrix A(5, 3);
  A(0, 0) = 34;
  A(0, 1) = 48;
  A(0, 2) = 15;

  A(1, 0) = 4;
  A(1, 1) = 19;
  A(1, 2) = 10;

  A(2, 0) = 21;
  A(2, 1) = 45;
  A(2, 2) = 19;

  A(3, 0) = 34;
  A(3, 1) = 86;
  A(3, 2) = 38;

  A(4, 0) = 30;
  A(4, 1) = 123;
  A(4, 2) = 59;
  double d = -325.7;
  Matrix C(5, 3);
  C(0, 0) = -11073.8;
  C(0, 1) = -15633.6;
  C(0, 2) = -4885.5;

  C(1, 0) = -1302.8;
  C(1, 1) = -6188.3;
  C(1, 2) = -3257;

  C(2, 0) = -6839.7;
  C(2, 1) = -14656.5;
  C(2, 2) = -6188.3;

  C(3, 0) = -11073.8;
  C(3, 1) = -28010.2;
  C(3, 2) = -12376.6;

  C(4, 0) = -9771;
  C(4, 1) = -40061.1;
  C(4, 2) = -19216.3;
  // Act
  Matrix D = d * A;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(AssignmentMulOverritenOperator, MatrixMatrix1) {
  // Arrange
  Matrix A(1, 1);
  A(0, 0) = 0;
  Matrix B(1, 1);
  B(0, 0) = -5;
  Matrix C(1, 1);
  C(0, 0) = 0;
  // Act
  A *= B;
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(AssignmentMulOverritenOperator, MatrixMatrix2) {
  // Arrange
  Matrix A(3, 5);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(0, 3) = 6;
  A(0, 4) = 9;

  A(1, 0) = 9;
  A(1, 1) = 1;
  A(1, 2) = 6;
  A(1, 3) = 8;
  A(1, 4) = 0;

  A(2, 0) = 5;
  A(2, 1) = 0;
  A(2, 2) = 2;
  A(2, 3) = 4;
  A(2, 4) = 7;
  Matrix B(5, 3);
  B(0, 0) = 34;
  B(0, 1) = 48;
  B(0, 2) = 15;

  B(1, 0) = 4;
  B(1, 1) = 19;
  B(1, 2) = 10;

  B(2, 0) = 21;
  B(2, 1) = 45;
  B(2, 2) = 19;

  B(3, 0) = 34;
  B(3, 1) = 86;
  B(3, 2) = 38;

  B(4, 0) = 30;
  B(4, 1) = 123;
  B(4, 2) = 59;
  Matrix C(3, 3);
  C(0, 0) = 579;
  C(0, 1) = 1844;
  C(0, 2) = 851;

  C(1, 0) = 708;
  C(1, 1) = 1409;
  C(1, 2) = 563;

  C(2, 0) = 558;
  C(2, 1) = 1535;
  C(2, 2) = 678;
  // Act
  A *= B;
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(AssignmentMulOverritenOperator, MatrixMatrix3) {
  // Arrange
  Matrix A(5, 3);
  A(0, 0) = 34;
  A(0, 1) = 48;
  A(0, 2) = 15;

  A(1, 0) = 4;
  A(1, 1) = 19;
  A(1, 2) = 10;

  A(2, 0) = 21;
  A(2, 1) = 45;
  A(2, 2) = 19;

  A(3, 0) = 34;
  A(3, 1) = 86;
  A(3, 2) = 38;

  A(4, 0) = 30;
  A(4, 1) = 123;
  A(4, 2) = 59;
  Matrix B(3, 5);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 6;
  B(0, 4) = 9;

  B(1, 0) = 9;
  B(1, 1) = 1;
  B(1, 2) = 6;
  B(1, 3) = 8;
  B(1, 4) = 0;

  B(2, 0) = 5;
  B(2, 1) = 0;
  B(2, 2) = 2;
  B(2, 3) = 4;
  B(2, 4) = 7;
  Matrix C(5, 5);
  C(0, 0) = 541;
  C(0, 1) = 116;
  C(0, 2) = 420;
  C(0, 3) = 648;
  C(0, 4) = 411;

  C(1, 0) = 225;
  C(1, 1) = 27;
  C(1, 2) = 146;
  C(1, 3) = 216;
  C(1, 4) = 106;

  C(2, 0) = 521;
  C(2, 1) = 87;
  C(2, 2) = 371;
  C(2, 3) = 562;
  C(2, 4) = 322;

  C(3, 0) = 998;
  C(3, 1) = 154;
  C(3, 2) = 694;
  C(3, 3) = 1044;
  C(3, 4) = 572;

  C(4, 0) = 1432;
  C(4, 1) = 183;
  C(4, 2) = 946;
  C(4, 3) = 1400;
  C(4, 4) = 683;
  // Act
  A *= B;
  // Assert
  ASSERT_TRUE(A == C);
}

TEST(AssignmentMulOverritenOperator, MatrixMatrix4) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(4, 4);
  B(0, 0) = 99;
  B(0, 1) = 4;
  B(1, 0) = -5;
  B(1, 1) = 6.7;
  // Act
  // Assert
  ASSERT_THROW(A *= B, std::runtime_error);
}

TEST(AssignmentMulOverritenOperator, MatrixNumber1) {
  // Arrange
  Matrix A(1, 1);
  A(0, 0) = 0;
  double d = 123.123;
  Matrix C(1, 1);
  C(0, 0) = 0;
  // Act
  Matrix D = d * A;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(AssignmentMulOverritenOperator, MatrixNumber2) {
  // Arrange
  Matrix A(1, 1);
  A(0, 0) = 1;
  double d = 123.123;
  Matrix C(1, 1);
  C(0, 0) = 123.123;
  // Act
  Matrix D = d * A;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(AssignmentMulOverritenOperator, MatrixNumber3) {
  // Arrange
  Matrix A(5, 3);
  A(0, 0) = 34;
  A(0, 1) = 48;
  A(0, 2) = 15;

  A(1, 0) = 4;
  A(1, 1) = 19;
  A(1, 2) = 10;

  A(2, 0) = 21;
  A(2, 1) = 45;
  A(2, 2) = 19;

  A(3, 0) = 34;
  A(3, 1) = 86;
  A(3, 2) = 38;

  A(4, 0) = 30;
  A(4, 1) = 123;
  A(4, 2) = 59;
  double d = -325.7;
  Matrix C(5, 3);
  C(0, 0) = -11073.8;
  C(0, 1) = -15633.6;
  C(0, 2) = -4885.5;

  C(1, 0) = -1302.8;
  C(1, 1) = -6188.3;
  C(1, 2) = -3257;

  C(2, 0) = -6839.7;
  C(2, 1) = -14656.5;
  C(2, 2) = -6188.3;

  C(3, 0) = -11073.8;
  C(3, 1) = -28010.2;
  C(3, 2) = -12376.6;

  C(4, 0) = -9771;
  C(4, 1) = -40061.1;
  C(4, 2) = -19216.3;
  // Act
  Matrix D = d * A;
  // Assert
  ASSERT_TRUE(D == C);
}

TEST(EqOverritenOperator, 1) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(2, 2);
  B(0, 0) = 6.7;
  B(0, 1) = 5;
  B(1, 0) = -4;
  B(1, 1) = 99;
  // Act
  // Assert
  ASSERT_TRUE(A == B);
}

TEST(EqOverritenOperator, 3) {
  // Arrange
  Matrix A(1, 1);
  A(0, 0) = -6.7;
  Matrix B(1, 1);
  B(0, 0) = -6.7;
  // Act
  // Assert
  ASSERT_TRUE(A == B);
}

TEST(EqOverritenOperator, 2) {
  // Arrange
  Matrix A(1, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  Matrix B(1, 2);
  B(0, 0) = 6.7;
  B(0, 1) = 5;
  // Act
  // Assert
  ASSERT_TRUE(A == B);
}

TEST(EqOverritenOperator, 4) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(2, 2);
  B(0, 0) = 6.7;
  B(0, 1) = 5;
  B(1, 0) = -4;
  B(1, 1) = 99;
  // Act
  // Assert
  ASSERT_FALSE(A == B);
}

TEST(EqOverritenOperator, 5) {
  // Arrange
  Matrix A(2, 2);
  A(0, 0) = 6.7;
  A(0, 1) = 5;
  A(1, 0) = -4;
  A(1, 1) = 99;
  Matrix B(2, 3);
  B(0, 0) = 6.7;
  B(0, 1) = 5;
  B(1, 0) = -4;
  B(1, 1) = 99;
  // Act
  // Assert
  ASSERT_FALSE(A == B);
}

TEST(BrecketsOverritenOperator, 1) {
  // Arrange
  int rows = 5;
  int cols = 3;
  Matrix A(rows, cols);
  // Act
  for (int i = 0, k = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++, k++) {
      A(i, j) = k;
    }
  }
  // Assert
  for (int i = 0, k = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++, k++) {
      ASSERT_EQ(A(i, j), k);
    }
  }
  ASSERT_EQ(A.GetRows(), rows);
  ASSERT_EQ(A.GetCols(), cols);
}

TEST(BrecketsOverritenOperator, 2) {
  // Arrange
  int rows = 5;
  int cols = 3;
  Matrix A(rows, cols);
  // Act
  // Assert
  ASSERT_THROW(A(1, -1), std::runtime_error);
}

TEST(BrecketsOverritenOperator, 3) {
  // Arrange
  int rows = 5;
  int cols = 3;
  Matrix A(rows, cols);
  // Act
  // Assert
  ASSERT_THROW(A(1, 10), std::runtime_error);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
