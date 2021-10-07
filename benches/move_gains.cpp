#include <benchmark/benchmark.h>
#include <string>


struct A {
    explicit A(const std::string &name) : name(name) {}

private:
    std::string name;
};


void Init1(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        A a{"An awfully long name"};
        benchmark::DoNotOptimize(a);
    }
}

BENCHMARK(Init1);


struct B {
    explicit B(std::string name) : name(std::move(name)) {}

private:
    std::string name;
};


void Init2(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        B b{"An awfully long name"};
        benchmark::DoNotOptimize(b);
    }
}

BENCHMARK(Init2);

void Init3(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        std::string name{"An awfully long name"};
        B a{name};
        benchmark::DoNotOptimize(a);
    }
}

BENCHMARK(Init3);

void Init4(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        std::string name{"An awfully long name"};
        B a{std::move(name)};
        benchmark::DoNotOptimize(a);
    }
}

BENCHMARK(Init4);




BENCHMARK_MAIN();
