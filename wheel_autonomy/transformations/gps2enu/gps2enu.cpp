#include "gps2enu.h"
#include <cmath>  // sin cos pow M_PI

namespace {
// Reference: https://en.wikipedia.org/wiki/World_Geodetic_System
static const double kEarthRadiusM    = 6378137.0;
static const double kEarthFlattening = 1 / 298.257223563;

inline double Deg2Rad(double _degree) { return _degree / 180.0 * M_PI; }
}  // namespace

Gps2Enu::Gps2Enu(const GpsCoord& _origin, double _yaw_deg) {
  xy_coord_system_.origin_point = _origin;
  xy_coord_system_.z_rotate_deg = _yaw_deg + 90.0;

  ComputeRmRn();
}

void Gps2Enu::ComputeRmRn() {
  L_   = Deg2Rad(xy_coord_system_.origin_point.lat_deg);
  R_M_ = kEarthRadiusM * pow(1 - kEarthFlattening, 2.0) *
         pow(1. - (2. - kEarthFlattening) * kEarthFlattening * pow(sin(L_), 2.),
             -3 / 2.);
  R_N_ = kEarthRadiusM *
         pow(1. - (2. - kEarthFlattening) * kEarthFlattening * pow(sin(L_), 2.),
             -0.5);
}

void Gps2Enu::Gps2Xy(const GpsCoord& _input_gps, XyCoord& _output_xy) {
  const double d_lat_deg =
      _input_gps.lat_deg - xy_coord_system_.origin_point.lat_deg;
  const double d_lon_deg =
      _input_gps.lon_deg - xy_coord_system_.origin_point.lon_deg;

  const double d_N = Deg2Rad(d_lat_deg) * R_M_;  // unit=m
  const double d_E = Deg2Rad(d_lon_deg) * (R_N_ * cos(L_));

  const double distance = sqrt(pow(d_N, 2) + pow(d_E, 2));

  double beta = 0;
  if (d_N >= 0 && d_E > 0) {  // first region
    beta = asin(d_N / distance);
  } else if (d_N > 0 && d_E <= 0) {  // second region
    beta = M_PI - asin(d_N / distance);
  } else if (d_N <= 0 && d_E < 0) {  // third region
    beta = M_PI - asin(d_N / distance);
  } else if (d_N < 0 && d_E >= 0) {  // fourth region
    beta = asin(d_N / distance);
  }
  double theta = beta + Deg2Rad(xy_coord_system_.z_rotate_deg);

  _output_xy.x_m = distance * cos(theta);
  _output_xy.y_m = distance * sin(theta);
}
