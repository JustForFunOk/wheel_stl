#!/bin/bash

function bazel_build() {
  echo -e "\n---------------------bazel test-------------------------"
  # build all
  bazel build ... --disk_cache=~/.wheel_stl_bazel_cache
}

function unit_test() {
  echo -e "\n----------------------unit test-------------------------"
  # run unit test
  bazel test ... --test_output=all
}

function code_coverage() {
  echo -e "\n----------------------code coverage---------------------"

  # check gcov
  gcovr --version  # return 0 if gcov has installed
  if [ $? -ne 0 ]; then
    sudo apt install gcovr
  fi

  # code coverage
  # 1
  # WARNING: Option 'javabase' is deprecated  (bazel version 5.1.1)
  # --javabase=@bazel_tools//tools/jdk:remote_jdk11 \
  # 2
  # macos use llvm which does not support gcov
  # https://stackoverflow.com/questions/7988355/getting-0-gcov-coverage-for-a-mac-app
  # --experimental_use_llvm_covmap \
  bazel coverage \
  --instrument_test_targets \
  --experimental_cc_coverage \
  --combined_report=lcov \
  --coverage_report_generator=@bazel_tools//tools/test/CoverageOutputGenerator/java/com/google/devtools/coverageoutputgenerator:Main \
  --java_runtime_version=remotejdk_11 \
  //...

  # generate html to ./bazel-out/code_coverage folder
  genhtml --output ./bazel-out/code_coverage "$(bazel info output_path)/_coverage/_coverage_report.dat"
}

# enable run function in command line
# https://stackoverflow.com/questions/8818119/how-can-i-run-a-function-from-a-script-in-command-line
# for example: ./pipeline.sh  code_coverage
"$@"