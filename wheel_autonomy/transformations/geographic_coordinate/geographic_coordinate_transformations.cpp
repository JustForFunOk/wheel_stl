#include "geographic_coordinate_transformations.hpp"

#include <Eigen/Dense>
#include <cmath>  // sin cos pow M_PI

namespace {
// Reference: https://en.wikipedia.org/wiki/World_Geodetic_System
static const double kWGS84EarthMajorAxisM = 6378137.0;          // a
static const double kWGS84EarthFlattening = 1 / 298.257223563;  // f = (a-b)/a

// e^2 = 1-(b^2)/(a^2) = f*(2-f)
static const double kE2 = kWGS84EarthFlattening * (2.0 - kWGS84EarthFlattening);

inline double Deg2Rad(double _degree) { return _degree / 180.0 * M_PI; }

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
ECEF Geodetic2ECEF(const Geodetic& _geodetic_coord) {
  const double lat_rad = Deg2Rad(_geodetic_coord.lat_deg);  // phi
  const double lon_rad = Deg2Rad(_geodetic_coord.lon_deg);  // lambda
  const double h       = _geodetic_coord.alt_m;             // h

  const double sin_lat = sin(lat_rad);  // sin(phi)
  const double cos_lat = cos(lat_rad);  // cos(phi)
  const double sin_lon = sin(lon_rad);  // sin(lambda)
  const double cos_lon = cos(lon_rad);  // cos(lambda)

  const double N_lat =
      kWGS84EarthMajorAxisM / sqrt(1.0 - kE2 * sin_lat * sin_lat);  // N(phi)

  const double x = (N_lat + h) * cos_lat * cos_lon;    // X
  const double y = (N_lat + h) * cos_lat * sin_lon;    // Y
  const double z = ((1 - kE2) * N_lat + h) * sin_lat;  // Z

  return {x, y, z};
}

}  // namespace

LocalCoord::LocalCoord(const Geodetic& _local_origin) {
  local_origin_ = Geodetic2ECEF(_local_origin);

  InitECEF2ENUMatrix(_local_origin);
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
void LocalCoord::InitECEF2ENUMatrix(const Geodetic& _geodetic_coord) {
  const double lat_rad = Deg2Rad(_geodetic_coord.lat_deg);
  const double lon_rad = Deg2Rad(_geodetic_coord.lon_deg);

  const double sin_phi    = sin(lat_rad);  // sin(phi)
  const double cos_phi    = cos(lat_rad);  // cos(phi)
  const double sin_lambda = sin(lon_rad);  // sin(lambda)
  const double cos_lambda = cos(lon_rad);  // cos(lambda)

  ecef2enu_matrix_3d_ << -sin_lambda, cos_lambda, 0, -sin_phi * cos_lambda,
      -sin_phi * sin_lambda, cos_phi, cos_phi * cos_lambda,
      cos_phi * sin_lambda, sin_phi;
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
ENU LocalCoord::Geodetic2ENU(const Geodetic& _geodetic_coord) {
  // Step 1: Convert geodetic to ECEF
  ECEF ecef_coord = Geodetic2ECEF(_geodetic_coord);

  // Step 2: Convert ECEF vector to ENU vector
  double delta_x = ecef_coord.x_m - local_origin_.x_m;
  double delta_y = ecef_coord.y_m - local_origin_.y_m;
  double delta_z = ecef_coord.z_m - local_origin_.z_m;
  Eigen::Vector3d ecef_vector(delta_x, delta_y, delta_z);

  Eigen::Vector3d enu_vector = ecef2enu_matrix_3d_ * ecef_vector;

  double e = enu_vector[0];
  double n = enu_vector[1];
  double u = enu_vector[2];

  return {e, n, u};
}