#ifndef TREASURE_HUNT_H
#define TREASURE_HUNT_H

#include "treasure.h"
#include "member.h"

template<typename T>
concept ValidTreasure = requires (T t) {
    std::same_as<T, Treasure<decltype(t.evaluate()), true>>
        || std::same_as<T, Treasure<decltype(t.evaluate()), false>>;
};

template<typename M, typename T>
concept HasLootMethod = requires(T &&t, M m) {
    {m.loot(std::forward(t))};
};

template<typename T>
concept ValidMember = requires(T m) {
    typename T::strength_t;
    {m.pay()} -> TreasureValueType;
    m.isArmed;
    {[]() constexpr {return T::isArmed;}()};
    std::convertible_to<decltype(m.isArmed), bool>;
    HasLootMethod<T, SafeTreasure<decltype(m.pay())>>;
    HasLootMethod<T, TrappedTreasure<decltype(m.pay())>>;
};

template<typename T>
concept EncounterSide = ValidMember<T> || ValidTreasure<T>;

template<EncounterSide sideA, EncounterSide sideB>
class Encounter {
public:
    sideA &a;
    sideB &b;

    constexpr Encounter(sideA &a, sideB &b) : a(a), b(b) {}
};

template<typename A, typename B>
constexpr void run(Encounter<A, B> encounter) = delete;

template<ValidMember A, ValidMember B>
constexpr void run(Encounter<A, B> encounter) { // member + member
    constexpr bool aIsArmed = encounter.a.isArmed;
    constexpr bool bIsArmed = encounter.b.isArmed;
    if constexpr (aIsArmed && bIsArmed) {
        auto cmp = encounter.a.getStrength() <=> encounter.b.getStrength();
        if (cmp < 0) {
            encounter.b.loot(SafeTreasure<decltype(encounter.a.pay())>(encounter.a.pay()));
        } else if (cmp > 0) {
            encounter.a.loot(SafeTreasure<decltype(encounter.b.pay())>(encounter.b.pay()));
        }
    } else if constexpr (aIsArmed) {
        encounter.a.loot(SafeTreasure<decltype(encounter.b.pay())>(encounter.b.pay()));
    } else if constexpr (bIsArmed) {
        encounter.b.loot(SafeTreasure<decltype(encounter.a.pay())>(encounter.a.pay()));
    }
}

template<ValidTreasure A, ValidMember B>
constexpr void run(Encounter<A, B> encounter) { // treasure + member
    encounter.b.loot(std::move(encounter.a));
}

template<ValidMember A, ValidTreasure B>
constexpr void run(Encounter<A, B> encounter) { // member + treasure
    encounter.a.loot(std::move(encounter.b));
}

template<typename... Encounters>
constexpr void expedition(Encounters... encounters) {
    (run(encounters), ...);
}

#endif // TREASURE_HUNT_H