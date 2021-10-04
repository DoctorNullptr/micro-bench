#include <benchmark/benchmark.h>
#include <memory>

static void Shared(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        auto p = std::make_shared<int>(0);
        benchmark::DoNotOptimize(*p);
    }
}

BENCHMARK(Shared);


static void Unique(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        std::unique_ptr<int> p{new int{}};
        benchmark::DoNotOptimize(*p);
    }
}

BENCHMARK(Unique);


static void Raw(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        auto p = new int{};
        benchmark::DoNotOptimize(*p);
        delete p;
    }
}

BENCHMARK(Raw);

static void RawUninit(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        auto p = new int; // no initializer
        benchmark::DoNotOptimize(*p);
        delete p;
    }
}

BENCHMARK(RawUninit);

static void Stack(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        int i{};
        benchmark::DoNotOptimize(i);
    }
}

BENCHMARK(Stack);

BENCHMARK_MAIN();
