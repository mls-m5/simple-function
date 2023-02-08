#pragma once

#include <array>
#include <cstddef>

namespace simple {

// A function that is easier to debug than std::function
template <typename _Signature>
class Function;

// A more debuggable function
template <typename Res, typename... Args>
struct Function<Res(Args...)> {
    //! valueSize:   amount of data that is available to store in
    //! the object. Heavier objects decreases likelyhood of memory being
    //! allocated on the heap
    constexpr static size_t valueSize = 36;
    using Signature = Res (*)(Args...);

    std::array<char, valueSize> valueData = {};
    char *data = valueData.data();
    Res (*call)(Function *data, Args...) = nullptr;
    void (*destructor)(Function *) = nullptr;
    void (*clone)(const Function *, Function *) = nullptr;
    size_t size = 0;

    // Copy from another simple function
    Function(const Function &f) {
        f.clone(&f, this);
    }

    Function &operator=(const Function &f) {
        f.clone(&f, *this);
    }

    template <typename F>
    Function(const F &f) {
        *this = f;
    }

    template <typename F>
    Function &operator=(const F &f) {
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
        size = sizeof(F);

        // How to copy this type
        clone = [](const Function *from, Function *to) {
            auto *f = reinterpret_cast<F *>(from->data);
            *to = *f; // Use operator=
        };

        // How to call this type
        call = +[](Function *self, Args... args) {
            auto *f = reinterpret_cast<F *>(self->data);
            (*f)(std::forward<Args...>(args...));
        };

        return *this;
    }

    ~Function() {
        destructor(this);
    }

    Res operator()(Args... args) {
        call(this, std::move(args)...);
    }
};

} // namespace simple
