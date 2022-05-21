#!/bin/bash

function install_clang_format() {
  if [[ "$(uname -s)" == "Darwin"* ]]; then
    echo "brew install clang-format"
    brew install clang-format
  else
    echo "sudo apt install clang-format"
    sudo apt install clang-format
  fi
}

function cd_to_git_root_path() {
  repo_path=$(git rev-parse --show-toplevel)
  echo "Change current path to git root path: ${repo_path}"
  cd ${repo_path}
}

function clang_format() {
  echo -e "\n-------------------clang-format-------------------"

  # Check clang-format is installed
  if ! $(clang-format --version &>/dev/null); then
    echo "Unable to locate clang-format. Start install clang-format..."
    install_clang_format
  else
    echo "clang-format version: $(clang-format --version)"
  fi

  # cd to git root path
  cd_to_git_root_path

  echo "Start clang-format for every file in current folder..."
  # SECONDS is bash builtin variable that tracks the number of seconds
  # that have passed since the shell was started
  SECONDS=0
  find ${repo_path} -type f -name "*.h" -or -name "*.cc" -or -name "*.cpp" -or -name "*.c" -or -name "*.hpp"\
    | grep -v $(printf -- "-f %s " $(find $repo_path -name \*.clangformatignore)) \
    | xargs clang-format -style=file -i '{}'  # Use -style=file to
                                              # load style configuration from .clang-format file
  echo "End of clang-format..."
  echo "Cost $SECONDS sec."
}

function cpplint() {
  echo -e "\n----------------------cpplint---------------------"

  # cd to git root path
  cd_to_git_root_path

  echo "Start cpplint..."
  SECONDS=0
  # grep -v to filt the file in .cpplintignore
  find $repo_path -type f -name "*.h" -or -name "*.cc" -or -name "*.cpp"\
    | grep -v $(printf -- "-f %s " $(find $repo_path -name \*.cpplintignore)) \
    | xargs $repo_path/utilities/cpplint/cpplint.py --counting=detailed --quiet
  echo "End of cpplint"

  echo "Cost $SECONDS sec."
}


function bazel_build() {
  echo -e "\n---------------------bazel build------------------------"
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

# workflow runner use UTC as default, change to china timezone
function set_timezone() {
  echo -e "\n----------------------set timezone---------------------"
  echo -e "Before: $(date)"
  sudo timedatectl set-timezone Asia/Shanghai
  echo -e "After: $(date)"
}

# enable run function in command line
# https://stackoverflow.com/questions/8818119/how-can-i-run-a-function-from-a-script-in-command-line
# for example: ./pipeline.sh  code_coverage
"$@"
