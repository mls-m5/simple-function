#pragma once

#include <array>
#include <cstring>

namespace simple {

// A function that is easier to debug than std::function
//! @param valueSize   amount of data that is available to store in
//! the object. Heavier objects decreases likelyhood of memory being
//! allocated on the heap
template <typename _Signature, int valueSize = 36>
class Function;

// A more debuggable function
template <typename Res, typename... Args, int valueSize>
struct Function<Res(Args...), valueSize> {
    using Signature = Res (*)(Args...);

    std::array<char, valueSize> valueData = {};
    char *data = valueData.data();
    Res (*call)(Function *data, Args...) = nullptr;
    void (*destructor)(Function *) = nullptr;

    template <typename F>
    Function(const F &f) {
        if (sizeof(F) > valueData.size()) {
            data = reinterpret_cast<char *>(::new auto(f));
            destructor = +[](Function *self) {
                auto *f = reinterpret_cast<F *>(self->data);
                delete f;
            };
        }
        else {
            ::new (valueData.data()) auto(f);
            destructor = +[](Function *self) {
                auto *f = reinterpret_cast<F *>(self->valueData.data());
                f->~F();
            };
        }

        call = +[](Function *self, Args... args) {
            auto *f = reinterpret_cast<F *>(self->data);
            (*f)(std::forward<Args...>(args...));
        };
    }

    ~Function() {
        destructor(this);
    }

    Res operator()(Args... args) {
        call(this, std::forward<Args...>(args...));
    }
};

} // namespace simple
