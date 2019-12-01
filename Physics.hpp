#ifndef PHYSICS_HPP_INCLUDED
#define PHYSICS_HPP_INCLUDED



#endif // PHYSICS_HPP_INCLUDED
#include <iostream>
#include <functional>
#include <utility>
#include <SFML/Graphics.hpp>
#include "Utilities.hpp"
#pragma once


class CellularAutomata{
public:


    sf::Vector2f& RealizeTheMove(sf::Time&);
    sf::Vector2f RealizeTheMoveAndReturnDelta(sf::Time&);
    CellularAutomata(sf::Vector2f& ,bool =true);
    void SetRange(sf::Vector2f&&, sf::Vector2f& );
    void ChangeVelocity(sf::Vector2f&& a){velocity=std::move(a);}

protected:
    sf::Vector2f velocity;
    int uy,dy,lx,px;
    sf::Vector2f laps {0,0};
    bool RightSideMove;// domyslnie wszystkie obiekty poruszaja sie w prawo
    int m=1;
    Dimension kierunek=Dimension::Vertical;

};



class Human{
public:
    void ChangeState(HumanStates&&);
    HumanStates ReturnHumanState();
    sf::Vector2f RealizeTheMove(sf::Vector2f&, sf::Vector2f&, bool , sf::Time& );
    sf::Vector2f RealizeTheFall(sf::Vector2f&,sf::Vector2f&, sf::Time& );

private:
    HumanStates stan=HumanStates::Fall;
    int ograniczenie=SKOK_GR;//domyslny- podany w pixelach, ustalany w konkretnej klasie
    int licznik=0;
};
