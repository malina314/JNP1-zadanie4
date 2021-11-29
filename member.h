#ifndef MEMBER_H
#define MEMBER_H

#include "treasure.h"
#include <cstddef>
#include <cstdint>

template<typename T, bool IsArmed>
requires TreasureValueType<T>
class Adventurer {
public:
    using strength_t = uint32_t;

    static constexpr bool isArmed = IsArmed;

    // ta metoda chyba nie jest "dziedziczona" przez specjalizacje
    // todo (Mateusz): poprawić to
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
requires TreasureValueType<T>
class Adventurer<T, false> {
public:
    using strength_t = uint32_t;

    static constexpr bool isArmed = false;

    constexpr Adventurer() : value(0), strength(0) {}

    constexpr void loot(SafeTreasure<T>&& treasure) {
        value += treasure.getLoot();
    }

private:
    T value;
    strength_t strength;
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

    constexpr strength_t getStrength() { return strength; }

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

    constexpr Veteran() : value(0), completedExpeditions(CompletedExpeditions) {
        // todo (Mateusz): fibonacci
        strength = 0;
    }

    template<bool isTrapped>
    constexpr void loot(Treasure<T, isTrapped>&& treasure) {
        value += treasure.getLoot();
    }

    T pay() {
        T buff = value;
        value = 0;
        return buff;
    }

    constexpr strength_t getStrength() { return strength; }


private:
    T value;
    strength_t strength;
    std::size_t completedExpeditions;
};

#endif // MEMBER_H