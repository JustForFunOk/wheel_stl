#!/bin/bash

# get the root path of git repository
repo_path=$(git rev-parse --show-toplevel)
echo "Current git root path: $repo_path"

# Check clang-format is installed
if ! type -p clang-format >/dev/null; then
  echo "Unable to locate clang-format. Please install it by: 'sudo apt install clang-format' or 'brew install clang-format'"
  exit 1
fi

echo "-------------------clang-format-------------------"
echo "Start clang-format for every file in current folder..."
# SECONDS is bash builtin variable that tracks the number of seconds
# that have passed since the shell was started
SECONDS=0
find $repo_path -type f -name "*.h" -or -name "*.cc" -or -name "*.cpp"\
  | grep -v $(printf -- "-f %s " $(find $repo_path -name \*.clangformatignore)) \
  | xargs clang-format -style=file -i '{}'  # Use -style=file to
                                            # load style configuration from .clang-format file
echo "End of clang-format..."
echo "Cost $SECONDS sec."

echo "----------------------cpplint---------------------"

echo "Start cpplint..."
SECONDS=0
# grep -v to filt the file in .cpplintignore
find $repo_path -type f -name "*.h" -or -name "*.cc" -or -name "*.cpp"\
  | grep -v $(printf -- "-f %s " $(find $repo_path -name \*.cpplintignore)) \
  | xargs $repo_path/utilities/cpplint/cpplint.py --counting=detailed --quiet
echo "End of cpplint"
echo "Cost $SECONDS sec."

echo "--------------------------------------------------"