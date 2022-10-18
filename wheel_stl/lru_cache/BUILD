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
    name = "lru_cache",
    srcs = [
        "lru_cache.h",
    ],
)

cc_test(
    name = "test_lru_cache",
    srcs = [
        "test_lru_cache.cpp",
    ],
    deps = [
        ":lru_cache",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)