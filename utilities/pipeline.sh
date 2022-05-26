#!/bin/bash

# echo with color
# Reference: https://stackoverflow.com/questions/5947742/how-to-change-the-output-color-of-echo-in-linux
RED='\033[0;31m'    # Error
YELLOW='\033[0;33m' # Warning
GREEN='\033[0;32m'  # OK
BLUE='\033[0;34m'   # Command
PURPLE='\033[0;35m' # Remind
NOCOLOR='\033[0m'  # remeber set NOCOLOR after use color echo

# test color
function test_color_echo() {
  echo -e "${RED}RED${YELLOW}YELLOW${GREEN}GREEN${BLUE}BLUE${PURPLE}PURPLE${NOCOLOR}NOCOLOR"
}

function echo_warning() {
  echo -e "${YELLOW}$1${NOCOLOR}"
}

function echo_error() {
  echo -e "${RED}$1${NOCOLOR}"
}

function echo_command() {
  echo -e "${BLUE}$1${NOCOLOR}"
}

function echo_remind() {
  echo -e "${PURPLE}$1${NOCOLOR}"
}

function install_clang_format() {
  if [[ "$(uname -s)" == "Darwin"* ]]; then
    echo_command "brew install clang-format"
    brew install clang-format
  else
    echo_command "sudo apt install clang-format"
    sudo apt install clang-format
  fi
}

function install_cppcheck() {
  if [[ "$(uname -s)" == "Darwin"* ]]; then
    echo_command "brew install cppcheck"
    brew install cppcheck
  else
    echo_command "sudo apt install cppcheck"
    sudo apt install cppcheck
  fi
}

function cd_to_git_root_path() {
  repo_path=$(git rev-parse --show-toplevel)
  echo_command "cd ${repo_path}"
  cd ${repo_path}
}

# Forbid to use 'clang-format' as function name
function clang_format() {
  echo_remind "\n-------------------clang-format-------------------"

  # Check clang-format is installed
  if ! $(clang-format --version >/dev/null); then
    echo_warning "Unable to locate clang-format. Start install clang-format..."
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
  find . -type f -name "*.h" -or -name "*.cc" -or -name "*.cpp" -or -name "*.c" -or -name "*.hpp" \
    | grep -v $(printf -- "-f %s " $(find . -name \*.clangformatignore)) \
    | xargs clang-format -style=file -i '{}'  # Use -style=file to
                                              # load style configuration from .clang-format file
  echo "End of clang-format..."
  echo "Cost $SECONDS sec."
}

function cpp_lint() {
  echo_remind"\n----------------------cpplint---------------------"

  # cd to git root path
  cd_to_git_root_path

  echo "Start cpplint..."
  SECONDS=0
  # grep -v to filter the file in .cpplintignore
  find . -type f -name "*.h" -or -name "*.cc" -or -name "*.cpp" -or -name "*.c" -or -name "*.hpp" \
    | grep -v $(printf -- "-f %s " $(find . -name \*.cpplintignore)) \
    | xargs ./utilities/cpplint/cpplint.py --counting=detailed --quiet
  echo "End of cpplint"

  echo "Cost $SECONDS sec."
}

# Forbid to use "cppcheck" as function name
function cpp_check() {
  echo_remind "\n----------------------cppcheck---------------------"

  # Check cppcheck is installed
  if ! $(cppcheck --version >/dev/null); then
    echo_warning "Unable to locate cppcheck. Start install cppcheck..."
    install_cppcheck
  else
    echo "cppcheck version: $(cppcheck --version)"
  fi

  # cd to git root path
  cd_to_git_root_path

  # cppcheck for the folder that contain BUILD file
  # '-mindepth 2' filter the BUILD in root path
  # 'xargs -n1 dirname' get the directory path
  find . -mindepth 2 -type f -name BUILD | sort --unique  \
    | grep -v $(printf -- "-f %s " $(find . -name \*.cppcheckignore)) | xargs -n1 dirname \
    | xargs -I {} cppcheck {}
}


function bazel_build() {
  echo_remind "\n---------------------bazel build------------------------"
  # build all
  echo_command "bazel build ... --disk_cache=~/.wheel_stl_bazel_cache"
  bazel build ... --disk_cache=~/.wheel_stl_bazel_cache
}

function unit_test() {
  echo_remind "\n----------------------unit test-------------------------"
  # run unit test
  echo_command "bazel test ... --test_output=all"
  bazel test ... --test_output=all
}

function code_coverage() {
  echo_remind "\n----------------------code coverage---------------------"

  # check gcov
  gcovr --version  # return 0 if gcov has installed
  if [ $? -ne 0 ]; then
    echo_warning "Unable to locate gcovr. Start install gcovr..."
    echo_command "sudo apt install gcovr"
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
  echo_command "sudo timedatectl set-timezone Asia/Shanghai"
  sudo timedatectl set-timezone Asia/Shanghai
  echo -e "After: $(date)"
}

# enable run function in command line
# https://stackoverflow.com/questions/8818119/how-can-i-run-a-function-from-a-script-in-command-line
# for example: ./pipeline.sh  code_coverage
"$@"
