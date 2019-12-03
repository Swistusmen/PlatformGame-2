#ifndef INTERFACE_HPP_INCLUDED
#define INTERFACE_HPP_INCLUDED



#endif // INTERFACE_HPP_INCLUDED
#include <iostream>
#include <utility>
#include <memory>
#include "Utilities.hpp"
#include "Units.hpp"
#include "Commands.hpp"
#include "SFML/Graphics.hpp"
#pragma once


class Interface{
public:
    void AutomaticMove(sf::Time& dt);
    void DetectCollisions();
    void DistributeCommands(CommandQueue& , sf::Time& );
    std::vector<std::shared_ptr<Observer>>& LookForObservations();
    void TakeBackObservator(std::vector<std::shared_ptr<Observer>>&& );

    void DeleteNoNeededObservators();
    void update();
    void draw(sf::RenderWindow& );
    void RespNewObjects(TextureHolder& );

    int Increment_Observers_IteratorPosition();//-1 jesli blad, w innym wypadku inkremenuje
    GameMechanisms&& ReturnMechanismFromTheObserwver();
    void StartSearchingForMechanics();
    bool IsEnd(){if (it1==_Observers.end())return 0; return 1;}




    Interface( TextureHolder& );

private:
    void MustBeDetectedFirst();
    void DetectFindings();
    void DetectBullets();
    void DetectSpecialPoints();
    void DetectFirstPlan();
    void DetectMonsters();

    void AutomaticFiring(TextureHolder&);
private:

    std::unique_ptr<Entity> _Hero;
    std::vector<std::unique_ptr<Entity>> _Monsters;
    std::vector<std::unique_ptr<Entity>> _Bullets;
    std::vector<std::unique_ptr<Entity>> _Findings;
    std::vector<std::shared_ptr<Entity>> _FirstPlan;
    std::vector<std::shared_ptr<Entity>> _SpecialPoints;
    std::vector<std::unique_ptr<Entity>> _SecondPlan;

    std::vector<std::shared_ptr<Observer>> _Observers;

    std::vector<std::shared_ptr<Observer>>::iterator it1;
    std::vector<std::unique_ptr<Entity>>::iterator it2;
    std::vector<std::shared_ptr<Entity>>::iterator it3;
};
