load("@com_github_bazelbuild_buildtools//buildifier:def.bzl", "buildifier")

package(default_visibility = ["//visibility:public"])

buildifier(
    name = "buildifier",
    lint_mode = "warn",
    mode = "check",
    verbose = True,
)

cc_library(
    name = "lut",
    srcs = [
        "lut.cpp",
    ],
    hdrs = [
        "lut.h",
    ],
)
