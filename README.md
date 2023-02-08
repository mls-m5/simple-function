# simple-function

What if you felt like you would like to debug a function call
one day, only to realize that std::function is so convoluted
with nested calls that it's almost impossible to step into
a function when debugging.

What if you could exchange std::function with another type
when debugging so that you could easier debug it?

It was with that thought in mind i created this library. It copies
and stores callable types to its own internal storage or on the
heap and calls just like std::function.

## Simple example
``` c++
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
```



## Features / implementation order:
(not many)
 - [x] Copy lambdas and then call
 - [x] Copy and move the simple::Function itself
 - [x] Copy std::function into simple::Function (did not need any extra implementation)


