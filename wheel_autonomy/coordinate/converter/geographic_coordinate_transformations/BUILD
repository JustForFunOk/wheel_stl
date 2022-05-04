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
    name = "geographic_coordinate_transformations",
    srcs = ["geographic_coordinate_transformations.cpp"],
    hdrs = ["geographic_coordinate_transformations.h"],
    deps = [
        "@eigen",
    ],
)

cc_test(
    name = "test_geodetic2enu",
    srcs = ["test_geodetic2enu.cpp"],
    deps = [
        "geographic_coordinate_transformations",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)