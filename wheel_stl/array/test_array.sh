#!/bin/bash

ROOT_PATH=$(git rev-parse --show-toplevel)

bazel test //wheel_stl/array:test_wheelstl_array --test_output=all