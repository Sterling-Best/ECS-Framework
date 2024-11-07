#include <cstdint>
#include <type_traits>
#include <string>
#include <tuple>
#include <utility>

// Expanded helper meta-function to check if EntityIdType is allowed
template<typename T>
struct IsValidEntityIdType {
    static constexpr bool value = std::is_arithmetic<T>::value                         // Arithmetic types (int, float, etc.)
        || std::is_same<T, std::string>::value               // std::string
        || std::is_same<T, std::wstring>::value              // std::wstring
        || std::is_same<T, char>::value                      // char
        || std::is_same<T, wchar_t>::value                   // wchar_t
        || std::is_same<T, std::u16string>::value            // std::u16string
        || std::is_same<T, std::u32string>::value            // std::u32string
        || std::is_enum<T>::value                            // Enum types
        || std::is_pointer<T>::value                         // Pointer types
        || std::is_same<T, std::pair<int, int>>::value       // Example of allowing a std::pair (or expand to any other custom type)
        || std::is_same<T, std::tuple<int, float>>::value;   // Example of allowing std::tuple (expand as needed)
};