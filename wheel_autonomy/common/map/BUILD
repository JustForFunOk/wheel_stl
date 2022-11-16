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
    name = "lane_id",
    srcs = [
        "lane_id.cpp",
    ],
    hdrs = [
        "lane_id.h",
    ],
)

######################################TEST#####################################

cc_test(
    name = "lane_id_test",
    srcs = [
        "lane_id_test.cpp",
    ],
    deps = [
        "@gtest",
        "@gtest//:gtest_main",
        ":lane_id"
    ],
)