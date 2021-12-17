#!/bin/bash

# Bazel

function install_bazel_package(){
  brew install bazel
}

# Install latest bazel
bazel --version &> /dev/null  # return 0 if bazel exist
if [ $? -ne 0 ]; then
  echo 'Bazel has not been installed. Start install bazel...'
  install_bazel_package
else
  echo 'Bazel has been installed. Skip...'
fi

bazel --version
echo 'Done!'