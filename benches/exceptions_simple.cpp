#include <benchmark/benchmark.h>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <random>
#include <iostream>

volatile auto load_size = 128ull;

using int_pair = std::pair<int, int>;
using namespace std::literals;


auto dummy_payload(std::size_t n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);

    std::vector<int_pair> acc{};
    acc.reserve(n);
    for (std::size_t i = 0; i < n; ++i)
        acc.emplace_back(distrib(gen), distrib(gen));
    if (std::any_of(acc.begin(), acc.end(), [](auto p) { return p.first <= 0 or p.second <= 0; }))
        std::terminate();
    return acc;
}

// notify of failure via return argument
int task(const std::vector<int_pair> &pairs, std::string &pb) noexcept {
    int s{};
    for (auto[x, y]: pairs) {
        if (x <= 0 and y <= 0)  {
            pb = "negative-vector encountered :"s + std::to_string(x) + ", "s + std::to_string(y);
            return s; // whatever
        }
        s += x * x + y * y;
    }
    return s;
}

void ManualHandling(benchmark::State &state) {
    auto pairs = dummy_payload(load_size);
    for ([[maybe_unused]] auto _: state) {
        std::string pb;
        int s = task(pairs, pb); // C-style error handling
        benchmark::DoNotOptimize(s);
        if (!pb.empty()) {
            std::cerr << pb << '\n';
            break; // break to imitate TryOuter, don't to imitate TryInner
        }
    }
}

BENCHMARK(ManualHandling);


// notify of failure via return argument
int task_exc(const std::vector<int_pair> &pairs) {
    int s{};
    for (auto[x, y]: pairs) {
        if (x <= 0 or y <= 0)
            throw std::runtime_error{"negative-vector encountered :"s + std::to_string(x) + ", "s + std::to_string(y)};
        s += x * x + y * y;
    }
    return s;
}


void InnerTryBlock(benchmark::State &state) {
    auto pairs = dummy_payload(load_size);
    for ([[maybe_unused]] auto _: state) {
        try {
            task_exc(pairs);
        } catch (std::exception &e) {
            std::cerr << e.what() << '\n';
        }
    }

}

BENCHMARK(InnerTryBlock);


void OuterTryBlock(benchmark::State &state) {
    auto pairs = dummy_payload(load_size);
    try {
        for ([[maybe_unused]] auto _: state)
            task_exc(pairs);
    } catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    }

}

BENCHMARK(OuterTryBlock);



BENCHMARK_MAIN();
