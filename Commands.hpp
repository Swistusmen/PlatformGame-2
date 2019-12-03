#ifndef COMMANDS_HPP_INCLUDED
#define COMMANDS_HPP_INCLUDED



#endif // COMMANDS_HPP_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Utilities.hpp"
#include "Units.hpp"
#include <functional>
#include <queue>
#pragma once


class command{//potrzebna bêdzie funkcja klasy Level która przyjmuje ObjectTypes i std::function
    //koniecznie trzeba dodać operator przypisujacy
public:
    command(std::function<void (Entity&, sf::Time&,sf::Vector2f&)>& , ObjectTypes&& =ObjectTypes::Hero );
    command(std::function<void (Entity&,sf::Time&,sf::Vector2f&)>&& , ObjectTypes&& =ObjectTypes::Hero);
   // command()=default;
public:
    ObjectTypes& GetObjectTypes();//zwraca typ obiektu
    std::function<void (Entity&, sf::Time&,sf::Vector2f&)>& GetAFunction();//zwraca samą funckje
private:
    std::function<void (Entity&,sf::Time&,sf::Vector2f&)> akcja;
    ObjectTypes przyporzadkowanie;
    sf::Time czas;
};

class CommandQueue{
public:
    CommandQueue()=default;
    void push(const command& komenda);
    command pop();
    bool IsEmpty();
private:
    std::queue<command> kolejka;
};
