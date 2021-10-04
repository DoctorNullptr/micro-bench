#include <vector>
#include <deque>
#include <list>
#include <array>
#include <memory_resource>
#include <benchmark/benchmark.h>

static void Vector(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        std::vector<int> vec{1, 2, 3};
        benchmark::DoNotOptimize(vec);
    }
}

BENCHMARK(Vector);

static void PmrVector(benchmark::State &state) {
    std::pmr::unsynchronized_pool_resource res{};
    std::pmr::polymorphic_allocator<int> allocator{&res};
    for ([[maybe_unused]] auto _: state) {
        std::pmr::vector<int> vec{allocator};
        vec.assign({1, 2, 3});
        benchmark::DoNotOptimize(vec);
    }
}

BENCHMARK(PmrVector);

static void PmrList(benchmark::State &state) {
    std::pmr::unsynchronized_pool_resource res{};
    std::pmr::polymorphic_allocator<int> allocator{&res};
    for ([[maybe_unused]] auto _: state) {
        std::pmr::list<int> vec{allocator};
        vec.assign({1, 2, 3});
        benchmark::DoNotOptimize(vec);
    }
}

BENCHMARK(PmrList);

static void List(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        std::list<int> vec{1, 2, 3};
        benchmark::DoNotOptimize(vec);
    }
}

BENCHMARK(List);

static void Deque(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        std::deque<int> vec{1, 2, 3};
        benchmark::DoNotOptimize(vec);
    }
}

BENCHMARK(Deque);

static void Array(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        std::array<int, 3> vec{1, 2, 3};
        benchmark::DoNotOptimize(vec);
    }
}

BENCHMARK(Array);

static void InitList(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        std::initializer_list<int> vec{1, 2, 3};
        benchmark::DoNotOptimize(vec);
    }
}

BENCHMARK(InitList);


BENCHMARK_MAIN();
