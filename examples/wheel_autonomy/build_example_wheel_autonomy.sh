#!/bin/bash

bazel build //examples/wheel_autonomy:test_eigen
bazel run //examples/wheel_autonomy:test_eigen