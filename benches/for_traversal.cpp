#include <benchmark/benchmark.h>
#include <vector>

constexpr std::size_t len{4096};

void IndexedFor(benchmark::State &state) {
    std::vector<int> vec(len, 42);

    int sz = vec.size(), *p = vec.data();
    for ([[maybe_unused]] auto _: state) {
        for (int i = 0; i < sz; ++i)
            benchmark::DoNotOptimize(p[i]);
    }
}

BENCHMARK(IndexedFor);

void ForIterator(benchmark::State &state) {
    std::vector<int> vec(len, 42);

    for ([[maybe_unused]] auto _: state) {
        for (auto it = vec.begin(); it != vec.end(); ++it)
            benchmark::DoNotOptimize(*it);
    }
}

BENCHMARK(ForIterator);

void ForEach(benchmark::State &state) {
    std::vector<int> vec(len, 42);

    for ([[maybe_unused]] auto _: state) {
        for (auto x: vec)
            benchmark::DoNotOptimize(x);
    }
}

BENCHMARK(ForEach);


BENCHMARK_MAIN();
