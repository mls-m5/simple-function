#include "simple/function.hpp"
#include <functional>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    std::string there = "there";

    simple::Function<void(std::string)> f([there](std::string arg) {
        std::cout << arg << " " << there << "\n"; ///
    });
    f("hello");

    auto f2 = f;
    f2("yo");

    // Wraps the simple function inside a std::function
    auto f3 = std::function{f2};
    f3("third hello");

    // Then wrap the std::function inside a simple::Function
    auto f4 = simple::Function<void(std::string)>{f3};
    f4("fourth hello");

    std::cout << std::endl;

    return 0;
}
