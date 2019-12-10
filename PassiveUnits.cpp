#include <iostream>
#include <functional>
#include <utility>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Physics.hpp"
#include <memory>
#include "Units.hpp"
#include "PassiveUnits.hpp"

///////////////////////////////// COIN

void Coin::AutomaticMove(sf::Time& )
{
if(dependent!=nullptr)
{
placement.x=dependent->ReturnPosition().x+stala.x;
placement.y=dependent->ReturnPosition().y+stala.y;
}
}

void Coin::react(Collision& a)
{
    if(obserwator!=nullptr)
    obserwator->MarkMeAsNoNedeed();
    obserwator->SawSomething(this->RetTypeOfObject(),a.typ);
    FreeObserver();
    FreeDependent();
}

void Coin::update()
{
    sprite.setPosition(placement);
}

Coin::Coin(ObjectTypes && a, sf::Vector2f && b,sf::Texture& c):PasiveEntity(std::move(a),std::move(b),c)
{
    stala=std::move(b);
    stala.x=-stala.x;
    stala.y=-stala.y;
}

/////////////////////////// PLATFORM

void Platform::AutomaticMove(sf::Time& dt)
{
    placement=RealizeTheMove(dt);
}

void Platform::update()
{
    sprite.setPosition(placement);
}

Platform::Platform(ObjectTypes && a, sf::Vector2f && b,sf::Texture& c):PasiveEntity(std::move(a),std::move(b),c),CellularAutomata(velocity)
{
    SetRange(sf::Vector2f{500,100},ReturnPosition());
}

Platform::Platform(ObjectTypes && a, sf::Vector2f && b, sf::IntRect && c,sf::Texture& d):PasiveEntity(std::move(a),std::move(b),std::move(c),d),CellularAutomata(velocity)
{
    SetRange(sf::Vector2f{500,100},ReturnPosition());
}

/////////////////////////// END GATE
void EndGate::react(Collision& a)
{
    std::cout<<"Reakcja\n";
    if(a.typ==Hero)
        obserwator->SawSomething(typ,a.typ);
}

void EndGate::update()
{
    sprite.setPosition(placement);
}

EndGate::EndGate(ObjectTypes && a, sf::Vector2f &&b,sf::Texture& c ):PasiveEntity(std::move(a),std::move(b),c)
{
    DoIWantAnObserwer=true;
}

////////////////////////////// GroundFloor
void gf::GroundFloor::update()
{
    sprite.setPosition(placement);
}

void gf::GroundFloor::AutomaticMove(sf::Time& a)
{
}

gf::GroundFloor::GroundFloor(ObjectTypes && a, sf::Vector2f && b,sf::Texture& c):PasiveEntity(std::move(a),std::move(b),c){};

gf::GroundFloor::GroundFloor(ObjectTypes && a, sf::Vector2f && b, sf::IntRect && c,sf::Texture& d):PasiveEntity(std::move(a),std::move(b),std::move(c),d)
{
d.setRepeated(true);
};

///////////////////////// Pasive Entity


void PasiveEntity::MoveEntity(sf::Vector2f& a,sf::Time& b, sf::Vector2f& c)
{
    placement+=a;
}

PasiveEntity::PasiveEntity(ObjectTypes && a, sf::Vector2f && b,sf::IntRect && c,sf::Texture& d):Entity(std::move(a),std::move(b))
{
    tekstura=d;
    sprite.setTexture(tekstura);

    sprite.setTextureRect(sf::IntRect(std::move(c)));
    tekstura.setRepeated(true);
}

PasiveEntity::PasiveEntity(ObjectTypes && a, sf::Vector2f && b,sf::Texture& c):Entity(std::move(a),std::move(b))
{
    tekstura=c;
    sprite.setTexture(tekstura);
    //sprite.setScale(std::move(d));
}


