// fix eigen display bug in vscode
// https://github.com/microsoft/vscode-cpptools/issues/7413#issuecomment-827172897
#if __INTELLISENSE__
#undef __ARM_NEON
#undef __ARM_NEON__
#endif

#include <gtest/gtest.h>
#include <Eigen/Dense>

// compare matrix size
#define EXPECT_MATRIX_SIZE_EQ(matrix, row_size, col_size) \
  EXPECT_EQ(matrix.rows(), row_size);                     \
  EXPECT_EQ(matrix.cols(), col_size);

// https://eigen.tuxfamily.org/dox/classEigen_1_1Matrix.html
TEST(Eigen, Constructor_Vector3d) {
  // Vector3d <==> Matrix<double, 3, 1>
  // 3x1 double
  // | 0.0 |
  // | 1.0 |
  // | 2.0 |
  Eigen::Vector3d vec_3d_1;
  vec_3d_1 << 0.0, 1.0, 2.0;  // 1
  EXPECT_MATRIX_SIZE_EQ(vec_3d_1, 3, 1);

  Eigen::Vector3d vec_3d_2(0.0, 1.0, 2.0);  // 2
  EXPECT_MATRIX_SIZE_EQ(vec_3d_2, 3, 1);

  Eigen::Vector3d vec_3d_3{0.0, 1.0, 2.0};  // 3
  EXPECT_MATRIX_SIZE_EQ(vec_3d_3, 3, 1);

  Eigen::Vector3d vec_3d_4 = {0.0, 1.0, 2.0};  // 4
  EXPECT_MATRIX_SIZE_EQ(vec_3d_4, 3, 1);
}

TEST(Eigen, Constructor_Matrix3d) {
  // Matrix3d <==> Matrix<double, 3, 3>
  // 3x3 double
  // | 0.0 0.1 0.2 |
  // | 1.0 1.1 1.2 |
  // | 2.0 2.1 2.2 |
  Eigen::Matrix3d matrix_33;
  EXPECT_MATRIX_SIZE_EQ(matrix_33, 3, 3);
}

TEST(Eigen, Constructor_MatrixXd) {
  // Avoid to use dynamic size of matrix for performance
  // MatrixXd <==> Matrix<double, Dynamic, Dynamic>
  Eigen::MatrixXd matrix_x;
  EXPECT_EQ(matrix_x.rows(), 0);
  EXPECT_EQ(matrix_x.cols(), 0);
}

// vector(n)即可做左值（修改向量的值），也可做右值（读取向量的值），n从0开始
TEST(Eigen, Vector_ElementReadWrite) {
  // 期望的向量如下
  // | 0.0 |
  // | 1.0 |
  // | 2.0 |
  Eigen::Vector3d vec_3d;
  vec_3d << 0.0,  // | 0.0 |
      1.0,        // | 1.0 |
      2.0;        // | 2.0 |

  // Read
  EXPECT_DOUBLE_EQ(vec_3d(0), 0.0);  // use operator() to read element
  EXPECT_DOUBLE_EQ(vec_3d[1], 1.0);  // use operator[] to read element
  EXPECT_DOUBLE_EQ(vec_3d(2), 2.0);

  // ostream& operator<<(ostream& os, const Eigen::Vector3d& vec)
  std::cout << vec_3d << std::endl;  // use operator<<() to print element

  // Write and Read
  vec_3d(0) = 6.6;
  EXPECT_DOUBLE_EQ(vec_3d(0), 6.6);
}

// use matrix(row, col) to read or write element, row and col start from 0
// matrix(row, col)即可做左值（修改矩阵的值），也可做右值（读取矩阵的值）
TEST(Eigen, Matrix_ElementReadWrite) {
  // 期望的矩阵内容如下
  // | 0.0 0.1 0.2 |
  // | 1.0 1.1 1.2 |
  // | 2.0 2.1 2.2 |
  // Eigen中矩阵储存默认是列优先(也可设置为行优先)，所以内存分布为
  // | 0.0 | 1.0 | 2.0 | 0.1 | 1.1 | 2.1 | 0.2 | 1.2 | 2.2 |
#define CHECK_MATRIX_ELEMENTS(matrix_3d)  \
  EXPECT_DOUBLE_EQ(matrix_3d(0, 0), 0.0); \
  EXPECT_DOUBLE_EQ(matrix_3d(1, 0), 1.0); \
  EXPECT_DOUBLE_EQ(matrix_3d(2, 0), 2.0); \
  EXPECT_DOUBLE_EQ(matrix_3d(0, 1), 0.1); \
  EXPECT_DOUBLE_EQ(matrix_3d(1, 1), 1.1); \
  EXPECT_DOUBLE_EQ(matrix_3d(2, 1), 2.1); \
  EXPECT_DOUBLE_EQ(matrix_3d(0, 2), 0.2); \
  EXPECT_DOUBLE_EQ(matrix_3d(1, 2), 1.2); \
  EXPECT_DOUBLE_EQ(matrix_3d(2, 2), 2.2);

  // 虽然储存是列优先，但初始化顺序是行优先，所以程序里看到的是什么样，它实际就是什么样
  Eigen::Matrix3d matrix_3d_1;
  matrix_3d_1 << 0.0, 0.1, 0.2,  // | 0.0 0.1 0.2 |
      1.0, 1.1, 1.2,             // | 1.0 1.1 1.2 |
      2.0, 2.1, 2.2;             // | 2.0 2.1 2.2 |
  CHECK_MATRIX_ELEMENTS(matrix_3d_1);

  // Print matrix
  // 通过Matrix的友元函数来实现
  // ostream& operator<<(ostream& os, const Eigen::Matrix3d& matrix)
  std::cout << matrix_3d_1 << std::endl;

  // Write and Read
  matrix_3d_1(0, 0) = 6.6;
  EXPECT_DOUBLE_EQ(matrix_3d_1(0, 0), 6.6);
}

TEST(Eigen, AlgebraicOperations) {
  Eigen::Matrix3d matrix_a;
  matrix_a << 0.0, 0.1, 0.2,  // | 0.0 0.1 0.2 |
      1.0, 1.1, 1.2,          // | 1.0 1.1 1.2 |
      2.0, 2.1, 2.2;          // | 2.0 2.1 2.2 |
  std::cout << "matrix_a=" << std::endl << matrix_a << std::endl;

  // 转置
  // | 0.0 1.0 2.0 |
  // | 0.1 1.1 2.1 |
  // | 0.2 1.2 2.2 |
  std::cout << "matrix_a.transpose()=" << std::endl
            << matrix_a.transpose() << std::endl;

  // 所有元素的和
  std::cout << "matrix_a.sum()=" << std::endl << matrix_a.sum() << std::endl;
  EXPECT_DOUBLE_EQ(matrix_a.sum(), 9.9);

  // 迹?
  std::cout << "matrix_a.trace()=" << std::endl
            << matrix_a.trace() << std::endl;
  EXPECT_DOUBLE_EQ(matrix_a.trace(), 3.3);

  // 数乘
  // |  0  1  2 |
  // | 10 11 12 |
  // | 20 21 22 |
  std::cout << "10*matrix_a=" << std::endl << 10 * matrix_a << std::endl;

  // 逆
  std::cout << "matrix_a.inverse()=" << std::endl
            << matrix_a.inverse() << std::endl;

  // 行列式?
  std::cout << "matrix_a.determinant()=" << std::endl
            << matrix_a.determinant() << std::endl;
}
