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

//problem: wrzucani obserwatorzy to nullptr, przez co trudno ich obslugiwac
//dowiedziec sie jak pzekazywac shared pointery

class Entity{
public:

virtual void update()=0;

virtual void react(Collision& )=0;//reakcja na wykryte kolizje
virtual void MoveEntity(sf::Vector2f& ,sf::Time& ,sf::Vector2f& w)=0;
virtual void AutomaticMove( sf::Time&)=0;

void MoveEntity(sf::Vector2f& );// funkcja dla obiektow poruszajacych sie na platformach, tak jak platforma
void draw (sf::RenderWindow& );
ObjectTypes& RetTypeOfObject();
Collision DoTheyCover(Entity& );// funkja sprawdza czy obiekty zachodza, jesli tak zwraca wektor zchodzenia
const sf::Vector2f& ReturnCurrentPlacement();
const sf::FloatRect ReturnTheShape();
sf::Vector2f& ReturnPosition(){return placement;}
bool WantAnObserver(){return DoIWantAnObserwer;}
void SetObserver(std::shared_ptr<Observer>& o){if(o!=nullptr){obserwator=o;std::cout<<"mam\n";}}
void FreeObserver(){obserwator->MarkMeAsNoNedeed();obserwator=nullptr;}
void SetDependent(std::shared_ptr<Entity> &d){if(dependent==nullptr)dependent=d;}
void SetDependent(const std::shared_ptr<Entity> &d){if(dependent==nullptr)dependent=d;}
void FreeDependent(){dependent=nullptr;}

bool DoItWannaFire(){return WannaFire;}
std::unique_ptr<Entity> ReturnBullet(TextureHolder&);

bool ConnectionToMove(){return isConnectedToMove;}

virtual ~Entity();

Entity(ObjectTypes &&, sf::Vector2f &&);// do obiektow pasywynych

protected:
bool isConnectedToMove=0;//do poruszania sie po plalformie
std::shared_ptr<Observer> obserwator;
std::shared_ptr<Entity> dependent;
//Observer obserwator;
bool DoIWantAnObserwer=0;
bool WannaFire=0;
sf::Sprite sprite;
ObjectTypes typ;
sf::Vector2f placement;

sf::Vector2f wzlgedem {0,0};
};

class PasiveEntity:public Entity{// obiekty nie wplywajace na gre- bedace nieruchome, badz zalezne w ruchu i dzialaniu
public:
    void MoveEntity(sf::Vector2f &, sf::Time& ,sf::Vector2f&w) override;
    PasiveEntity(ObjectTypes &&, sf::Vector2f &&,sf::Texture& ,sf::Vector2f&&= sf::Vector2f(1,1));
    PasiveEntity(ObjectTypes &&, sf::Vector2f &&, sf::IntRect &&,sf::Texture& ,sf::Vector2f&&= sf::Vector2f(1,1));
protected:
    sf::Texture tekstura;
};

class ActiveEntity:public Entity{// obiekty wykonujace samodzielny ruch
public:
    ~ActiveEntity(){};
    ActiveEntity(ObjectTypes &&, sf::Vector2f &&,sf::Texture&,sf::Vector2f&&= sf::Vector2f(1,1));
protected:
    sf::Texture tekstura;
};

class Player:public ActiveEntity,public Human{
public:
    Player(ObjectTypes &&, sf::Vector2f &&,sf::Texture& ,sf::Vector2f&&= sf::Vector2f(1,1));

    void update() override;
    void MoveEntity(sf::Vector2f& ,sf::Time&,sf::Vector2f&w) override;
    void react(Collision& ) override;
    void AutomaticMove(sf::Time&) override;
    void MoveEntity(sf::Vector2f& );

    void Hello(){std::cout<<"Hello world\n";}
private:
    sf::Vector2f velocity {200,30};
};

class Enemy:public ActiveEntity,public CellularAutomata{
public:
    void update() override;
    void MoveEntity(sf::Vector2f& ,sf::Time& ,sf::Vector2f&w) override;
    void react(Collision& ) override;
    void AutomaticMove(sf::Time&) override;

    Enemy(ObjectTypes &&, sf::Vector2f &&,sf::Texture& ,sf::Vector2f&&= sf::Vector2f(1,1));
private:
sf::Vector2f velocity {100,20};
};

class BasicWalkingEnemy:public ActiveEntity,public CellularAutomata{
public:
    void update() override;
    void MoveEntity(sf::Vector2f& ,sf::Time& ,sf::Vector2f&w){};
    void react(Collision& ) override;
    void AutomaticMove(sf::Time&) override;
    void SetDependent(std::shared_ptr<Entity> &d);

    BasicWalkingEnemy(ObjectTypes &&, sf::Vector2f &&,sf::Texture& ,sf::Vector2f&&= sf::Vector2f(1,1));

private:
sf::Vector2f velocity {100,0};
//sf::Vector2f bufor{0,0};
};

class Bomb:public ActiveEntity{
public:
    void update() override;
    void MoveEntity(sf::Vector2f& ,sf::Time& ,sf::Vector2f&w) {};
    void react(Collision& );
    void AutomaticMove(sf::Time&) override;

    //~Bomb();
    Bomb(ObjectTypes &&, sf::Vector2f &&,sf::Texture& ,sf::Vector2f&&= sf::Vector2f(1,1));
private:
    sf::Vector2f velocity {0,300};
};

namespace gf{
class GroundFloor:public PasiveEntity{
public:
    GroundFloor(ObjectTypes &&, sf::Vector2f &&,sf::Texture& ,sf::Vector2f&&= sf::Vector2f(1,1));
    GroundFloor(ObjectTypes &&, sf::Vector2f &&, sf::IntRect &&,sf::Texture& ,sf::Vector2f&&= sf::Vector2f(1,1));
    void react(Collision& a){}
    void update( ) override;
    void AutomaticMove(sf::Time& ) override;
};
}

class EndGate:public PasiveEntity{
public:
    void react(Collision& a);
    void update( ) override;
    void AutomaticMove(sf::Time& ){}
    EndGate(ObjectTypes &&, sf::Vector2f &&,sf::Texture& ,sf::Vector2f&&= sf::Vector2f(1,1));
};

class Platform:public PasiveEntity,public CellularAutomata{
public:
    Platform(ObjectTypes &&, sf::Vector2f &&,sf::Texture& ,sf::Vector2f&&= sf::Vector2f(1,1));
    Platform(ObjectTypes &&, sf::Vector2f &&, sf::IntRect &&,sf::Texture& ,sf::Vector2f&&= sf::Vector2f(1,1));
    void react(Collision& a){}
    void update( ) override;
    void AutomaticMove(sf::Time& ) override;
private:
    sf::Vector2f velocity{50,50};
};

class Coin:public PasiveEntity{
public:
    Coin(ObjectTypes &&, sf::Vector2f &&,sf::Texture& ,const std::shared_ptr<Entity>& =nullptr,sf::Vector2f&&= sf::Vector2f(1,1));
    void react(Collision& a);
    void update( );
    void AutomaticMove(sf::Time& );

private:
    sf::Vector2f stala{0,0};
};

class BasicFlyingEnemy:public ActiveEntity, public CellularAutomata
{
public:
    void update() override;
    void MoveEntity(sf::Vector2f& ,sf::Time& ,sf::Vector2f&w){};
    void react(Collision& ) override;
    void AutomaticMove(sf::Time&) override;
    //void SetDependent(std::shared_ptr<Entity> &d);

    BasicFlyingEnemy(ObjectTypes &&, sf::Vector2f &&,sf::Texture& ,sf::Vector2f&&= sf::Vector2f(1,1));

private:
sf::Vector2f velocity {100,100};
int licznik=0;
};

