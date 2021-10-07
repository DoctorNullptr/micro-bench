#include <string>
#include <string_view>
#include <benchmark/benchmark.h>

constexpr std::string_view text
        {"ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo"};


static void StoreString(benchmark::State &state) {
    const std::string s{text.data(), static_cast<std::size_t>(state.range(0))};
    for ([[maybe_unused]] auto _: state) {
        std::string copy{s};
        benchmark::DoNotOptimize(copy);
    }
}

constexpr std::size_t max_len = 40;
static_assert(text.size() >= max_len);

BENCHMARK(StoreString)->DenseRange(0, max_len);

BENCHMARK_MAIN();
