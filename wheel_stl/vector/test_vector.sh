#!/bin/bash

ROOT_PATH=$(git rev-parse --show-toplevel)

bazel test //wheel_stl/vector:test_wheelstl_vector --test_output=all