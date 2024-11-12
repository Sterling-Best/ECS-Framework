#pragma once
#include <ankerl/unordered_dense.h>
#include <type_traits>
#include <string>
#include <tuple>

template <typename EntityIdType, typename Enable = void>
struct CustomHash;

template <typename EntityIdType>
struct CustomHash<EntityIdType, std::enable_if_t<
    std::is_arithmetic_v<EntityIdType> ||
    std::is_same_v<EntityIdType, std::string> ||
    std::is_same_v<EntityIdType, std::wstring> ||
    std::is_enum_v<EntityIdType>>> : public ankerl::unordered_dense::hash<EntityIdType> {
    using is_avalanching = void;
};

template <typename EntityIdType>
struct CustomHash<EntityIdType, std::enable_if_t<std::is_pointer_v<EntityIdType>>> {
    using is_avalanching = void;
    size_t operator()(const EntityIdType& id) const noexcept {
        return ankerl::unordered_dense::detail::wyhash::hash(reinterpret_cast<const void*>(id), sizeof(id));
    }
};

template <>
struct CustomHash<std::pair<int, int>> {
    using is_avalanching = void;
    size_t operator()(const std::pair<int, int>& id) const noexcept {
        size_t h1 = ankerl::unordered_dense::hash<int>{}(id.first);
        size_t h2 = ankerl::unordered_dense::hash<int>{}(id.second);
        return h1 ^ (h2 << 1);
    }
};

template <>
struct CustomHash<std::tuple<int, float>> {
    using is_avalanching = void;
    size_t operator()(const std::tuple<int, float>& id) const noexcept {
        size_t h1 = ankerl::unordered_dense::hash<int>{}(std::get<0>(id));
        size_t h2 = ankerl::unordered_dense::hash<float>{}(std::get<1>(id));
        return h1 ^ (h2 << 1);
    }
};
