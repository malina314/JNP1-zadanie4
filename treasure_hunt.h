#ifndef TREASURE_HUNT_H
#define TREASURE_HUNT_H

#include "treasure.h"
#include "member.h"

template<typename T>
concept ValidTreasure = requires {}

template<typename T>
concept ValidMember = requires {}

template<typename T>
concept EncounterSide = ValidMember<T> || ValidTreasure<T>;

template<typename sideA, typename sideB>
requires EncounterSide<sideA> && EncounterSide<sideB>
class Encounter {
public:
    template<typename A, typename B>
    requires ValidMember<A> && ValidMember<B>
    constexpr void static run(Encounter<A, B> encounter) {
        //member + member
    }

    template<typename A, typename B>
    requires ValidTreasure<A> && ValidMember<B>
    constexpr void static run(Encounter<A, B> encounter) {
        //treasure + member
    }

    template<typename A, typename B>
    requires ValidMember<A> && ValidTreasure<B>
    constexpr void static run(Encounter<A, B> encounter) = run(Encounter(encounter.b, encounter.a));
            //treasure + member
private:
    sideA& a;
    sideB& b;
};

template<typename... Encounters>
void expedition(Encounters... encounters) {
    (run(encounters), ...);
}

#endif // TREASURE_HUNT_H