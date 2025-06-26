# type_map

Convert runtime values to compile-time types.

```c++
import std;
import type_map;

using namespace std::string_view_literals;

[[nodiscard]] constexpr std::size_t get_type_size_by_name(std::string_view name) {
    constexpr type_map map {
        make_type_map_entry<char>("char"sv),
        make_type_map_entry<int>("int"sv),
        make_type_map_entry<double>("double"sv),
    };
    
    return visit([]<typename T>(std::type_identity<T>) {
        return sizeof(T);
    }, map.get_variant(name));
}


int main() {
    static_assert(get_type_size_by_name("char") == 1);
    static_assert(get_type_size_by_name("int") == 4);
    static_assert(get_type_size_by_name("double") == 8);
}
```

## Usage

### Manual Installation

```shell
git clone --depth 1 https://github.com/stripe2933/type_map.git
cd type_map
mkdir build
cmake -S . -B build -G Ninja
cmake --build build --target install
```

Then in your CMake project, you can use:

`CMakeLists.txt`
```cmake
find_package(type_map CONFIG REQUIRED)
target_link_libraries(<target> PRIVATE type_map::type_map)
```

### vcpkg

```shell
vcpkg add port type-map
```

Then in your CMake project, you can use:

`CMakeLists.txt`
```cmake
find_package(type_map CONFIG REQUIRED)
target_link_libraries(<target> PRIVATE type_map::type_map)
```

### CPM

`CMakeLists.txt`
```cmake
CPMAddPackage("gh:stripe2933/type_map@0.1.0")
target_link_libraries(<target> PRIVATE type_map::type_map)
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.txt) file for details.