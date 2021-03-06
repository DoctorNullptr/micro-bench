#include <benchmark/benchmark.h>
#include <string>
#include <memory>
#include <optional>
#include <utility>

class A {
public:
    ~A() { delete report; } // need to clean up

    // not generated by default because of custom destructor, we have to write it
    A(int data, std::string info, std::string *report = nullptr) :
            data(data),
            info(std::move(info)),
            report(report) {}

private:
    int data{-1};
    std::string info;
    std::string *report;
};

void problematic() {
    A a{3, "foo", new std::string{"bar"}};
    A b{a}; // innocent copy

    // now both a and b delete A::report :/

    // to prevent copy, more boilerplate ?
}

void UseA(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        A a{3, "foo", new std::string{"bar"}};
        benchmark::DoNotOptimize(a);
    }
}

BENCHMARK(UseA);


struct B {
    int data{-1};
    std::string info;
    std::unique_ptr<std::string> report; // unique_ptr does not allow copy; thus B cannot be copied either
};

void UseB(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        B b{3, "foo", std::make_unique<std::string>("bar")};
        benchmark::DoNotOptimize(b);
    }
}

BENCHMARK(UseB);

static_assert(sizeof(A) == sizeof(B)); // no size overhead

// to summarize : RAII works on members of a class; prefer using std::unique_ptr/std::shared_ptr as a member to
// writing custom constructor/destructor, deleting copy constructor/assigment... in order to express ownership

struct C {
    int data{-1};
    std::string info;
    std::optional<std::string> report; // a member that can be present or absent really could be optional
};

void UseC(benchmark::State &state) {
    for ([[maybe_unused]] auto _: state) {
        C c{3, "foo", std::make_optional<std::string>("bar")};
        benchmark::DoNotOptimize(c);
    }
}

BENCHMARK(UseC);

BENCHMARK_MAIN();
