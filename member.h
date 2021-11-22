#include "treasure.h"
#include <cstddef>
#include <cstdint>

using strength_t = uint32_t;

template<typename T, bool IsArmed>
class Adventurer {
    // todo: check if T is the same type as in treasure
    T value;

public:
    bool isArmed = IsArmed;
    strength_t strength;

    // ta metoda chyba nie jest "dziedziczona" przez specjalizacje
    // todo: poprawić to
    T pay() {
        T buff = value;
        value = 0;
        return buff;
    }
};

template<typename T>
class Adventurer<T, false> {
    // todo: check if T is the same type as in treasure
    T value;

public:
    bool isArmed;
    strength_t strength;
    constexpr Adventurer() : value(0), strength(0), isArmed(false) {}

    void loot(SafeTreasure<T>&& treasure) {
        value += treasure.getLoot();
    }

};

template<typename T>
class Adventurer<T, true> {
    // todo: check if T is the same type as in treasure
    T value;

public:
    bool isArmed;
    strength_t strength;
    constexpr Adventurer(strength_t stren) : value(0), strength(stren), isArmed(true) {}

    template<bool isTrapped>
    constexpr void loot(Treasure<T, isTrapped>&& treasure) {
        if (isTrapped) {
            strength /= 2;
        }
        value += treasure.getLoot();
    }

    constexpr strength_t getStrength() { return strength; }
};

template<typename T>
using Explorer = Adventurer<T, false>;

template<typename T, std::size_t CompletedExpeditions>
class Veteran {
    // todo: check if T is the same type as in treasure
    T value;
    // todo: check if CompletedExpeditions < 25
    std::size_t completedExpeditions;

public:
    bool isArmed;
    strength_t strength;

    constexpr Veteran() : value(0), completedExpeditions(CompletedExpeditions), isArmed(true) {
        // todo: fibonacci
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
};