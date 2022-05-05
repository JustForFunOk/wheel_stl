#include "geographic_coordinate_transformations.hpp"

#include <gtest/gtest.h>

static const double kExpectedMaxError = 1E-3;

/** \example test_gps2enu.cpp
 * This is an example and test case of how to use the Geodetic2ENU function.
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
      : origin_point_(31.28220207946997, 121.18304182503508, 0.0),
        converter_(origin_point_) {}
  virtual ~Geodetic2ENUTest() {}

 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}

  Geodetic origin_point_;
  LocalCoord converter_;
};

TEST_F(Geodetic2ENUTest, first_region) {
  const Geodetic input_gps_coord(31.288347, 121.189725, 0.0);
  ENU output_enu_coord = converter_.Geodetic2ENU(input_gps_coord);

  // echo 31.288347 121.189725 0.0 | CartConvert -l 31.28220207946997
  // 121.18304182503508 0.0
  const ENU gt_enu_coord(636.343060, 681.333525, -0.068252);

  EXPECT_NEAR(gt_enu_coord.e_m, output_enu_coord.e_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.n_m, output_enu_coord.n_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.u_m, output_enu_coord.u_m, kExpectedMaxError);
}

TEST_F(Geodetic2ENUTest, second_region) {
  const Geodetic input_gps_coord(31.294333, 121.168606, 0.0);
  ENU output_enu_coord = converter_.Geodetic2ENU(input_gps_coord);

  // echo 31.294333 121.168606 0.0 | CartConvert -l 31.28220207946997
  // 121.18304182503508 0.0
  const ENU gt_enu_coord(-1374.430058, 1345.098820, -0.290359);

  EXPECT_NEAR(gt_enu_coord.e_m, output_enu_coord.e_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.n_m, output_enu_coord.n_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.u_m, output_enu_coord.u_m, kExpectedMaxError);
}

TEST_F(Geodetic2ENUTest, third_region) {
  const Geodetic input_gps_coord(31.270879, 121.167555, 0.0);
  ENU output_enu_coord = converter_.Geodetic2ENU(input_gps_coord);

  // echo 31.270879 121.167555 0.0 | CartConvert -l 31.28220207946997
  // 121.18304182503508 0.0
  const ENU gt_enu_coord(-1474.860395, -1255.334203, -0.294400);

  EXPECT_NEAR(gt_enu_coord.e_m, output_enu_coord.e_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.n_m, output_enu_coord.n_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.u_m, output_enu_coord.u_m, kExpectedMaxError);
}

TEST_F(Geodetic2ENUTest, fourth_region) {
  const Geodetic input_gps_coord(31.274891, 121.22289, 0.0);
  ENU output_enu_coord = converter_.Geodetic2ENU(input_gps_coord);

  // echo 31.274891 121.22289 0.0 | CartConvert -l 31.28220207946997
  // 121.18304182503508 0.0
  ENU gt_enu_coord(3794.709618, -809.925359, -1.179454);

  EXPECT_NEAR(gt_enu_coord.e_m, output_enu_coord.e_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.n_m, output_enu_coord.n_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.u_m, output_enu_coord.u_m, kExpectedMaxError);
}

TEST_F(Geodetic2ENUTest, big_distance_cal) {
  const Geodetic input_gps_coord(31.2, 121.1, 0.0);
  ENU output_enu_coord = converter_.Geodetic2ENU(input_gps_coord);

  // echo 31.2 121.1 0.0 | CartConvert -l 31.28220207946997 121.18304182503508
  // 0.0
  ENU gt_enu_coord(-7914.244979, -9111.060729, -11.439406);

  EXPECT_NEAR(gt_enu_coord.e_m, output_enu_coord.e_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.n_m, output_enu_coord.n_m, kExpectedMaxError);
  EXPECT_NEAR(gt_enu_coord.u_m, output_enu_coord.u_m, kExpectedMaxError);
}
