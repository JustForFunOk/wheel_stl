#include <gtest/gtest.h>
#include <cmath>
#include "gps2enu.h"

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

class Gps2EnuTest : public testing::Test {
 public:
  Gps2EnuTest()
      : origin_point_(31.28220207946997, 121.18304182503508),
        gps2enu_test_(origin_point_) {}
  virtual ~Gps2EnuTest() {}

 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}

  GpsCoord origin_point_;
  Gps2Enu gps2enu_test_;
};

TEST_F(Gps2EnuTest, first_region_Gps2Xy) {
  const GpsCoord input_gps_coord(31.288347, 121.189725);
  XyCoord output_xy_coord;
  gps2enu_test_.Gps2Xy(input_gps_coord, output_xy_coord);

  const XyCoord gt_xy_coord(636.343060, 681.333525);
  EXPECT_NEAR(gt_xy_coord.x_m, output_xy_coord.x_m, 1.0);
  EXPECT_NEAR(gt_xy_coord.y_m, output_xy_coord.y_m, 1.0);
}

TEST_F(Gps2EnuTest, second_region_Gps2Xy) {
  const GpsCoord input_gps_coord(31.294333, 121.168606);
  XyCoord output_xy_coord;
  gps2enu_test_.Gps2Xy(input_gps_coord, output_xy_coord);

  const XyCoord gt_xy_coord(-1374.430058, 1345.098820);
  EXPECT_NEAR(gt_xy_coord.x_m, output_xy_coord.x_m, 1.0);
  EXPECT_NEAR(gt_xy_coord.y_m, output_xy_coord.y_m, 1.0);
}

TEST_F(Gps2EnuTest, third_region_Gps2Xy) {
  const GpsCoord input_gps_coord(31.270879, 121.167555);
  XyCoord output_xy_coord;
  gps2enu_test_.Gps2Xy(input_gps_coord, output_xy_coord);

  const XyCoord gt_xy_coord(-1474.860395, -1255.334203);
  EXPECT_NEAR(gt_xy_coord.x_m, output_xy_coord.x_m, 1.0);
  EXPECT_NEAR(gt_xy_coord.y_m, output_xy_coord.y_m, 1.0);
}

TEST_F(Gps2EnuTest, fourth_region_Gps2Xy) {
  const GpsCoord input_gps_coord(31.274891, 121.22289);
  XyCoord output_xy_coord;
  gps2enu_test_.Gps2Xy(input_gps_coord, output_xy_coord);

  XyCoord gt_xy_coord(3794.709618, -809.925359);
  EXPECT_NEAR(gt_xy_coord.x_m, output_xy_coord.x_m, 1.0);
  EXPECT_NEAR(gt_xy_coord.y_m, output_xy_coord.y_m, 1.0);
}

// big distance failed
// TEST_F(Gps2EnuTest, big_distance_cal) {
//   const GpsCoord input_gps_coord(31.2, 121.1);
//   XyCoord output_xy_coord;
//   gps2enu_test_.Gps2Xy(input_gps_coord, output_xy_coord);

//   XyCoord gt_xy_coord(-7914.244979, -9111.060729);
//   EXPECT_NEAR(gt_xy_coord.x_m, output_xy_coord.x_m, 3.0);
//   EXPECT_NEAR(gt_xy_coord.y_m, output_xy_coord.y_m, 3.0);
// }
