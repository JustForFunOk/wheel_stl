#pragma once

struct GpsCoord {
  GpsCoord() {}
  GpsCoord(double _lat_deg, double _lon_deg)
      : lat_deg(_lat_deg), lon_deg(_lon_deg) {}
  double lat_deg;
  double lon_deg;
};

struct XyCoord {
  XyCoord() {}
  XyCoord(double _x_m, double _y_m) : x_m(_x_m), y_m(_y_m) {}
  double x_m;
  double y_m;
};

/**
 * @brief This class is used to convert coordinate between gps and x-y
 * coordinate system. The x-y coordinate system is Cartesian coordinate system
 * and is right hand rule. Set a initial gps coordinate as the origin of x-y
 * coordinate system. And then, you can transform coordinate between gps and xy.
 */
class Gps2Enu {
 public:
  /** @brief Constructor of Gps2Enu class.
   *
   * @param _origin Latitude and longitude of origin point.
   * @param _yaw Yaw angle in origin point. It comes directly from the GPS
   * output. If not specfied, It will calculate the delta X(east direction) and
   * delta Y(north direction)of two input gps coordinate. If specfied, the
   * x-axis and y-axis direction is the same as the direction of VCS(vehicle
   * coordinate system) in origin point.
   */
  explicit Gps2Enu(const GpsCoord& _origin, double _yaw_deg = -90.0);

  /** @brief Calculate the (x,y) coordinate of input GPS coordinate.
   * @param _input_gps Latitude and longitude of input GPS point.
   * @param _output_xy (x,y) coordinate of input GPS point.
   */
  void Gps2Xy(const GpsCoord& _input_gps, XyCoord& _output_xy);

 private:
  void ComputeRmRn();

 private:
  struct CoordSystem {
    GpsCoord origin_point;
    double z_rotate_deg;  // the rotated degree of z-axis compared to ENU
  } xy_coord_system_;

  double L_;
  double R_M_;
  double R_N_;
};  // class
