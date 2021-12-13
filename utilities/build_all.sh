#!/bin/bash

# get the root path of git repository
repo_path=$(git rev-parse --show-toplevel)

cd $repo_path

echo "Current Path: $(pwd)"

# build all
bazel build ... --disk_cache=~/.wheel_stl_bazel_cache