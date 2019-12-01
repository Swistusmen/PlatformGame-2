#include <iostream>
#include <utility>
#include <memory>
#include "Units.hpp"
#include "Utilities.hpp"
#include "Game.hpp"
#include "Observer.hpp"


/*
class Observer{
public:
    void SawSomething (ObjectTypes ,ObjectTypes);
    GameStates ReturnDetection();
    bool Detection=0;
private:
    GameStates stan;
};*/

void Observer::SawSomething(ObjectTypes moj,ObjectTypes obcy)
{
    if((moj==ObjectTypes::End)&&(obcy==ObjectTypes::Hero))
    {
        Detection=1;
        stan=GameStates::Winner;
    }
}
