#include <benchmark/benchmark.h>
#include <memory>

void increment_copy(std::shared_ptr<int> ptr) {
    ++*ptr;
}

static void Copy(benchmark::State &state) {
    auto p = std::make_shared<int>(0);
    for ([[maybe_unused]] auto _: state) {
        increment_copy(p);
        benchmark::DoNotOptimize(*p);
    }
}

BENCHMARK(Copy);

void increment_ref(std::shared_ptr<int> &ptr) {
    ++*ptr;
}

static void Ref(benchmark::State &state) {
    auto p = std::make_shared<int>(0);
    for ([[maybe_unused]] auto _: state) {
        increment_ref(p);
        benchmark::DoNotOptimize(*p);
    }
}

BENCHMARK(Ref);


BENCHMARK_MAIN();
