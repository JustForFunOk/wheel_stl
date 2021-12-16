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
    name = "test_official_vector",
    srcs = ["test_official_vector.cpp"],
    deps = [
        "@gtest",
        "@gtest//:gtest_main",
    ],
)