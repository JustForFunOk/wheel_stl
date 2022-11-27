#include "wheel_autonomy/common/lookup_table/lut.h"

#include <gtest/gtest.h>
#include <chrono>  // check performance
#include <cmath>   // use std::ata2 as ground truth
#include <random>  // generate random test data

TEST(LUT, Atan2LookUp) {
  // (y, x)
  std::vector<std::pair<float, float>> test_case = {
      {0.0f, 0.0f},    // x == 0 && y == 0
      {-3.0f, -5.0f},  // -180 < degree < -135
      {-5.0f, -5.0f},  // -135
      {-5.0f, -3.0f},  // -135 < degree < -90
      {-5.0f, 0.0f},   // -90
      {-5.0f, 3.0f},   // -90 < degree < -45
      {-5.0f, 5.0f},   // -45
      {-3.0f, 5.0f},   // -45 < degree < 0
      {0.0f, 5.0f},    // 0
      {3.0f, 5.0f},    // 0 < degree < 45
      {5.0f, 5.0f},    // 45
      {5.0f, 3.0f},    // 45 < degree < 90
      {5.0f, 0.0f},    // 90
      {5.0f, -3.0f},   // 90 < degree < 135
      {5.0f, -5.0f},   // 135
      {3.0f, -5.0f},   // 135 < degree < 180
      {0.0f, -5.0f},   // 180
  };

  for (std::size_t i = 0; i < test_case.size(); ++i) {
    float y = test_case[i].first;
    float x = test_case[i].second;
    EXPECT_NEAR(std::atan2(y, x),
                ::wheel_autonomy::common::lut::Atan2LookUp(y, x),
                0.0001);  // 0.0001rad, 0.0057degree
  }
}

TEST(LUT, Atan2LookUpPerformance) {
  // generate random number in range [-200.0, 200.0]
  const int sample_size = 70000;
  std::vector<float> random_sample_x(sample_size);
  std::vector<float> random_sample_y(sample_size);
  for (std::size_t i = 0; i < sample_size; ++i) {
    random_sample_x[i] =
        static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 400 - 200;
    random_sample_y[i] =
        static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 400 - 200;
  }

  // evaluate precision
  for (std::size_t i = 0; i < sample_size; ++i) {
    float y = random_sample_y[i];
    float x = random_sample_x[i];
    EXPECT_NEAR(std::atan2(y, x),
                ::wheel_autonomy::common::lut::Atan2LookUp(y, x),
                0.0001);  // 0.0001rad, 0.0057degree
  }

  // evaluate performance
  std::chrono::steady_clock::time_point t1, t2;
  std::chrono::duration<double> time_span;
  t1 = std::chrono::steady_clock::now();
  for (std::size_t i = 0; i < sample_size; ++i) {
    std::atan2(random_sample_y[i], random_sample_x[i]);
  }
  t2 = std::chrono::steady_clock::now();
  time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "std::atan2  cost: " << time_span.count();

  t1 = std::chrono::steady_clock::now();
  for (std::size_t i = 0; i < sample_size; ++i) {
    ::wheel_autonomy::common::lut::Atan2LookUp(random_sample_y[i],
                                               random_sample_x[i]);
  }
  t2 = std::chrono::steady_clock::now();
  time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "Atan2LookUp cost: " << time_span.count();
}