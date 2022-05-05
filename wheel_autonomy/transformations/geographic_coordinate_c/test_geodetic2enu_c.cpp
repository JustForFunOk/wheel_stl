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

class Geodetic2ENUCVersionTest : public testing::Test {
 public:
  Geodetic2ENUCVersionTest() {
    Geodetic origin_point;
    origin_point.lat_deg = 31.28220207946997;
    origin_point.lon_deg = 121.18304182503508;
    origin_point.alt_m   = 0.0;
    SetLocalOrigin(&origin_point);
  }
  virtual ~Geodetic2ENUCVersionTest() {}

 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Geodetic2ENUCVersionTest, first_region_Gps2Xy) {
  Geodetic input_gps_coord;
  input_gps_coord.lat_deg = 31.288347;
  input_gps_coord.lon_deg = 121.189725;
  input_gps_coord.alt_m   = 0.0;
  ENU output_xy_coord     = Geodetic2ENU(&input_gps_coord);

  ENU gt_xy_coord;
  gt_xy_coord.e_m = 636.343060;
  gt_xy_coord.n_m = 681.333525;
  gt_xy_coord.u_m = 0.0;
  EXPECT_NEAR(gt_xy_coord.e_m, output_xy_coord.e_m, 1.0)
      << "The result of x from function Geodetic2ENU should be : "
      << gt_xy_coord.e_m;
  EXPECT_NEAR(gt_xy_coord.n_m, output_xy_coord.n_m, 1.0)
      << "The result of y from function Geodetic2ENU should be : "
      << gt_xy_coord.n_m;
}

TEST_F(Geodetic2ENUCVersionTest, second_region_Gps2Xy) {
  Geodetic input_gps_coord;
  input_gps_coord.lat_deg = 31.294333;
  input_gps_coord.lon_deg = 121.168606;
  input_gps_coord.alt_m   = 0.0;
  ENU output_xy_coord     = Geodetic2ENU(&input_gps_coord);

  ENU gt_xy_coord;
  gt_xy_coord.e_m = -1374.430058;
  gt_xy_coord.n_m = 1345.098820;
  gt_xy_coord.u_m = 0.0;
  EXPECT_NEAR(gt_xy_coord.e_m, output_xy_coord.e_m, 1.0)
      << "The result of x from function Geodetic2ENU should be : "
      << gt_xy_coord.e_m;
  EXPECT_NEAR(gt_xy_coord.n_m, output_xy_coord.n_m, 1.0)
      << "The result of y from function Geodetic2ENU should be : "
      << gt_xy_coord.n_m;
}

TEST_F(Geodetic2ENUCVersionTest, third_region_Gps2Xy) {
  Geodetic input_gps_coord;
  input_gps_coord.lat_deg = 31.270879;
  input_gps_coord.lon_deg = 121.167555;
  input_gps_coord.alt_m   = 0.0;
  ENU output_xy_coord     = Geodetic2ENU(&input_gps_coord);

  ENU gt_xy_coord;
  gt_xy_coord.e_m = -1474.860395;
  gt_xy_coord.n_m = -1255.334203;
  gt_xy_coord.u_m = 0.0;
  EXPECT_NEAR(gt_xy_coord.e_m, output_xy_coord.e_m, 1.0)
      << "The result of x from function Geodetic2ENU should be : "
      << gt_xy_coord.e_m;
  EXPECT_NEAR(gt_xy_coord.n_m, output_xy_coord.n_m, 1.0)
      << "The result of y from function Geodetic2ENU should be : "
      << gt_xy_coord.n_m;
}

TEST_F(Geodetic2ENUCVersionTest, fourth_region_Gps2Xy) {
  Geodetic input_gps_coord;
  input_gps_coord.lat_deg = 31.274891;
  input_gps_coord.lon_deg = 121.22289;
  input_gps_coord.alt_m   = 0.0;
  ENU output_xy_coord     = Geodetic2ENU(&input_gps_coord);

  ENU gt_xy_coord;
  gt_xy_coord.e_m = 3794.709618;
  gt_xy_coord.n_m = -809.925359;
  gt_xy_coord.u_m = 0.0;
  EXPECT_NEAR(gt_xy_coord.e_m, output_xy_coord.e_m, 1.0)
      << "The result of x from function Geodetic2ENU should be : "
      << gt_xy_coord.e_m;
  EXPECT_NEAR(gt_xy_coord.n_m, output_xy_coord.n_m, 1.0)
      << "The result of y from function Geodetic2ENU should be : "
      << gt_xy_coord.n_m;
}

TEST_F(Geodetic2ENUCVersionTest, big_distance_cal) {
  Geodetic input_gps_coord;
  input_gps_coord.lat_deg = 31.2;
  input_gps_coord.lon_deg = 121.1;
  input_gps_coord.alt_m   = 0.0;
  ENU output_xy_coord     = Geodetic2ENU(&input_gps_coord);

  ENU gt_xy_coord;
  gt_xy_coord.e_m = -7914.244979;
  gt_xy_coord.n_m = -9111.060729;
  gt_xy_coord.u_m = 0.0;
  EXPECT_NEAR(gt_xy_coord.e_m, output_xy_coord.e_m, 1.0)
      << "The result of x from function Geodetic2ENU should be : "
      << gt_xy_coord.e_m;
  EXPECT_NEAR(gt_xy_coord.n_m, output_xy_coord.n_m, 1.0)
      << "The result of y from function Geodetic2ENU should be : "
      << gt_xy_coord.n_m;
}
