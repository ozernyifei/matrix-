#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

TEST(MatrixConstructorSuite, BasicTest) {
  S21Matrix testMatrix;
  EXPECT_EQ(testMatrix.GetCols(), 0);
  EXPECT_EQ(testMatrix.GetRows(), 0);
}

TEST(MatrixConstructorSuite, SquareTest) {
  S21Matrix testMatrix(3, 3);
  EXPECT_EQ(testMatrix.GetCols(), 3);
  EXPECT_EQ(testMatrix.GetRows(), 3);
}

TEST(MatrixConstructorSuite, NormalTest) {
  S21Matrix testMatrix(3, 5);
  EXPECT_EQ(testMatrix.GetCols(), 5);
  EXPECT_EQ(testMatrix.GetRows(), 3);
}

TEST(MatrixConstructorSuite, CopyTest) {
  S21Matrix testMatrix(12, 12);
  S21Matrix copy(testMatrix);

  EXPECT_EQ(copy.GetCols(), 12);
  EXPECT_EQ(copy.GetRows(), 12);
}

TEST(MatrixConstructorSuite, MoveTest) {
  S21Matrix testMatrix(3, 5);
  S21Matrix testMatrix2(std::move(testMatrix));
  EXPECT_EQ(testMatrix.GetCols(), 0);
  EXPECT_EQ(testMatrix.GetRows(), 0);
  EXPECT_EQ(testMatrix2.GetRows(), 3);
  EXPECT_EQ(testMatrix2.GetCols(), 5);
}

TEST(MatrixConstructorSuite, ErrorTest) {
  ASSERT_ANY_THROW(S21Matrix m(-1, -1));
}

TEST(MatrixConstructorSuite, SetTest) {
  S21Matrix testMatrix(2, 2);
  testMatrix[1][1] = 6.9;
  testMatrix.SetRows(5);
  EXPECT_EQ(testMatrix.GetRows(), 5);
  EXPECT_EQ(testMatrix[1][1], 6.9);

  S21Matrix testMatrix1(2, 2);
  testMatrix1[0][0] = 6.9;
  testMatrix1.SetRows(1);
  EXPECT_EQ(testMatrix1.GetRows(), 1);
  EXPECT_EQ(testMatrix1[0][0], 6.9);

  S21Matrix testMatrix2;
  EXPECT_ANY_THROW(testMatrix2.SetRows(0));

  S21Matrix testMatrix3(2, 2);
  testMatrix3[1][1] = 6.9;
  testMatrix3.SetCols(5);
  EXPECT_EQ(testMatrix3.GetCols(), 5);
  EXPECT_EQ(testMatrix3[1][1], 6.9);

  S21Matrix testMatrix4(2, 2);
  testMatrix4[0][0] = 6.9;
  testMatrix4.SetCols(1);
  EXPECT_EQ(testMatrix4.GetCols(), 1);
  EXPECT_EQ(testMatrix4[0][0], 6.9);

  S21Matrix testMatrix5;
  EXPECT_ANY_THROW(testMatrix5.SetCols(0));
}

TEST(MatrixConstructorSuite, SetWrongTest) {
  S21Matrix testMatrix(5, 5);
  ASSERT_ANY_THROW(testMatrix.SetCols(-5));
  ASSERT_ANY_THROW(testMatrix.SetRows(-2));
  ASSERT_ANY_THROW(testMatrix.SetRows(0));
}

TEST(MatrixArithmeticSuite, EqualTest) {
  S21Matrix testMatrix;
  S21Matrix testMatrix2;
  EXPECT_TRUE(testMatrix.EqMatrix(testMatrix2));
}

TEST(MatrixArithmeticSuite, NotEqualTest) {
  S21Matrix testMatrix(1, 1);
  S21Matrix testMatrix2(1, 1);
  testMatrix[0][0] = 12;
  testMatrix[0][0] = 7;
  EXPECT_FALSE(testMatrix == testMatrix2);
}

TEST(MatrixArithmeticSuite, NotEqualColCountTest) {
  S21Matrix testMatrix(2, 2);
  S21Matrix testMatrix2(2, 3);
  EXPECT_FALSE(testMatrix.EqMatrix(testMatrix2));
}

TEST(MatrixArithmeticSuite, SumTest) {
  S21Matrix testMatrix(2, 2);
  S21Matrix testMatrix2(2, 2);

  for (int i = 0; i < testMatrix.GetRows() && i < testMatrix.GetCols(); i++) {
    testMatrix[i][i] = 3;
    testMatrix2[i][i] = 4;
  }

  testMatrix.SumMatrix(testMatrix2);
  EXPECT_DOUBLE_EQ(testMatrix(1, 1), 7);

  testMatrix.SetCols(5);
  ASSERT_ANY_THROW(testMatrix.SumMatrix(testMatrix2));
}

TEST(MatrixArithmeticSuite, SubTest) {
  S21Matrix testMatrix(2, 2);
  S21Matrix testMatrix2(2, 2);

  for (int i = 0; i < testMatrix.GetRows() && i < testMatrix.GetCols(); i++) {
    testMatrix[i][i] = 3;
    testMatrix2[i][i] = 4;
  }

  testMatrix.SubMatrix(testMatrix2);
  EXPECT_DOUBLE_EQ(testMatrix(1, 1), -1);

  testMatrix.SetCols(5);
  ASSERT_ANY_THROW(testMatrix.SubMatrix(testMatrix2));
}

TEST(MatrixArithmeticSuite, MulNumberTest) {
  S21Matrix testMatrix(3, 3);

  testMatrix[1][1] = 3;

  testMatrix.MulNumber(6);
  EXPECT_DOUBLE_EQ(testMatrix(1, 1), 18);
}

TEST(MatrixArithmeticSuite, MulMatrixTest) {
  S21Matrix testMatrix(3, 2);
  S21Matrix testMatrix2(2, 3);

  for (int i = 0; i < testMatrix.GetRows(); i++) {
    for (int j = 0; j < testMatrix.GetCols(); j++) {
      testMatrix[i][j] = 3;
      testMatrix2[j][i] = 4;
    }
  }

  testMatrix.MulMatrix(testMatrix2);
  EXPECT_DOUBLE_EQ(testMatrix(1, 1), 24);
}

TEST(MatrixArithmeticSuite, MulMatrixErrorTest) {
  S21Matrix testMatrix(2, 4);
  S21Matrix testMatrix2(3, 2);
  ASSERT_ANY_THROW(testMatrix.MulMatrix(testMatrix2));
}

TEST(MatrixFunctionSuite, TransposeTest) {
  S21Matrix testMatrix(2, 3);
  testMatrix[0][2] = 3;
  S21Matrix result(testMatrix.Transpose());

  EXPECT_EQ(result.GetRows(), 3);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_DOUBLE_EQ(result(2, 0), 3.0);
}

TEST(MatrixFunctionSuite, DeterminantNormalTest) {
  S21Matrix testMatrix(1, 1);
  testMatrix[0][0] = 1;
  double myDet = testMatrix.Determinant();
  EXPECT_DOUBLE_EQ(myDet, 1.0);

  S21Matrix testMatrix1(3, 3);
  for (int i = 0; i < testMatrix1.GetRows(); i++) {
    for (int j = 0; j < testMatrix1.GetCols(); j++) {
      testMatrix1[i][j] = 3;
    }
  }
  myDet = testMatrix1.Determinant();
  EXPECT_DOUBLE_EQ(myDet, 0.0);

  testMatrix1[0][0] = -0.00345;
  testMatrix1[2][2] = 47;
  myDet = testMatrix1.Determinant();
  EXPECT_DOUBLE_EQ(myDet, -396.4554);
}

TEST(MatrixFunctionSuite, DeterminantNotSquareTest) {
  S21Matrix testMatrix(3, 2);
  ASSERT_ANY_THROW(testMatrix.Determinant());
}

TEST(MatrixFunctionSuite, CalcComplementsErrorTest) {
  S21Matrix testMatrix(1, 2);
  EXPECT_ANY_THROW(testMatrix.CalcComplements());
}

TEST(MatrixFunctionSuite, CalcComplements1Test) {
  const int rows = 3;
  const int cols = 3;

  S21Matrix given(rows, cols);
  S21Matrix expected(rows, cols);

  expected[0][0] = 0;
  expected[0][1] = 10;
  expected[0][2] = -20;
  expected[1][0] = 4;
  expected[1][1] = -14;
  expected[1][2] = 8;
  expected[2][0] = -8;
  expected[2][1] = -2;
  expected[2][2] = 4;

  given[0][0] = 1;
  given[0][1] = 2;
  given[0][2] = 3;
  given[1][0] = 0;
  given[1][1] = 4;
  given[1][2] = 2;
  given[2][0] = 5;
  given[2][1] = 2;
  given[2][2] = 1;

  S21Matrix res = given.CalcComplements();

  ASSERT_TRUE(res == expected);
}

TEST(MatrixFunctionSuite, CalcComplements2Test) {
  const int rows = 3;
  const int cols = 3;

  S21Matrix given(rows, cols);
  S21Matrix expected(rows, cols);

  given[0][0] = 1.0;
  given[0][1] = 2.0;
  given[0][2] = 3.0;
  given[1][0] = 0.0;
  given[1][1] = 4.0;
  given[1][2] = 2.0;
  given[2][0] = 5.0;
  given[2][1] = 2.0;
  given[2][2] = 1.0;

  expected[0][0] = 0.0;
  expected[0][1] = 10.0;
  expected[0][2] = -20.0;
  expected[1][0] = 4.0;
  expected[1][1] = -14.0;
  expected[1][2] = 8.0;
  expected[2][0] = -8.0;
  expected[2][1] = -2.0;
  expected[2][2] = 4.0;

  S21Matrix res = given.CalcComplements();

  ASSERT_TRUE(res == expected);
}

TEST(MatrixFunctionSuite, InverseMatrixErrorTest) {
  S21Matrix testMatrix(3, 3);
  EXPECT_ANY_THROW(testMatrix.InverseMatrix());
}

TEST(MatrixFunctionSuite, InverseMatrixBasicTest) {
  const int size = 3;
  S21Matrix given(size, size);
  S21Matrix expected(size, size);
  S21Matrix result(size, size);

  expected[0][0] = 44300.0 / 367429.0;
  expected[0][1] = -236300.0 / 367429.0;
  expected[0][2] = 200360.0 / 367429.0;
  expected[1][0] = 20600.0 / 367429.0;
  expected[1][1] = 56000.0 / 367429.0;
  expected[1][2] = -156483.0 / 367429.0;
  expected[2][0] = 30900.0 / 367429.0;
  expected[2][1] = 84000.0 / 367429.0;
  expected[2][2] = -51010.0 / 367429.0;

  given[0][0] = 2.8;
  given[0][1] = 1.3;
  given[0][2] = 7.01;
  given[1][0] = -1.03;
  given[1][1] = -2.3;
  given[1][2] = 3.01;
  given[2][0] = 0;
  given[2][1] = -3;
  given[2][2] = 2;

  result = given.InverseMatrix();
  for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j)
      EXPECT_DOUBLE_EQ(result[i][j], expected[i][j]);
}

TEST(MatrixFunctionSuite, InverseMatrixNormalTest) {
  const int size = 3;
  S21Matrix given(size, size);
  S21Matrix expected(size, size);
  expected[0][0] = 1.0;
  expected[0][1] = -1.0;
  expected[0][2] = 1.0;
  expected[1][0] = -38.0;
  expected[1][1] = 41.0;
  expected[1][2] = -34.0;
  expected[2][0] = 27.0;
  expected[2][1] = -29.0;
  expected[2][2] = 24.0;

  given[0][0] = 2.0;
  given[0][1] = 5.0;
  given[0][2] = 7.0;
  given[1][0] = 6.0;
  given[1][1] = 3.0;
  given[1][2] = 4.0;
  given[2][0] = 5.0;
  given[2][1] = -2.0;
  given[2][2] = -3.0;

  ASSERT_TRUE(given.InverseMatrix() == expected);
}

TEST(MatrixOperatorSuite, BracesOutOfIndexTest) {
  S21Matrix testMatrix(3, 3);
  S21Matrix testMatrix2(3, 3);

  ASSERT_ANY_THROW(testMatrix(4, 4));
}

TEST(MatrixOperatorSuite, PlusMinusTest) {
  S21Matrix testMatrix(3, 3);
  S21Matrix testMatrix2(3, 3);
  for (int i = 0; i < testMatrix.GetRows(); i++) {
    for (int j = 0; j < testMatrix.GetCols(); j++) {
      testMatrix[i][j] = 3;
      testMatrix2[i][j] = 4;
    }
  }
  S21Matrix resultMatrix(testMatrix + testMatrix2);
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), 7.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 2), 7.0);

  resultMatrix += testMatrix;
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), 10.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 2), 10.0);
  EXPECT_DOUBLE_EQ(testMatrix(2, 2), 3.0);
  EXPECT_DOUBLE_EQ(testMatrix2(2, 2), 4.0);

  resultMatrix = testMatrix - testMatrix2;
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 2), -1.0);

  resultMatrix -= testMatrix;
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), -4.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 2), -4.0);
}

TEST(MatrixOperatorSuite, MultiplicationTest) {
  S21Matrix testMatrix(3, 3);
  S21Matrix testMatrix2(3, 3);
  for (int i = 0; i < testMatrix.GetRows(); i++) {
    for (int j = 0; j < testMatrix.GetCols(); j++) {
      testMatrix[i][j] = 3;
      testMatrix2[i][j] = 4;
    }
  }
  S21Matrix resultMatrix = testMatrix * -2.0;
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), -6.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 2), -6.0);

  resultMatrix *= -(1.0 / 2.0);
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), 3.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 2), 3.0);

  for (int i = 0; i < testMatrix2.GetRows(); i++) {
    for (int j = 0; j < testMatrix2.GetCols(); j++) {
      testMatrix2[i][j] = 3;
    }
  }
  resultMatrix = testMatrix * testMatrix2;
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), 27.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 2), 27.0);

  testMatrix.SetCols(2);
  testMatrix2.SetRows(2);
  resultMatrix = testMatrix * testMatrix2;
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), 18.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 2), 18.0);

  for (int i = 0; i < resultMatrix.GetRows(); i++) {
    for (int j = 0; j < resultMatrix.GetCols(); j++) {
      resultMatrix[i][j] = 4;
    }
  }
  resultMatrix *= testMatrix;
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), 36.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 1), 36.0);
}

int main() {
  testing::InitGoogleTest();
  // testing::GTEST_FLAG(filter) = "MatrixConstructorSuite*";
  // testing::GTEST_FLAG(filter) = "MatrixArithmeticSuite*";
  // testing::GTEST_FLAG(filter) = "MatrixFunctionSuite*";
  // testing::GTEST_FLAG(filter) = "MatrixOperatorSuite*";
  return RUN_ALL_TESTS();
}