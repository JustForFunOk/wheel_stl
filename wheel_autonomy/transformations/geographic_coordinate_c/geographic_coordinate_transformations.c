#include "geographic_coordinate_transformations.h"

#include <math.h>  // sin cos pow M_PI
#include <stdio.h>

// Reference: https://en.wikipedia.org/wiki/World_Geodetic_System
#define kWGS84EarthMajorAxisM 6378137.0            // a
#define kWGS84EarthFlattening (1 / 298.257223563)  // f = (a-b)/a
// e^2 = 1-(b^2)/(a^2) = f*(2-f)
#define kE2 (kWGS84EarthFlattening * (2.0 - kWGS84EarthFlattening))

#define Deg2Rad(_degree) (_degree / 180.0 * M_PI)

// Matrix multiply C=AB
#define A_ROW 3
#define A_COL 3
#define B_ROW A_COL
#define B_COL 1
#define C_ROW A_ROW
#define C_COL B_COL

// the ECEF coordinate of ENU coordinate system origin point
static ECEF local_origin_;

static double ecef2enu_matrix_3d_[3][3];  // 3x3 matrix

/** @brief Convert Geodetic coordinate to ECEF coordinate.
 *
 * Formula Reference:
 * https://en.wikipedia.org/wiki/Geographic_coordinate_conversion#From_geodetic_to_ECEF_coordinates
 * The annotations below in the code are correspond to formula.
 *
 * Code Reference1: "pos2ecef()" in
 * https://github.com/tomojitakasu/RTKLIB/blob/master/src/rtkcmn.c Code
 * Reference2: "geodetic2ecef()" in
 * https://github.com/commaai/openpilot/blob/master/common/transformations/coordinates.cc
 *
 * @param _geodetic_coord Geodetic coordinate
 * @return  ECEF coordinate
 */
static ECEF Geodetic2ECEF(const Geodetic* _geodetic_coord) {
  const double lat_rad = Deg2Rad(_geodetic_coord->lat_deg);  // phi
  const double lon_rad = Deg2Rad(_geodetic_coord->lon_deg);  // lambda
  const double h       = _geodetic_coord->alt_m;             // h

  const double sin_lat = sin(lat_rad);  // sin(phi)
  const double cos_lat = cos(lat_rad);  // cos(phi)
  const double sin_lon = sin(lon_rad);  // sin(lambda)
  const double cos_lon = cos(lon_rad);  // cos(lambda)

  const double N_lat =
      kWGS84EarthMajorAxisM / sqrt(1.0 - kE2 * sin_lat * sin_lat);  // N(phi)

  const double x = (N_lat + h) * cos_lat * cos_lon;    // X
  const double y = (N_lat + h) * cos_lat * sin_lon;    // Y
  const double z = ((1 - kE2) * N_lat + h) * sin_lat;  // Z

  ECEF ecef_coord;
  ecef_coord.x_m = x;
  ecef_coord.y_m = y;
  ecef_coord.z_m = z;
  return ecef_coord;
}

static void Matrix3dMultiplyVector3d(const double _left_matrix_3d[3][3],
                                     const double _right_vector_3d[3][1],
                                     double _output_vector_3d[3][1]) {
  for (int i = 0; i < A_ROW; ++i) {
    for (int j = 0; j < B_COL; ++j) {
      _output_vector_3d[i][j] = 0.0;
      for (int k = 0; k < B_ROW; ++k) {
        _output_vector_3d[i][j] +=
            _left_matrix_3d[i][k] * _right_vector_3d[k][j];
      }
    }
  }
}

/** @brief Init the transformation matrix from ECEF to ENU.
 *
 * Formula Reference:
 * https://en.wikipedia.org/wiki/Geographic_coordinate_conversion#From_ECEF_to_ENU
 * The variable name below in the code are correspond to formula.
 *
 * Code Reference1: "xyz2enu()" in
 * https://github.com/tomojitakasu/RTKLIB/blob/master/src/rtkcmn.c
 *
 * @param _geodetic_coord Geodetic coordinate
 * @return  void
 */
static void InitECEF2ENUMatrix(const Geodetic* _geodetic_coord) {
  const double lat_rad = Deg2Rad(_geodetic_coord->lat_deg);
  const double lon_rad = Deg2Rad(_geodetic_coord->lon_deg);

  const double sin_phi    = sin(lat_rad);  // sin(phi)
  const double cos_phi    = cos(lat_rad);  // cos(phi)
  const double sin_lambda = sin(lon_rad);  // sin(lambda)
  const double cos_lambda = cos(lon_rad);  // cos(lambda)

  //  |     -sin_lambda            cos_lambda           0      |
  //  | -sin_phi * cos_lambda  -sin_phi * sin_lambda  cos_phi  |
  //  |  cos_phi * cos_lambda   cos_phi * sin_lambda  sin_phi  |
  ecef2enu_matrix_3d_[0][0] = -sin_lambda;
  ecef2enu_matrix_3d_[0][1] = cos_lambda;
  ecef2enu_matrix_3d_[0][2] = 0;
  ecef2enu_matrix_3d_[1][0] = -sin_phi * cos_lambda;
  ecef2enu_matrix_3d_[1][1] = -sin_phi * sin_lambda;
  ecef2enu_matrix_3d_[1][2] = cos_phi;
  ecef2enu_matrix_3d_[2][0] = cos_phi * cos_lambda;
  ecef2enu_matrix_3d_[2][1] = cos_phi * sin_lambda;
  ecef2enu_matrix_3d_[2][2] = sin_phi;
}

void SetLocalOrigin(const Geodetic* _local_origin) {
  local_origin_ = Geodetic2ECEF(_local_origin);
  // printf("local_origin_.x_m = %f", local_origin_.x_m);
  // printf("local_origin_.y_m = %f", local_origin_.y_m);
  // printf("local_origin_.z_m = %f", local_origin_.z_m);

  InitECEF2ENUMatrix(_local_origin);
}

/** @brief Convert Geodetic coordinate to ENU coordinate.
 *
 * Formula Reference:
 * https://en.wikipedia.org/wiki/Geographic_coordinate_conversion#Geodetic_to/from_ENU_coordinates
 * The variable name below in the code are correspond to formula.
 *
 * Code Reference1: "ecef2enu()" in
 * https://github.com/tomojitakasu/RTKLIB/blob/master/src/rtkcmn.c
 *
 * @param _geodetic_coord Geodetic coordinate
 * @return  ENU coordinate
 */
ENU Geodetic2ENU(const Geodetic* _geodetic_coord) {
  // Step 1: Convert geodetic to ECEF
  ECEF ecef_coord = Geodetic2ECEF(_geodetic_coord);

  // Step 2: Convert ECEF vector to ENU vector
  double delta_x = ecef_coord.x_m - local_origin_.x_m;
  double delta_y = ecef_coord.y_m - local_origin_.y_m;
  double delta_z = ecef_coord.z_m - local_origin_.z_m;

  double ecef_vector_3d[3][1];
  ecef_vector_3d[0][0] = delta_x;
  ecef_vector_3d[1][0] = delta_y;
  ecef_vector_3d[2][0] = delta_z;

  double enu_vector_3d[3][1];
  Matrix3dMultiplyVector3d(ecef2enu_matrix_3d_, ecef_vector_3d, enu_vector_3d);

  ENU enu_coord;
  enu_coord.e_m = enu_vector_3d[0][0];
  enu_coord.n_m = enu_vector_3d[1][0];
  enu_coord.u_m = enu_vector_3d[2][0];
  return enu_coord;
}