#ifndef MEMBER_H
#define MEMBER_H

#include "treasure.h"
#include <algorithm>
#include <cstddef>
#include <cstdint>

template<typename ValueType, bool IsArmed>
requires TreasureValueType<ValueType>
class Adventurer {}; // Klasa jest implementowana poprzez specjalizacje.

template<typename ValueType>
requires TreasureValueType<ValueType>
class Adventurer<ValueType, false> { // Nieuzbrojony poszukiwacz przygód.
public:
    using strength_t = uint32_t;

    constexpr Adventurer() : value(0) {}

    static constexpr const bool isArmed = false;

    template<bool IsTrapped>
    constexpr void loot(Treasure<ValueType, IsTrapped> &&treasure) {
        if(!treasure.isTrapped) {
            value += treasure.getLoot();
        }
    }

    constexpr ValueType pay() {
        ValueType buff = value;
        value = 0;
        return buff;
    }

private:
    ValueType value;
};

template<typename ValueType>
requires TreasureValueType<ValueType>
class Adventurer<ValueType, true> { // Uzbrojony poszukiwacz przygód.
public:
    using strength_t = uint32_t;

    constexpr explicit Adventurer(strength_t s_val) : value(0), strength(s_val) {}

    constexpr strength_t getStrength() const {return strength;}

    static constexpr const bool isArmed = true;

    template<bool IsTrapped>
    constexpr void loot(Treasure<ValueType, IsTrapped> &&treasure) {
        if (IsTrapped) {
            if (strength != 0) {
                strength /= 2;
                value += treasure.getLoot();
            }
        } else {
            value += treasure.getLoot();
        }
    }

    constexpr ValueType pay() {
        ValueType buff = value;
        value = 0;
        return buff;
    }

private:
    ValueType value;
    strength_t strength;
};

template<typename ValueType>
using Explorer = Adventurer<ValueType, false>;

template<typename ValueType, std::size_t CompletedExpeditions>
requires TreasureValueType<ValueType> && (CompletedExpeditions < 25)
class Veteran {
public:
    using strength_t = uint32_t;

    constexpr Veteran() : value(0), completedExpeditions(CompletedExpeditions),
    strength(calcStrength()) {}

    static constexpr const bool isArmed = true;

    template<bool isTrapped>
    constexpr void loot(Treasure<ValueType, isTrapped> &&treasure) {
        if (isTrapped) {
            if (strength != 0) {
                value += treasure.getLoot();
            }
        } else {
            value += treasure.getLoot();
        }
    }

    constexpr ValueType pay() {
        ValueType buff = value;
        value = 0;
        return buff;
    }

    constexpr strength_t getStrength() const {return strength;}

private:
    ValueType value;
    const std::size_t completedExpeditions;
    const strength_t strength;

    constexpr strength_t calcStrength() const {
        if (completedExpeditions == 0) {
            return 0;
        }
        strength_t a = 0, b = 1;
        for (std::size_t i = 2; i <= completedExpeditions; i++) {
            a += b;
            std::swap(a, b);
        }
        return b;
    }
};

#endif // MEMBER_H