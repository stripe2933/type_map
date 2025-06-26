#include <cassert>
#include <version>
#if __cpp_lib_modules < 202207L
#include <string_view>
#include <type_traits>
#include <variant>
#endif

#if __cpp_lib_modules >= 202207L
import std;
#endif
import type_map;

using namespace std::string_view_literals;

int main() {
    constexpr auto get_type_size_by_type_name = [](std::string_view name) {
        constexpr type_map map {
            make_type_map_entry<char>("char"sv),
            make_type_map_entry<int>("int"sv),
            make_type_map_entry<double>("double"sv),
        };

        return visit([]<typename T>(std::type_identity<T>) noexcept {
            return sizeof(T);
        }, map.get_variant(name));
    };

#if __cpp_lib_variant >= 202106L
    static_assert(get_type_size_by_type_name("char") == sizeof(char));
    static_assert(get_type_size_by_type_name("int") == sizeof(int));
    static_assert(get_type_size_by_type_name("double") == sizeof(double));
#else
    assert(get_type_size_by_type_name("char") == sizeof(char));
    assert(get_type_size_by_type_name("int") == sizeof(int));
    assert(get_type_size_by_type_name("double") == sizeof(double));
#endif

    try {
        get_type_size_by_type_name("string");
    }
    catch (const std::out_of_range&) {
        return 0;
    }
    assert(false && "Expected std::out_of_range exception");
}