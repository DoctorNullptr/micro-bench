#include <string>
#include <string_view>
#include <benchmark/benchmark.h>


void Stack(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        std::string foo{"Foo"};
        benchmark::DoNotOptimize(foo);
    }
}

BENCHMARK(Stack);

void Placement(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        alignas(std::string) std::byte mem[sizeof(std::string)];
        const auto *p = new(mem) std::string{"Foo"};

        benchmark::DoNotOptimize(*p);

        std::destroy_at(p);
    }

}
BENCHMARK(Placement);


BENCHMARK_MAIN();
