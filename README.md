# wheel_stl

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


## Config Local Develop Environment
``` bash
./utilities/setup_local_environment.sh
```

## CICD Build & Run Environment
* github runner has install latest bazel by default.