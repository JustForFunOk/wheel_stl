#pragma once

/**
 * @brief lookup table (LUT) is an array that replaces runtime computation with
 * a simpler array indexing operation.
 * Reference: https://en.wikipedia.org/wiki/Lookup_table
 */

namespace wheel_autonomy {
namespace common {
namespace lut {

/**
 * @brief Calculate atan2 by look up pre-calculated atan table.
 *
 * Interface: Same interface definition with std::atan2().
 *
 * Performance: 2x faster compare with std::atan2().
 *
 * Precision: angle error less than +/-0.0057degree. check result:
 * https://colab.research.google.com/drive/1NBfbYWmgYCfvwGvAvaD70x6zJZMgLbat#scrollTo=sBPSjbXN2CsI
 */
float Atan2LookUp(float y, float x);

}  // namespace lut
}  // namespace common
}  // namespace wheel_autonomy
