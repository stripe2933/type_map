#include <cassert>
#include <version>
#if __cpp_lib_modules < 202207L
#include <stdexcept>
#include <utility>
#include <variant>
#endif

#if __cpp_lib_modules >= 202207L
import std;
#endif
import type_map;

int main() {
    for (int i = 0; i < 4; ++i) {
        visit([i](auto N) {
            assert(i == N);

            // Is compile-time constant?
            [[maybe_unused]] int nums[N];
        }, iota_map<4>::get_variant(i));
    }

    try {
        std::ignore = iota_map<4>::get_variant(4);
        return 1;
    }
    catch (const std::out_of_range&) { }
    catch (...) {
        return 1;
    }

    for (int i = 1; i < 5; ++i) {
        visit([i](auto N) {
            assert(i == N);

            // Is compile-time constant?
            [[maybe_unused]] int nums[N];
        }, iota_map<4, 1>::get_variant(i));
    }

    try {
        std::ignore = iota_map<4, 1>::get_variant(0);
        return 1;
    }
    catch (const std::out_of_range&) {
        return 0;
    }
}