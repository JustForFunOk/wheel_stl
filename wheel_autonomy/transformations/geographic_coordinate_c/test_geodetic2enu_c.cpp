#include <gtest/gtest.h>
#include "geographic_coordinate_transformations.h"

static const double kExpectedMaxError = 1E-3;

/** \example test_geodetic2enu_c.cpp
 * This is an example and test case of how to use the Geodetic2ENU functions.
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

TEST_F(Geodetic2ENUCVersionTest, first_region) {
  Geodetic input_gps_coord;
  input_gps_coord.lat_deg = 31.288347;
  input_gps_coord.lon_deg = 121.189725;
  input_gps_coord.alt_m   = 0.0;

  ENU output_enu_coord = Geodetic2ENU(&input_gps_coord);

  // echo 31.288347 121.189725 0.0 | CartConvert -l 31.28220207946997
  // 121.18304182503508 0.0
  ENU gt_enu_coord;
  gt_enu_coord.e_m = 636.343060;
  gt_enu_coord.n_m = 681.333525;
  gt_enu_coord.u_m = -0.068252;

  EXPECT_NEAR(gt_enu_coord.e_m, output_enu_coord.e_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.n_m, output_enu_coord.n_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.u_m, output_enu_coord.u_m, kExpectedMaxError);
}

TEST_F(Geodetic2ENUCVersionTest, second_region) {
  Geodetic input_gps_coord;
  input_gps_coord.lat_deg = 31.294333;
  input_gps_coord.lon_deg = 121.168606;
  input_gps_coord.alt_m   = 0.0;

  ENU output_enu_coord = Geodetic2ENU(&input_gps_coord);

  // echo 31.294333 121.168606 0.0 | CartConvert -l 31.28220207946997
  // 121.18304182503508 0.0
  ENU gt_enu_coord;
  gt_enu_coord.e_m = -1374.430058;
  gt_enu_coord.n_m = 1345.098820;
  gt_enu_coord.u_m = -0.290359;

  EXPECT_NEAR(gt_enu_coord.e_m, output_enu_coord.e_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.n_m, output_enu_coord.n_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.u_m, output_enu_coord.u_m, kExpectedMaxError);
}

TEST_F(Geodetic2ENUCVersionTest, third_region) {
  Geodetic input_gps_coord;
  input_gps_coord.lat_deg = 31.270879;
  input_gps_coord.lon_deg = 121.167555;
  input_gps_coord.alt_m   = 0.0;

  ENU output_enu_coord = Geodetic2ENU(&input_gps_coord);

  // echo 31.270879 121.167555 0.0 | CartConvert -l 31.28220207946997
  // 121.18304182503508 0.0
  ENU gt_enu_coord;
  gt_enu_coord.e_m = -1474.860395;
  gt_enu_coord.n_m = -1255.334203;
  gt_enu_coord.u_m = -0.294400;
  EXPECT_NEAR(gt_enu_coord.e_m, output_enu_coord.e_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.n_m, output_enu_coord.n_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.u_m, output_enu_coord.u_m, kExpectedMaxError);
}

TEST_F(Geodetic2ENUCVersionTest, fourth_region) {
  Geodetic input_gps_coord;
  input_gps_coord.lat_deg = 31.274891;
  input_gps_coord.lon_deg = 121.22289;
  input_gps_coord.alt_m   = 0.0;

  ENU output_enu_coord = Geodetic2ENU(&input_gps_coord);

  // echo 31.274891 121.22289 0.0 | CartConvert -l 31.28220207946997
  // 121.18304182503508 0.0
  ENU gt_enu_coord;
  gt_enu_coord.e_m = 3794.709618;
  gt_enu_coord.n_m = -809.925359;
  gt_enu_coord.u_m = -1.179454;

  EXPECT_NEAR(gt_enu_coord.e_m, output_enu_coord.e_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.n_m, output_enu_coord.n_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.u_m, output_enu_coord.u_m, kExpectedMaxError);
}

TEST_F(Geodetic2ENUCVersionTest, big_distance_cal) {
  Geodetic input_gps_coord;
  input_gps_coord.lat_deg = 31.2;
  input_gps_coord.lon_deg = 121.1;
  input_gps_coord.alt_m   = 0.0;

  ENU output_enu_coord = Geodetic2ENU(&input_gps_coord);

  // echo 31.2 121.1 0.0 | CartConvert -l 31.28220207946997 121.18304182503508
  // 0.0
  ENU gt_enu_coord;
  gt_enu_coord.e_m = -7914.244979;
  gt_enu_coord.n_m = -9111.060729;
  gt_enu_coord.u_m = -11.439406;

  EXPECT_NEAR(gt_enu_coord.e_m, output_enu_coord.e_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.n_m, output_enu_coord.n_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.u_m, output_enu_coord.u_m, kExpectedMaxError);
}

TEST_F(Geodetic2ENUCVersionTest, i) {
  // set new origin point
  Geodetic origin_point;
  origin_point.lat_deg = 40.0;
  origin_point.lon_deg = 60.0;
  origin_point.alt_m   = 0.0;
  SetLocalOrigin(&origin_point);

  Geodetic input_gps_coord;
  input_gps_coord.lat_deg = 40.1;
  input_gps_coord.lon_deg = 60.1;
  input_gps_coord.alt_m   = 100.0;

  ENU output_enu_coord = Geodetic2ENU(&input_gps_coord);

  // echo 40.1 60.1 100.0 | CartConvert -l 40.0 60.0 0.0
  ENU gt_enu_coord;
  gt_enu_coord.e_m = 8527.045105;
  gt_enu_coord.n_m = 11108.511405;
  gt_enu_coord.u_m = 84.609809;

  EXPECT_NEAR(gt_enu_coord.e_m, output_enu_coord.e_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.n_m, output_enu_coord.n_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.u_m, output_enu_coord.u_m, kExpectedMaxError);
}
