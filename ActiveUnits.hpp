#ifndef ACTIVEUNITS_HPP_INCLUDED
#define ACTIVEUNITS_HPP_INCLUDED



#endif // ACTIVEUNITS_HPP_INCLUDED
#include <iostream>
#include <functional>
#include <utility>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Physics.hpp"
#include <memory>
#include "Units.hpp"

#pragma once

class ActiveEntity:public Entity{// obiekty wykonujace samodzielny ruch
public:
    ~ActiveEntity(){};
    ActiveEntity(ObjectTypes &&, sf::Vector2f &&,sf::Texture&);
public:
    bool DoItWannaFire(){return WannaFire;} //ACTIV
    std::unique_ptr<Entity> ReturnBullet(TextureHolder&);   //ACTIV

    bool ConnectionToMove(){return isConnectedToMove;} //ACTIV
protected:
    sf::Texture tekstura;
protected:
    bool isConnectedToMove=0;// ACTIV
    bool WannaFire=0;
};

class Player:public ActiveEntity,public Human{
public:
    Player(ObjectTypes &&, sf::Vector2f &&,sf::Texture& );

    void update() override;
    void MoveEntity(sf::Vector2f& ,sf::Time&,sf::Vector2f&w) override;
    void react(Collision& ) override;
    void AutomaticMove(sf::Time&) override;
    void MoveEntity(sf::Vector2f& );

private:
    sf::Vector2f velocity {200,30};
};

class Enemy:public ActiveEntity,public CellularAutomata{
public:
    void update() override;
    void MoveEntity(sf::Vector2f& ,sf::Time& ,sf::Vector2f&w) override;
    void react(Collision& ) override;
    void AutomaticMove(sf::Time&) override;

    Enemy(ObjectTypes &&, sf::Vector2f &&,sf::Texture& );
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

    BasicWalkingEnemy(ObjectTypes &&, sf::Vector2f &&,sf::Texture& );

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
    Bomb(ObjectTypes &&, sf::Vector2f &&,sf::Texture& );
private:
    sf::Vector2f velocity {0,300};
};

class BasicFlyingEnemy:public ActiveEntity, public CellularAutomata
{
public:
    void update() override;
    void MoveEntity(sf::Vector2f& ,sf::Time& ,sf::Vector2f&w){};
    void react(Collision& ) override;
    void AutomaticMove(sf::Time&) override;
    //void SetDependent(std::shared_ptr<Entity> &d);

    BasicFlyingEnemy(ObjectTypes &&, sf::Vector2f &&,sf::Texture& );

private:
sf::Vector2f velocity {100,100};
int licznik=0;
};
