#include <iostream>
#include <functional>
#include <utility>
#include <SFML/Graphics.hpp>
#include "Utilities.hpp"
#include "Physics.hpp"

sf::Vector2f Human::RealizeTheFall(sf::Vector2f& polozenie,sf::Vector2f& predkosc, sf::Time& dt)
{
    int k=(predkosc.y*dt.asSeconds()*15);
    if(stan==HumanStates::Fall)
    {
        polozenie.y=polozenie.y+k;
        if(polozenie.y>WYSOKOSCOKNA)
        {
            polozenie.y=WYSOKOSCOKNA;
            //ChangeState(HumanStates::Stand);
        }
    }
    else if(stan==HumanStates::Jump)
        {
        if(licznik+k<ograniczenie)
        {
            licznik+=k;
            polozenie.y=polozenie.y-k;
        }
        else
        {
            ChangeState(HumanStates::Fall);
            licznik=0;
            polozenie.y=polozenie.y+k;
        }
        if(polozenie.y<0)
        {
            polozenie.y=0;
            ChangeState(HumanStates::Fall);
            licznik=0;
        }
    }
    return polozenie;
}

sf::Vector2f Human::RealizeTheMove(sf::Vector2f& polozenie, sf::Vector2f& predkosc, bool isZero, sf::Time& dt)
{
    int k=(predkosc.y*dt.asSeconds()*15);
        if(isZero==false)
        {
          ChangeState(HumanStates::Jump);
          licznik+=k;
            polozenie.y=polozenie.y-k;
        }
         return polozenie;
}




HumanStates Human::ReturnHumanState()
{
    return stan;
}

void Human::ChangeState(HumanStates&& a)
{
    stan=std::move(a);
}


/////////////////////////// Cellular Automata


sf::Vector2f& CellularAutomata::RealizeTheMove(sf::Time& dt)
{
    switch(kierunek)
    {
        case Dimension::Vertical:
            {
        int k=dt.asSeconds()*velocity.x*10;
            laps.x+=k*m;
        if(laps.x>=px)
        {
            kierunek=Dimension::Horizontal;
            laps.x=px;
        }
        else if(laps.x<=lx)
        {

            laps.x=lx;
            kierunek=Dimension::Horizontal;
        }
        }break;
        case Dimension::Horizontal:
            {

                int k=dt.asSeconds()*velocity.y*10;
                laps.y+=k*m;
                if(laps.y>=dy)
                {
                    laps.y=dy;
                    kierunek=Dimension::Vertical;
                    m=-1;
                }
                else if(laps.y<=uy)
                {
                    laps.y=uy;
                    kierunek=Dimension::Vertical;
                    m=1;
                }
            }break;
    }
    return laps;
}

sf::Vector2f CellularAutomata::RealizeTheMoveAndReturnDelta(sf::Time& dt)
{
    sf::Vector2f buffer=laps;
    switch(kierunek)
    {
        case Dimension::Vertical:
            {
        int k=dt.asSeconds()*velocity.x*10;
            laps.x+=k*m;
        if(laps.x>=px)
        {
            kierunek=Dimension::Horizontal;
            laps.x=px;
        }
        else if(laps.x<=lx)
        {

            laps.x=lx;
            kierunek=Dimension::Horizontal;
        }
        }break;
        case Dimension::Horizontal:
            {

                int k=dt.asSeconds()*velocity.y*10;
                laps.y+=k*m;
                if(laps.y>=dy)
                {
                    laps.y=dy;
                    kierunek=Dimension::Vertical;
                    m=-1;
                }
                else if(laps.y<=uy)
                {
                    laps.y=uy;
                    kierunek=Dimension::Vertical;
                    m=1;
                }
            }break;
    }
    buffer=laps-buffer;
    return buffer;
}

void CellularAutomata::SetRange(sf::Vector2f&& zakres,sf::Vector2f& pol)
{

    //sf::Vector2f range=std::move(zakres);
    lx=pol.x;
    px=pol.x+zakres.x;
    uy=pol.y;
    dy=pol.y+zakres.y;
    laps.x=lx;
    laps.y=uy;
}

CellularAutomata::CellularAutomata(sf::Vector2f& v, bool a)
{

    velocity=sf::Vector2f{20,20};
    RightSideMove=a;
}

