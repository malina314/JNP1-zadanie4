#ifndef MEMBER_H
#define MEMBER_H

#include "treasure.h"
#include <algorithm>
#include <cstddef>
#include <cstdint>

template<typename T, bool IsArmed>
requires TreasureValueType<T>
class Adventurer {}; // Klasa jest implementowana poprzez specjalizacje.

template<typename T>
requires TreasureValueType<T>
class Adventurer<T, false> {
public:
    using strength_t = uint32_t;

    static constexpr bool isArmed = false;

    constexpr Adventurer() : value(0), strength(0) {}

    // todo (Mateusz): sprawdzić czy tutaj nie powinno być T2
    constexpr void loot(SafeTreasure<T>&& treasure) {
        value += treasure.getLoot();
    }

    constexpr T pay() {
        T buff = value;
        value = 0;
        return buff;
    }

private:
    T value;
    const strength_t strength;
};

template<typename T>
requires TreasureValueType<T>
class Adventurer<T, true> {
public:
    using strength_t = uint32_t;

    static constexpr bool isArmed = true;

    constexpr explicit Adventurer(strength_t stren) : value(0), strength(stren) {}

    template<bool isTrapped>
    constexpr void loot(Treasure<T, isTrapped>&& treasure) {
        if (isTrapped) {
            strength /= 2;
        }
        value += treasure.getLoot();
    }

    constexpr strength_t getStrength() const {return strength;}

    constexpr T pay() {
        T buff = value;
        value = 0;
        return buff;
    }

private:
    T value;
    strength_t strength;
};

template<typename T>
using Explorer = Adventurer<T, false>;

template<typename T, std::size_t CompletedExpeditions>
requires TreasureValueType<T> && (CompletedExpeditions < 25)
class Veteran {
public:
    using strength_t = uint32_t;

    static constexpr bool isArmed = true;

    constexpr Veteran() : value(0), completedExpeditions(CompletedExpeditions),
        strength(calcStrength()) {}

    template<bool isTrapped>
    constexpr void loot(Treasure<T, isTrapped>&& treasure) {
        value += treasure.getLoot();
    }

    constexpr strength_t getStrength() const {return strength;}

    constexpr T pay() {
        T buff = value;
        value = 0;
        return buff;
    }

private:
    T value;
    const std::size_t completedExpeditions;
    const strength_t strength;

    constexpr strength_t calcStrength() const {
        if (CompletedExpeditions == 0) {
            return 0;
        }
        strength_t a = 0, b = 1;
        for (std::size_t i = 2; i <= CompletedExpeditions; i++) {
            a += b;
            std::swap(a, b);
        }
        return b;
    }
};

#endif // MEMBER_H