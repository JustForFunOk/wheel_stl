#!/bin/bash

# get the root path of git repository
repo_path=$(git rev-parse --show-toplevel)

cd $repo_path

echo "Current Path: $(pwd)"

# Check code style
./utilities/format_code.sh

# build all
bazel build ... --disk_cache=~/.wheel_stl_bazel_cache

# run uint test
bazel test ... --test_output=all

# code coverage
bazel coverage --instrument_test_targets --experimental_cc_coverage --combined_report=lcov --coverage_report_generator=@bazel_tools//tools/test/CoverageOutputGenerator/java/com/google/devtools/coverageoutputgenerator:Main  //wheel_autonomy/transformations/geographic_coordinate/...
genhtml --output genhtml "$(bazel info output_path)/_coverage/_coverage_report.dat"