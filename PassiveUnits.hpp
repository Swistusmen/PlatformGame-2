#ifndef PASSIVEUNITS_HPP_INCLUDED
#define PASSIVEUNITS_HPP_INCLUDED



#endif // PASSIVEUNITS_HPP_INCLUDED
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

class PasiveEntity:public Entity{// obiekty nie wplywajace na gre- bedace nieruchome, badz zalezne w ruchu i dzialaniu
public:
    std::unique_ptr<Entity> ReturnBullet(TextureHolder&)final {return nullptr;} ;
    bool DoItWannaFire() final {return 0;} ;
    bool ConnectionToMove() final {return 0;};


public:
    void MoveEntity(sf::Vector2f &, sf::Time& ,sf::Vector2f&w) override;
    PasiveEntity(ObjectTypes &&, sf::Vector2f &&,sf::Texture& );

    PasiveEntity(ObjectTypes &&, sf::Vector2f &&, sf::IntRect &&,sf::Texture& );

protected:
    sf::Texture tekstura;
};

namespace gf{
class GroundFloor:public PasiveEntity{
public:
    GroundFloor(ObjectTypes &&, sf::Vector2f &&,sf::Texture& );
    GroundFloor(ObjectTypes &&, sf::Vector2f &&, sf::IntRect &&,sf::Texture& );
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
    EndGate(ObjectTypes &&, sf::Vector2f &&,sf::Texture& );
};

class Platform:public PasiveEntity,public CellularAutomata{
public:
    Platform(ObjectTypes &&, sf::Vector2f &&,sf::Texture& );
    Platform(ObjectTypes &&, sf::Vector2f &&, sf::IntRect &&,sf::Texture& );
    void react(Collision& a){}
    void update( ) override;
    void AutomaticMove(sf::Time& ) override;
private:
    sf::Vector2f velocity{50,50};
};

class Coin:public PasiveEntity{
public:
    Coin(ObjectTypes &&, sf::Vector2f &&,sf::Texture& );
    void react(Collision& a);
    void update( );
    void AutomaticMove(sf::Time& );

private:
    sf::Vector2f stala{0,0};
};
