#include <map>
#include <array>
#include <unordered_map>
#include <string>
#include <benchmark/benchmark.h>

template<class Mapping>
void populate_map(Mapping &map, std::size_t n) {
    for (auto i{0ull}; i != n; ++i)
        map[i] = i * i;
}

static void Map(benchmark::State &state) {
    std::map<int, std::string> mp{};
    populate_map(mp, state.range(0));

    for ([[maybe_unused]] auto _: state) {
        auto ref = mp.at(0);
        benchmark::DoNotOptimize(ref);
    }
}

BENCHMARK(Map)->Range(8, 1 << 16);



static void HashMap(benchmark::State &state) {
    std::unordered_map<int, std::string> mp{};
    populate_map(mp, state.range(0));

    for ([[maybe_unused]] auto _: state) {
        auto ref = mp.at(0);
        benchmark::DoNotOptimize(ref);
    }
}

BENCHMARK(HashMap)->Range(8, 1 << 16);

static void MapNC(benchmark::State &state) {
    std::map<int, std::string> mp{};
    populate_map(mp, state.range(0));
    int where{1};

    for ([[maybe_unused]] auto _: state) {
        where *= 3;
        while (where > mp.size()) where -= mp.size();
        auto ref = mp.at(where);
        benchmark::DoNotOptimize(ref);
    }
}

BENCHMARK(MapNC)->Range(8, 1 << 16);



static void HashMapNC(benchmark::State &state) {
    std::unordered_map<int, std::string> mp{};
    populate_map(mp, state.range(0));
    int where{1};

    for ([[maybe_unused]] auto _: state) {
        where *= 3;
        while (where > mp.size()) where -= mp.size();
        auto ref = mp.at(where);
        benchmark::DoNotOptimize(ref);
    }
}

BENCHMARK(HashMapNC)->Range(8, 1 << 16);


BENCHMARK_MAIN();
