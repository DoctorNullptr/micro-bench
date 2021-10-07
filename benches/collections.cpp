#include <vector>
#include <deque>
#include <list>
#include <array>
#include <memory_resource>
#include <benchmark/benchmark.h>

static void Vector(benchmark::State &state) {
    std::size_t len = state.range();
    for ([[maybe_unused]] auto _: state) {
        std::vector<int> collection(len, 33);
        benchmark::DoNotOptimize(collection);
    }
}

static void List(benchmark::State &state) {
    std::size_t len = state.range();
    for ([[maybe_unused]] auto _: state) {
        std::list<int> collection(len, 33);
        benchmark::DoNotOptimize(collection);
    }
}

static void Deque(benchmark::State &state) {
    std::size_t len = state.range();
    for ([[maybe_unused]] auto _: state) {
        std::deque<int> collection(len, 33);
        benchmark::DoNotOptimize(collection);
    }
}

constexpr std::size_t top_size = 1 << 12;


BENCHMARK(Vector)->Range(1, top_size);
BENCHMARK(List)->Range(1, top_size);
BENCHMARK(Deque)->Range(1, top_size);


static void Array4(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        std::array<int, 4> array{1, 2, 3, 4};
        benchmark::DoNotOptimize(array);
    }
}

static void InitList4(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        std::initializer_list<int> list{1, 2, 3, 4};
        benchmark::DoNotOptimize(list);
    }
}

BENCHMARK(Array4)->Name("Array/4");
BENCHMARK(InitList4)->Name("InitList/4");

static void PmrVector(benchmark::State &state) {
    std::pmr::unsynchronized_pool_resource res{};
    std::pmr::polymorphic_allocator<int> allocator{&res};

    std::size_t len = state.range();
    for ([[maybe_unused]] auto _: state) {
        std::pmr::vector<int> collection{allocator};

        collection.assign(len, 33);

        benchmark::DoNotOptimize(collection);
    }
}


static void PmrList(benchmark::State &state) {
    std::pmr::monotonic_buffer_resource res{};
    std::pmr::polymorphic_allocator<int> allocator{&res};

    std::size_t len = state.range();
    for ([[maybe_unused]] auto _: state) {
        std::pmr::list<int> collection{allocator};

        collection.assign(len, 33);
        benchmark::DoNotOptimize(collection);
    }
}

BENCHMARK(PmrVector)->Range(1, top_size);
BENCHMARK(PmrList)->Range(1, top_size);


BENCHMARK_MAIN();
