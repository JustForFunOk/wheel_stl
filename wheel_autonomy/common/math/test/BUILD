load("@rules_cc//cc:defs.bzl", "cc_test")
load("@com_github_bazelbuild_buildtools//buildifier:def.bzl", "buildifier")

package(default_visibility = ["//visibility:public"])

buildifier(
    name = "buildifier",
    lint_mode = "warn",
    mode = "check",
    verbose = True,
)

cc_test(
    name = "test_vec2",
    srcs = [
        "test_vec2.cpp",
    ],
    deps = [
        "@gtest",
        "@gtest//:gtest_main",
        "@eigen",
        "//wheel_autonomy/common/math:vec2"
    ],
)

cc_test(
    name = "test_line_segment2",
    srcs = [
        "test_line_segment2.cpp",
    ],
    deps = [
        "@gtest",
        "@gtest//:gtest_main",
        "//wheel_autonomy/common/math:line_segment2"
    ],
)

cc_test(
    name = "test_polygon2",
    srcs = [
        "test_polygon2.cpp",
    ],
    deps = [
        "@gtest",
        "@gtest//:gtest_main",
        "//wheel_autonomy/common/math:polygon2"
    ],
)

cc_test(
    name = "test_rectangle2",
    srcs = [
        "test_rectangle2.cpp",
    ],
    deps = [
        "@gtest",
        "@gtest//:gtest_main",
        "//wheel_autonomy/common/math:rectangle2"
    ],
)
