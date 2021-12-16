#!/bin/bash

ROOT_PATH=$(git rev-parse --show-toplevel)

bazel test //wheel_stl/vector:test_official_vector --test_output=all