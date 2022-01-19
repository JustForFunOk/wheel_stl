#include <gtest/gtest.h>
#include <Eigen/Dense>

TEST(Eigen, Constructor_Vector3d) {
  // Vector3d <==> Matrix<double, 3, 1>
  // 3x1 double
  //
  //
  //
  Eigen::Vector3d v_3d;
  EXPECT_EQ(v_3d.rows(), 3);
  EXPECT_EQ(v_3d.cols(), 1);
}

TEST(Eigen, Constructor_Matrix3d) {
  // Matrix3d <==> Matrix<double, 3, 3>
  // 3x3 double
  //
  //
  //
  Eigen::Matrix3d matrix_33;
  EXPECT_EQ(matrix_33.rows(), 3);
  EXPECT_EQ(matrix_33.cols(), 3);
}

TEST(Eigen, Constructor_MatrixXd) {
  // Avoid to use dynamic size of matrix for performance
  // MatrixXd <==> Matrix<double, Dynamic, Dynamic>
  Eigen::MatrixXd matrix_x;
  EXPECT_EQ(matrix_x.rows(), 0);
  EXPECT_EQ(matrix_x.cols(), 0);
}
