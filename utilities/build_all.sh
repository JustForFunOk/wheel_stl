#!/bin/bash

# get the root path of git repository
repo_path=$(git rev-parse --show-toplevel)

cd $repo_path

echo "Current Path: $(pwd)"

# Check code style
./utilities/format_code.sh

# build
./utilities/pipeline.sh bazel_build

# test
./utilities/pipeline.sh unit_test

# code coverage
if [[ "$(uname -s)" == "Darwin"* ]]; then
  echo "[code coverage] does not work no macos, skip..."
else
  ./utilities/pipeline.sh code_coverage
fi