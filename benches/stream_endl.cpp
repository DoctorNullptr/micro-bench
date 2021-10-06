#include <benchmark/benchmark.h>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

struct TmpFile {
public:
    auto stream() const { return std::fstream{path, std::ios_base::out}; }

    ~TmpFile() { fs::remove(path); }

    const fs::path path;
};

void CoutEndl(benchmark::State &state) {
    TmpFile file{fs::path{"junk.txt"}};
    auto stream{file.stream()};
    for ([[maybe_unused]] auto _: state)
        stream << "Hello, world !" << std::endl;

}

BENCHMARK(CoutEndl);


void CoutRet(benchmark::State &state) {
    TmpFile file{fs::path{"junk.txt"}};
    auto stream{file.stream()};
    for ([[maybe_unused]] auto _: state)
        stream << "Hello, world !" << '\n';
}

BENCHMARK(CoutRet);



BENCHMARK_MAIN();
