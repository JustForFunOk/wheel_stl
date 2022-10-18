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
    name = "lru",
    srcs = [
        "lru.cpp",
        "lru.h",
    ],
    deps = [
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "test_lru",
    srcs = [
        "test_lru.cpp",
    ],
    deps = [
        ":lru",
    ],
)