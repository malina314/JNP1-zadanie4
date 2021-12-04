#ifndef TREASURE_HUNT_H
#define TREASURE_HUNT_H

#include "treasure.h"
#include "member.h"

template<typename T>
concept ValidTreasure = requires {
    //todo
}

template<typename T>
concept ValidMember = requires {
    // todo
    }

template<typename T>
concept EncounterSide = ValidMember<T> || ValidTreasure<T>;

template<typename sideA, typename sideB>
requires EncounterSide<sideA> && EncounterSide<sideB>
class Encounter {
public:
    template<typename A, typename B>
    requires ValidMember<A> && ValidMember<B>
    constexpr void static run(Encounter<A, B> encounter) {
        bool aIsArmed = encounter.a.isArmed;
        bool bIsArmed = encounter.a.isArmed;
        if (aIsArmed && bIsArmed) {
            auto cmp = encounter.a.getStrength() <=> encounter.b.getStrength();
            if (cmp < 0) {
                encounter.b.loot(SafeTreasure<decltype(encounter.a.pay())>(encounter.a.pay()));
            } else if (cmp > 0) {
                encounter.a.loot(SafeTreasure<decltype(encounter.b.pay())>(encounter.b.pay()));
            }
        } else if (aIsArmed && !bIsArmed) {
            encounter.a.loot(SafeTreasure<decltype(encounter.b.pay())>(encounter.b.pay()));
        } else if (!aIsArmed && bIsArmed) {
            encounter.b.loot(SafeTreasure<decltype(encounter.a.pay())>(encounter.a.pay()));
        }
    }

    template<typename A, typename B>
    requires ValidTreasure<A> && ValidMember<B>
    constexpr void static run(Encounter<A, B> encounter) { //treasure + member
        encounter.a.loot(encounter.b);
    }

    template<typename A, typename B>
    requires ValidMember<A> && ValidTreasure<B>
    constexpr void static run(Encounter<A, B> encounter) { // member + treasure
        encounter.b.loot(encounter.a);
    }

private:
    sideA& a;
    sideB& b;
};

template<typename... Encounters>
void expedition(Encounters... encounters) {
    (run(encounters), ...);
}

#endif // TREASURE_HUNT_H