#!/bin/bash

# Exit immediately if a command failed
set -e

# Cd to the root path of git repository
repo_path=$(git rev-parse --show-toplevel)
echo "Current git root path: $repo_path"
cd $repo_path

# Check code style
./utilities/pipeline.sh clang_format

# Check cpplint
./utilities/pipeline.sh cpplint

# Bazel build
./utilities/pipeline.sh bazel_build

# Bazel test
./utilities/pipeline.sh unit_test

# Code coverage
if [[ "$(uname -s)" == "Darwin"* ]]; then
  echo -e "\n[code coverage] does not work no macos, skip..."
else
  ./utilities/pipeline.sh code_coverage
fi
