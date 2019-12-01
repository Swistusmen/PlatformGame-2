#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED



#endif // GAME_HPP_INCLUDED
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Units.hpp"
#include "Utilities.hpp"
#include "Commands.hpp"
//#include "Observer.hpp"
#pragma once


class Game{
public:
    public:
    void Run();
    Game();
private:
    void draw();
    void update();

private:
    void HandleEvent();
    void ProcessEvent();//ta i powyzsza funkcja sa stosowane do zmiany stanu gry
    void ProcessInput();//pobieranie inputu w real time i wydawanie komend bohaterowi

    void DistributeTheCommands(sf::Time& );
private:
    GameStates stanGry =GameStates::Uninitialized;
    sf::RenderWindow appwindow;
    TextureHolder Holder;

    CommandQueue Orders;
    std::unique_ptr<Entity> Gracz;
    std::unique_ptr<Entity> ziemia;
    std::unique_ptr<Entity> ziemia_wyspa;

    std::unique_ptr<Entity> wrog;
    std::unique_ptr<Entity> brama;

    std::vector<std::unique_ptr<Entity>> wektor;
    std::vector<std::unique_ptr<Entity>>::iterator it2;
    std::vector<std::unique_ptr<Entity>>::iterator it3;

    std::vector<std::unique_ptr<Entity>> potwory;
    std::vector<std::unique_ptr<Entity>> pociski;

    std::shared_ptr<Entity> test;
    std::vector<std::shared_ptr<Observer>> obserwatorzy;

};
