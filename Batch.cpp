#include <iostream>
#include <utility>
#include <memory>
#include "Utilities.hpp"
#include "Units.hpp"
#include "SFML/Graphics.hpp"
#include "ActiveUnits.hpp"
#include "PassiveUnits.hpp"
#include "Batch.hpp"


Batch::Batch(TextureHolder& Holder)
{
    std::unique_ptr<Entity> wsk(new Player(ObjectTypes::Hero,sf::Vector2f{2100,100},Holder.GetTexture(ObjectTypes::Hero)));
    _Hero=std::move(wsk);

    std::shared_ptr<Entity> ptr(new gf::GroundFloor(ObjectTypes::GroundFloor,sf::Vector2f(0,1300),sf::IntRect(0,1300,3000,100),Holder.GetTexture(ObjectTypes::GroundFloor)));
    _FirstPlan.push_back(std::move(ptr));

    std::shared_ptr<Entity> platf(new gf::GroundFloor(ObjectTypes::GroundFloor,sf::Vector2f(1000,900),sf::IntRect(1000,900,300,100),Holder.GetTexture(ObjectTypes::GroundFloor)));
    _FirstPlan.push_back(std::move(platf));

    std::shared_ptr<Observer> obs (new Observer);
    _Observers.push_back(std::move(obs));

    std::shared_ptr<Entity> ptrr(new EndGate(ObjectTypes::End,sf::Vector2f{2000,1200},Holder.GetTexture(ObjectTypes::End)));
    ptrr->SetObserver((_Observers.back()));
    _SpecialPoints.push_back(std::move(ptrr));

    std::shared_ptr<Entity> te (new Platform(ObjectTypes::Platforma,sf::Vector2f(1800,800),sf::IntRect(1800,800,300,100),Holder.GetTexture(ObjectTypes::Platforma)));
    _FirstPlan.push_back(std::move(te));

    std::shared_ptr<Observer> obss (new Observer);
    _Observers.push_back(std::move(obss));


    std::unique_ptr<Entity> tet(new Coin(ObjectTypes::Dolar,sf::Vector2f{-100,200},Holder.GetTexture(ObjectTypes::Dolar)));
    tet->SetDependent(_FirstPlan.back());
    tet->SetObserver(_Observers.back());
    _Findings.push_back(std::move(tet));

    obss.reset(new Observer);
    _Observers.push_back(obss);//nowe
    tet.reset(new Coin(ObjectTypes::Dolar,sf::Vector2f{100,1200},Holder.GetTexture(ObjectTypes::Dolar)));
    tet->SetObserver(_Observers.back());
    _Findings.push_back(std::move(tet));

    tet.reset(new BasicWalkingEnemy(ObjectTypes::BWEnemy,sf::Vector2f{600,1200},Holder.GetTexture(ObjectTypes::BWEnemy)));
    obss.reset(new Observer);

    _Observers.push_back(obss);//nowe
    tet->SetObserver(_Observers.back());
    _Monsters.push_back(std::move(tet));

    tet.reset(new BasicFlyingEnemy(ObjectTypes::BFEnemy,sf::Vector2f{1000,100},Holder.GetTexture(ObjectTypes::BFEnemy)));
    obss.reset(new Observer);
    _Observers.push_back(obss);//nowe
    tet->SetObserver(_Observers.back());
    _Monsters.push_back(std::move(tet));
}
