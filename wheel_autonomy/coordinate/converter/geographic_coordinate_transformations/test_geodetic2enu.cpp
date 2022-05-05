#include "geographic_coordinate_transformations.h"

#include <gtest/gtest.h>
#include <cmath>

/** \example test_gps2enu.cpp
 * This is an example and test case of how to use the functions in gps2enu.h.
 *
 *  As the test case for convert geodetic coordinates to either geocentric or
 * local cartesian coordinates. All ground truth get from CartConvert utility,
 * for detail infos you can get from this web
 *        http://manpages.ubuntu.com/manpages/trusty/man1/CartConvert.1.html.
 *
 * More details about this example.
 */

class Geodetic2ENUTest : public testing::Test {
 public:
  Geodetic2ENUTest()
      : origin_point_(31.28220207946997, 121.18304182503508, 0),
        converter_(origin_point_) {}
  virtual ~Geodetic2ENUTest() {}

 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}

  Geodetic origin_point_;
  LocalCoord converter_;
};

TEST_F(Geodetic2ENUTest, first_region_Gps2Xy) {
  const Geodetic input_gps_coord(31.288347, 121.189725, 0);
  ENU output_xy_coord = converter_.Geodetic2ENU(input_gps_coord);

  const ENU gt_xy_coord(636.343060, 681.333525, 0);
  EXPECT_NEAR(gt_xy_coord.e_m, output_xy_coord.e_m, 1.0)
      << "The result of x from function Geodetic2ENU should be : "
      << gt_xy_coord.e_m;
  EXPECT_NEAR(gt_xy_coord.n_m, output_xy_coord.n_m, 1.0)
      << "The result of y from function Geodetic2ENU should be : "
      << gt_xy_coord.n_m;
}

TEST_F(Geodetic2ENUTest, second_region_Gps2Xy) {
  const Geodetic input_gps_coord(31.294333, 121.168606, 0);
  ENU output_xy_coord = converter_.Geodetic2ENU(input_gps_coord);

  const ENU gt_xy_coord(-1374.430058, 1345.098820, 0);
  EXPECT_NEAR(gt_xy_coord.e_m, output_xy_coord.e_m, 1.0)
      << "The result of x from function Geodetic2ENU should be : "
      << gt_xy_coord.e_m;
  EXPECT_NEAR(gt_xy_coord.n_m, output_xy_coord.n_m, 1.0)
      << "The result of y from function Geodetic2ENU should be : "
      << gt_xy_coord.n_m;
}

TEST_F(Geodetic2ENUTest, third_region_Gps2Xy) {
  const Geodetic input_gps_coord(31.270879, 121.167555, 0);
  ENU output_xy_coord = converter_.Geodetic2ENU(input_gps_coord);

  const ENU gt_xy_coord(-1474.860395, -1255.334203, 0);
  EXPECT_NEAR(gt_xy_coord.e_m, output_xy_coord.e_m, 1.0)
      << "The result of x from function Geodetic2ENU should be : "
      << gt_xy_coord.e_m;
  EXPECT_NEAR(gt_xy_coord.n_m, output_xy_coord.n_m, 1.0)
      << "The result of y from function Geodetic2ENU should be : "
      << gt_xy_coord.n_m;
}

TEST_F(Geodetic2ENUTest, fourth_region_Gps2Xy) {
  const Geodetic input_gps_coord(31.274891, 121.22289, 0);
  ENU output_xy_coord = converter_.Geodetic2ENU(input_gps_coord);

  ENU gt_xy_coord(3794.709618, -809.925359, 0);
  EXPECT_NEAR(gt_xy_coord.e_m, output_xy_coord.e_m, 1.0)
      << "The result of x from function Geodetic2ENU should be : "
      << gt_xy_coord.e_m;
  EXPECT_NEAR(gt_xy_coord.n_m, output_xy_coord.n_m, 1.0)
      << "The result of y from function Geodetic2ENU should be : "
      << gt_xy_coord.n_m;
}

TEST_F(Geodetic2ENUTest, big_distance_cal) {
  const Geodetic input_gps_coord(31.2, 121.1, 0);
  ENU output_xy_coord = converter_.Geodetic2ENU(input_gps_coord);

  ENU gt_xy_coord(-7914.244979, -9111.060729, 0);
  EXPECT_NEAR(gt_xy_coord.e_m, output_xy_coord.e_m, 1.0);
  EXPECT_NEAR(gt_xy_coord.n_m, output_xy_coord.n_m, 1.0);
}
