#pragma once

// fix eigen display bug in vscode
// https://github.com/microsoft/vscode-cpptools/issues/7413#issuecomment-827172897
#if __INTELLISENSE__
#undef __ARM_NEON
#undef __ARM_NEON__
#endif

#include <Eigen/Dense>

// Reference: https://en.wikipedia.org/wiki/Geodetic_coordinates
struct Geodetic {
  Geodetic() {}
  Geodetic(double _lat_deg, double _lon_deg, double _alt_m)
      : lat_deg(_lat_deg), lon_deg(_lon_deg), alt_m(_alt_m) {}
  double lat_deg;
  double lon_deg;
  double alt_m;
};

// Reference: https://en.wikipedia.org/wiki/Local_tangent_plane_coordinates
struct ENU {
  ENU() {}
  ENU(double _e_m, double _n_m, double _u_m)
      : e_m(_e_m), n_m(_n_m), u_m(_u_m) {}
  double e_m;
  double n_m;
  double u_m;
};

// Reference:
// https://en.wikipedia.org/wiki/Earth-centered,_Earth-fixed_coordinate_system
struct ECEF {
  ECEF() {}
  ECEF(double _x_m, double _y_m, double _z_m)
      : x_m(_x_m), y_m(_y_m), z_m(_z_m) {}
  double x_m;
  double y_m;
  double z_m;
};

/**
 * @brief This class is used to convert geodetic coordinate to local cartesian.
 */
class LocalCoord {
 public:
  /** @brief Constructor of LocalCoord class.
   *
   * @param _local_origin Geodetic info of local origin point.
   */
  LocalCoord(const Geodetic& _local_origin);

  /** @brief Calculate the local cartesian coordinate of input geodetic
   * coordinate.
   *
   * @param _input_gps Input of Geodetic coordinate.
   *
   * @return Local cartesian coordinate of geodetic point.
   */
  ENU Geodetic2ENU(const Geodetic& _input_geodetic);

 private:
  void InitECEF2ENUMatrix(const Geodetic& _geodetic_coord);

 private:
  ECEF local_origin_;  // the ECEF coordinate of ENU coordinate system origin
                       // point
  Eigen::Matrix3d ecef2enu_matrix_3d_;
};
