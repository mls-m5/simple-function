#include "simple/function.hpp"
#include <functional>
#include <iostream>
#include <string_view>

int main(int argc, char *argv[]) {
    std::string there = "there";

    simple::Function<void(std::string)> f([there](std::string arg) {
        std::cout << arg << " " << there << "\n"; ///
    });

    f("hello");

    std::cout << std::endl;

    return 0;
}
