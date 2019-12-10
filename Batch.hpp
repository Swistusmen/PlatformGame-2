#ifndef BATCH_HPP_INCLUDED
#define BATCH_HPP_INCLUDED



#endif // BATCH_HPP_INCLUDED
#include <iostream>
#include <utility>
#include <memory>
#include "Utilities.hpp"
#include "Units.hpp"
#include "SFML/Graphics.hpp"
#include "ActiveUnits.hpp"
#include "PassiveUnits.hpp"
#pragma once

struct Batch{
public:
    Batch(TextureHolder& Holder);
    ~Batch(){std::cout<<"Batch zostal zniszczony\n";}

public:
    std::unique_ptr<Entity> _Hero;
    std::vector<std::unique_ptr<Entity>> _Monsters;
    std::vector<std::unique_ptr<Entity>> _Bullets;
    std::vector<std::unique_ptr<Entity>> _Findings;
    std::vector<std::shared_ptr<Entity>> _FirstPlan;
    std::vector<std::shared_ptr<Entity>> _SpecialPoints;
    std::vector<std::unique_ptr<Entity>> _SecondPlan;

    std::vector<std::shared_ptr<Observer>> _Observers;
};
