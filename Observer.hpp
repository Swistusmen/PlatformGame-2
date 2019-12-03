#ifndef OBSERVER_HPP_INCLUDED
#define OBSERVER_HPP_INCLUDED



#endif // OBSERVER_HPP_INCLUDED
#pragma once
#include <iostream>
#include <utility>
#include <memory>
#include "Utilities.hpp"
#include "Game.hpp"
#pragma once

//obserwator jest metoda push, tj. jest wciagany przez obserwowany obiekt, w razie sytuacji zobaczenia
// jakiegos dzialania, a obiekt wysyla info do obserwatora, obserwator musi miec referencje na klase Game, musi ja
// zawiadamiac, ale odpowiedzialnosc za czytanie lezy po stronie klasy Game

//problem w jaki sposob obserwver ma informowac game?- niech istnieje oddzielny obiekt w klasie game
//ktory posiada zbior obserwatorow, niech kazdy obserwowany obiekt ma swojego obserwatora w tej strukturze danych
// problem? jak automatycznie tworzyc i obserwatora i obiekt w klasie- obserwator musi byc wrzucany do klasy
// z zewnatrz co znaczy ze musi byc najpierw zaimplementowany w klasie gra, niech powstanie funkcja ktora
// odpowiada na pytanie czy chce obserwatora,jesli odpowiedz brzmi tak, niech w konstruktorze gry zostanie
//przydzielona referencja obserwatora

//reakcja na zaobserwowane rzeczy musi nastepowac razem z reakcja na kolizje


class Observer{
public:
    void SawSomething (ObjectTypes ,ObjectTypes);
    GameStates ReturnObserwation(){Detection=0;return stan;};
    bool WasSomethingObserved(){return stan;};
private:
    bool Detection=0;
    GameStates stan;
};
