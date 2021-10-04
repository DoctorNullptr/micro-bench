#include <map>
#include <array>
#include <unordered_map>
#include <string>
#include <string_view>
#include <benchmark/benchmark.h>

static void Direct(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        std::map<int, std::string> mp{
                {1, "foo"},
                {2, "bar"},
                {3, "baz"},
                {4, "trt"},
        };
        benchmark::DoNotOptimize(mp);
    }
}

BENCHMARK(Direct);

static void DirectHash(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        std::unordered_map<int, std::string> mp{
                {1, "foo"},
                {2, "bar"},
                {3, "baz"},
                {4, "trt"},
        };
        benchmark::DoNotOptimize(mp);
    }
}

BENCHMARK(DirectHash);


static void Vectored(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        std::vector<std::pair<int, std::string_view>> mp{
                {1, "foo"},
                {2, "bar"},
                {3, "baz"},
                {4, "trt"},
        };
        benchmark::DoNotOptimize(mp);
    }
}

BENCHMARK(Vectored);


static void TooMuch(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        std::array<std::pair<int, std::string_view>, 4> mp{{
                                                                   {1, "foo"},
                                                                   {2, "bar"},
                                                                   {3, "baz"},
                                                                   {4, "trt"},
                                                           }};
        benchmark::DoNotOptimize(mp);
    }
}

BENCHMARK(TooMuch);


static void InDirect(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        std::map<int, std::string *> mp{
                {1, new std::string{"foo"}},
                {2, new std::string{"bar"}},
                {3, new std::string{"baz"}},
                {4, new std::string{"trt"}},
        };
        benchmark::DoNotOptimize(mp);
        for (auto[_i, p]: mp)
            delete p;
    }
}

BENCHMARK(InDirect);


BENCHMARK_MAIN();
