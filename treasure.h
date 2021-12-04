#ifndef TREASURE_H
#define TREASURE_H

#include <concepts>

template<typename T>
concept TreasureValueType = std::integral<T>;

template<typename T, bool IsTrapped>
requires TreasureValueType<T>
class Treasure {
    T value;

public:
    static constexpr const bool isTrapped = IsTrapped;

    constexpr explicit Treasure(T val) : value(val) {}

    constexpr T evaluate() const { return value; }

    constexpr T getLoot() {
        T buff = value;
        value = 0;
        return buff;
    }
};

template<typename T>
using SafeTreasure = Treasure<T, false>;

template<typename T>
using TrappedTreasure = Treasure<T, true>;

#endif // TREASURE_H