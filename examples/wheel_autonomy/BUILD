load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@com_github_bazelbuild_buildtools//buildifier:def.bzl", "buildifier")

package(default_visibility = ["//visibility:public"])

buildifier(
    name = "buildifier",
    lint_mode = "warn",
    mode = "check",
    verbose = True,
)

cc_binary(
    name = "test_eigen",
    srcs = ["test_eigen.cpp"],
    deps = [
        "@eigen",
    ],
)