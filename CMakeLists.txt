cmake_minimum_required(VERSION 3.19)
project(Benchmarks)

set(CMAKE_CXX_STANDARD 17)
find_package(benchmark REQUIRED)


# register benchmarks
file(GLOB benchmark_files "${CMAKE_SOURCE_DIR}/benches/*.cpp")
foreach(file ${benchmark_files})
    cmake_path(GET file STEM bench_name)
    add_executable(${bench_name} ${file})
    target_link_libraries(${bench_name} PRIVATE benchmark::benchmark)
endforeach()
