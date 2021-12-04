#ifndef TREASURE_H
#define TREASURE_H

#include <concepts>

template<typename T>
concept TreasureValueType = std::integral<T>;

template<typename ValueType, bool IsTrapped>
requires TreasureValueType<ValueType>
class Treasure {
    ValueType value;

public:
    static constexpr const bool isTrapped = IsTrapped;

    constexpr explicit Treasure(ValueType val) : value(val) {}

    constexpr ValueType evaluate() const {return value;}

    constexpr ValueType getLoot() {
        ValueType buff = value;
        value = 0;
        return buff;
    }
};

template<typename T>
using SafeTreasure = Treasure<T, false>;

template<typename T>
using TrappedTreasure = Treasure<T, true>;

#endif // TREASURE_H