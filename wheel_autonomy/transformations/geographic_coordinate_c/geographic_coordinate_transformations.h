#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Reference: https://en.wikipedia.org/wiki/Geodetic_coordinates
typedef struct {
  double lat_deg;
  double lon_deg;
  double alt_m;
} Geodetic;

// Reference: https://en.wikipedia.org/wiki/Local_tangent_plane_coordinates
typedef struct {
  double e_m;
  double n_m;
  double u_m;
} ENU;

// Reference:
// https://en.wikipedia.org/wiki/Earth-centered,_Earth-fixed_coordinate_system
typedef struct {
  double x_m;
  double y_m;
  double z_m;
} ECEF;

extern void SetLocalOrigin(const Geodetic* _local_origin);
extern ENU Geodetic2ENU(const Geodetic* _geodetic_coord);

#ifdef __cplusplus
}  // extern "C"
#endif