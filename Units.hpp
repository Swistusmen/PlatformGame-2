#ifndef UNITS_HPP_INCLUDED
#define UNITS_HPP_INCLUDED



#endif // UNITS_HPP_INCLUDED
#include <iostream>
#include <functional>
#include <utility>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Physics.hpp"
#include <memory>
//#include "Observer.hpp"
#pragma once

//usunac dependent w konstruktorze Coin

class EntityInterface
{
public:
    virtual void update()=0;
    virtual void react(Collision& )=0;//reakcja na wykryte kolizje
    virtual void MoveEntity(sf::Vector2f& ,sf::Time& ,sf::Vector2f& w)=0;
    virtual void AutomaticMove( sf::Time&)=0;

public:
    virtual bool DoItWannaFire()=0;//{return WannaFire;} //ACTIV
    virtual bool ConnectionToMove()=0;//{return isConnectedToMove;}
};

class Entity:public EntityInterface{
public:
Collision DoTheyCover(Entity& );// funkja sprawdza czy obiekty zachodza, jesli tak zwraca wektor zchodzenia
                                //CZY NIE DA SIE WYDZIELIC TEJ FUNKCJONALNOSCI JAKO OSOBNEJ KLASY
    //zostaje
void draw (sf::RenderWindow& );
ObjectTypes& RetTypeOfObject();
const sf::Vector2f& ReturnCurrentPlacement();
const sf::FloatRect ReturnTheShape();
sf::Vector2f& ReturnPosition(){return placement;} //zostaja

bool WantAnObserver(){return DoIWantAnObserwer;}
void SetObserver(std::shared_ptr<Observer>& o){if(o!=nullptr){obserwator=o;std::cout<<"mam\n";}}
void FreeObserver(){obserwator->MarkMeAsNoNedeed();obserwator=nullptr;} //ZOSTAJA

void SetDependent(std::shared_ptr<Entity> &d){if(dependent==nullptr)dependent=d;} //ZOSTAJE
void SetDependent(const std::shared_ptr<Entity> &d){if(dependent==nullptr)dependent=d;} //ZOSTAJE
void FreeDependent(){dependent=nullptr;} //ZOSTAJE
void SetScale(sf::Vector2f& );
    //zostaje

virtual ~Entity();

Entity(ObjectTypes &&, sf::Vector2f &&);// do obiektow pasywynych

virtual std::unique_ptr<Entity> ReturnBullet(TextureHolder&)=0;

protected:
std::shared_ptr<Observer> obserwator; //ZOSTAJE
std::shared_ptr<Entity> dependent; //ZOSTAJE
bool DoIWantAnObserwer=0; //ZOSTAJE

sf::Sprite sprite;
ObjectTypes typ;
sf::Vector2f placement;
sf::Vector2f wzlgedem {0,0}; //ZOSTAJE

};
