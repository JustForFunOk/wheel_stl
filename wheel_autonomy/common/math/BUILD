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
    name = "vec2",
    hdrs = [
        "vec2.h",
    ],
)

cc_library(
    name = "point2",
    hdrs = [
        "point2.h",
    ],
    deps = [
        ":vec2",
    ],
)

cc_library(
    name = "line_segment2",
    hdrs = [
        "line_segment2.h",
    ],
    deps = [
        ":point2",
    ],
)

cc_library(
    name = "polygon2",
    hdrs = [
        "polygon2.h",
    ],
    deps = [
        ":point2",
        ":line_segment2",
    ],
)

cc_library(
    name = "rectangle2",
    hdrs = [
        "rectangle2.h",
    ],
    deps = [
        ":point2",
    ],
)

######################################TEST#####################################

cc_test(
    name = "vec2_test",
    srcs = [
        "vec2_test.cpp",
    ],
    deps = [
        "@gtest",
        "@gtest//:gtest_main",
        "@eigen",
        ":vec2"
    ],
)

cc_test(
    name = "line_segment2_test",
    srcs = [
        "line_segment2_test.cpp",
    ],
    deps = [
        "@gtest",
        "@gtest//:gtest_main",
        ":line_segment2"
    ],
)

cc_test(
    name = "polygon2_test",
    srcs = [
        "polygon2_test.cpp",
    ],
    deps = [
        "@gtest",
        "@gtest//:gtest_main",
        ":polygon2"
    ],
)

cc_test(
    name = "rectangle2_test",
    srcs = [
        "rectangle2_test.cpp",
    ],
    deps = [
        "@gtest",
        "@gtest//:gtest_main",
        ":rectangle2"
    ],
)