load("@rules_cc//cc:defs.bzl", "cc_test")
load("@com_github_bazelbuild_buildtools//buildifier:def.bzl", "buildifier")

package(default_visibility = ["//visibility:public"])

buildifier(
    name = "buildifier",
    lint_mode = "warn",
    mode = "check",
    verbose = True,
)

cc_library(
    name = "geographic_coordinate_transformations_c",
    srcs = ["geographic_coordinate_transformations.c"],
    hdrs = ["geographic_coordinate_transformations.h"],
)

cc_test(
    name = "test_geodetic2enu_c",
    srcs = ["test_geodetic2enu_c.cpp"],
    deps = [
        "geographic_coordinate_transformations_c",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)