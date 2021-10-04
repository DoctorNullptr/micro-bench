#include <string>
#include <string_view>
#include <benchmark/benchmark.h>

constexpr std::string_view text
        {"ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo"};

static_assert(text.size() >= 60);


static void StoreString(benchmark::State &state) {
    const std::string s{text.data(), static_cast<std::size_t>(state.range(0))};
    for ([[maybe_unused]] auto _: state) {
        std::string copy{s};
        benchmark::DoNotOptimize(copy);
    }
}

BENCHMARK(StoreString)->DenseRange(12, 18);

BENCHMARK_MAIN();
