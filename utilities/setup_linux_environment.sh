#!/bin/bash

# Bazel

function install_bazel_package(){
  sudo apt install apt-transport-https curl gnupg
  curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor > bazel.gpg
  sudo mv bazel.gpg /etc/apt/trusted.gpg.d/
  echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
  sudo apt update && sudo apt install bazel
}

function update_bazel(){
  sudo apt update && sudo apt-get --only-upgrade install bazel
}

# Install latest bazel
bazel --version &> /dev/null  # return 0 if bazel exist
if [ $? -ne 0 ]; then
  echo 'Bazel not installed. Start install bazel...'
  install_bazel_package
else
  echo 'Try update bazel...'
  update_bazel
fi

bazel --version
echo 'Done!'