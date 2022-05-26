# wheel_stl

[![CICD Workflows](https://github.com/JustForFunOk/wheel_stl/actions/workflows/remote_pipeline.yml/badge.svg)](https://github.com/JustForFunOk/wheel_stl/actions/workflows/remote_pipeline.yml)

Reinventing the wheel of STL (Standard Template Library)

## Why this project?

This project is really 'Just For Study'. Including the following aspects:

* **the principle of STL**
* project workflow
  * CICD ([github action](https://docs.github.com/en/actions))
  * Style (clang-format, cpplint)
  * Static code analysis ([cppcheck](https://cppcheck.sourceforge.io))
  * Build ([bazel](https://bazel.build/))
  * Test ([gtest](https://github.com/google/googletest))
  * Code coverage (gcov, lcov)
  * ...


## Local Development

### Environment Setup
``` bash
./utilities/setup_<linux/macos>_environment.sh
```
### Develop workflow
``` bash
./utilities/build_all.sh
```

### Commit with emoji
Github and Gitlab all support display emoji in commit message. Check
[gitmoji](https://gitmoji.dev) for emoji code.

## CICD Build & Run Environment

[Do nothing]

* **Bazel**. github runner has install latest bazel by default.
* **third-party**. other third-party dependency all installed by Bazel.