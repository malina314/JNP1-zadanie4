#ifndef TREASURE_HUNT_H
#define TREASURE_HUNT_H

#include "treasure.h"
#include "member.h"

template<typename T>
concept EncounterSide = requires() {
    //todo (Michał):
    // zaimplementować to
};

template<typename sideA, typename sideB>
requires EncounterSide<sideA> && EncounterSide<sideB>
class Encounter {
    sideA& a;
    sideB& b;

    constexpr void run(Encounter encounter) {
        //todo (Michał):
        // zaimplementować to
    }
};

// todo (wspólnie): poprawić to
//  ale chyba najpierw trzeba zrobi wcześniejsze rzeczy
//  na pewno musi być variadic template
template<typename sideA, typename sideB>
void expedition(Encounter<sideA, sideB>... E) {
    // lepiej użyć folda
    for (auto e : E) {
        run(r);
    }
}

#endif // TREASURE_HUNT_H