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
    name = "gps2enu",
    srcs = ["gps2enu.cpp"],
    hdrs = ["gps2enu.h"],
)

cc_test(
    name = "test_gps2enu",
    srcs = ["test_gps2enu.cpp"],
    deps = [
        "gps2enu",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)