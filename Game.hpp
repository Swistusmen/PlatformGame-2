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
#include "Interface.hpp"
#include "Controler.hpp"
#include "Batch.hpp"
#include "Loader.hpp"

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
    void ManageGameMechanics(GameMechanisms& );

    void DistributeTheCommands(sf::Time& );
private:
    Controler Kontroler;

    GameStates stanGry =GameStates::Uninitialized;
    sf::RenderWindow appwindow;
    TextureHolder Holder;

    Interface interfejs;//(Holder) ;

    CommandQueue Orders;


};
