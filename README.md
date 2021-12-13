# wheel_stl

![Build Status](https://github.com/JustForFunOk/wheel_stl/actions/workflows/bazel_build.yml/badge.svg)

Reinventing the wheel of STL (Standard Template Library)

## Why this project?

This project is really 'Just For Study'. Including the following aspects:

* **the principle of STL**
* project workflow
  * Style (clang-format, cpplint)
  * Build ([bazel](https://bazel.build/))
  * Test ([gtest](https://github.com/google/googletest))
  * CICD ([github action](https://docs.github.com/en/actions))
  * ...


## Local Development

### Environment Setup
``` bash
./utilities/setup_local_environment.sh
```
## Develop workflow
``` bash
./utilities/build_all.sh
```

## CICD Build & Run Environment

[Do nothing]

* **Bazel**. github runner has install latest bazel by default.
* **third-party**. other third-party dependency all installed by Bazel.