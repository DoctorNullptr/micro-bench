# Benchmarks

This project showcases the performance differences of a few C++ constructs vs their alternatives.

## Prerequisites

`google-benchmark` is required to build this project.

### Google benchmark as a package

To install it, run:

```shell
git clone https://github.com/google/benchmark.git
cmake -S benchmark -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON -DCMAKE_BUILD_TYPE=Release -GNinja -B build-bm-rel 
sudo cmake --install build-bm-rel
```

### Google benchmark as a subdirectory

Alternatively, you may clone `google-benchmark` at the top of the source tree and use `add_subdirectory(benchmark)`
instead of `find_package(benchmark)`.

## Running a benchmark

### Configuration

Benchmarks matching `benches/*.cpp` are detected at configure step.

```shell
cmake -S . -B build-rel -DCMAKE_BUILD_TYPE=Release -GNinja
```

### Building a target

```shell
cmake --build build-rel  # build all targets
cmake --build build-rel --target string_storage  # build only string_storage
```

### Launching a benchmark

```shell
./build-rel/string_storage  # for example
```
