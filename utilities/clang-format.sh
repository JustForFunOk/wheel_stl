#!/usr/bin/env bash

# get the root path of git repository
repo_path=$(git rev-parse --show-toplevel)
echo "Current git root path: $repo_path"

echo "Start clang-forat for every file in current folder..."
# SECONDS is bash builtin variable that tracks the number of seconds
# that have passed since the shell was started
SECONDS=0
find $repo_path \
    \( -iname '*.c' \
    -o -iname '*.cc' \
    -o -iname '*.cpp' \
    -o -iname '*.h' \
    -o -iname '*.hh' \
    -o -iname '*.hpp' \) \
    -exec clang-format -style=file -i '{}' \;  # Use -style=file to
                                               # load style configuration from .clang-format file
echo "End of clang-format..."
echo "Cost $SECONDS sec."