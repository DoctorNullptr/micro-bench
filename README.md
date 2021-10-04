# Benchmarks

This project showcases the performance differences of a few C++ constructs vs their alternatives.

## Prerequisites

`google-benchmark` is required to build this project; it is cloned and added as a subdirectory.

```shell
# at the toplevel of the source tree
git clone https://github.com/google/benchmark.git
cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON -DCMAKE_BUILD_TYPE=Release -S . -B build-release # configuration
```

## Running a benchmark

### Configuration

Benchmarks matching `benches/*.cpp` are detected at configure step, reconfigure to detect more.

### Building a target

```shell
cmake --build build-release  # build all targets
cmake --build build-release --target string_storage  # build only string_storage
```

### Launching a benchmark

```shell
./build-rel/string_storage  # for example
```
