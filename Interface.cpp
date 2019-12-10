#include <iostream>
#include <utility>
#include <memory>
#include "Utilities.hpp"
//#include "Units.hpp"
#include "Commands.hpp"
#include "Interface.hpp"
#include "ActiveUnits.hpp"
#include "PassiveUnits.hpp"
#include "Batch.hpp"


Interface::Interface(std::unique_ptr<Batch>&& batch)
{
    TakeBatch(std::move(batch));
}

void Interface::TakeBatch(std::unique_ptr<Batch>&& batch)
{
    std::cout<<"Przyjalem\n";
    _Hero=std::move(batch->_Hero);
    _Monsters=std::move(batch->_Monsters);
    _Bullets=std::move(batch->_Bullets);
    _Findings=std::move(batch->_Findings);
    _FirstPlan=std::move(batch->_FirstPlan);
    _SpecialPoints=std::move(batch->_SpecialPoints);
    _SecondPlan=std::move(batch->_SecondPlan);
    _Observers=std::move(batch->_Observers);
    batch.reset();
}

void Interface::RespNewObjects(TextureHolder& Holder)
{
    AutomaticFiring(Holder);
}

void Interface::AutomaticFiring(TextureHolder& Holder)
{
    for(it2=_Monsters.begin();it2!=_Monsters.end();it2++)
    {
        if((*it2)->DoItWannaFire()==true)
        {
            _Bullets.push_back((*it2)->ReturnBullet(Holder));
            std::shared_ptr<Observer> ob (new Observer);
            _Observers.push_back(std::move(ob));
            _Bullets.back()->SetObserver((_Observers.back()));
        }
    }
}

int Interface::Increment_Observers_IteratorPosition()
{
    if(it1==_Observers.end())
        return -1;
    it1++;
        return 1;
}

GameMechanisms&& Interface::ReturnMechanismFromTheObserwver()
{

    GameMechanisms d=(*it1)->ReturnObserwation();
    if(d!=GameMechanisms::Empty)
    return std::move(d);
    GameMechanisms a=GameMechanisms::Empty;
    return std::move(a);
}

void Interface::StartSearchingForMechanics()
{
    std::cout<<_Observers.size()<<std::endl;
    it1=_Observers.begin();
}

void Interface::TakeBackObservator(std::vector<std::shared_ptr<Observer>>&& obserwastorzy )
{
    _Observers=std::move(obserwastorzy);
}

std::vector<std::shared_ptr<Observer>>& Interface::LookForObservations()
{
    return _Observers;
}

void Interface::DetectBullets()
{
    Collision pozycja;

    if(_Bullets.empty()==false)
    {
        it2=_Bullets.begin();
        while(it2!=_Bullets.end())
        {
            pozycja=(*it2)->DoTheyCover(*_Hero);
            if(pozycja.typ==ObjectTypes::Hero)
            {
                (*it2)->react(pozycja);
                if(it2==_Bullets.end())
                {
                    _Bullets.erase(it2);
                    break;
                }
                else
                    it2=_Bullets.erase(it2);
            }
            else
                it2++;
        }

        it2=_Bullets.begin();
        while(it2!=_Bullets.end())
        {
            bool a=0;
            for(it3=_FirstPlan.begin(); it3!=_FirstPlan.end(); it3++)
            {
                pozycja=(*it2)->DoTheyCover(**it3);
                if (pozycja.typ!=ObjectTypes::None)
                {
                    (*it2)->react(pozycja);
                    if(it2!=_Bullets.end())
                        it2=_Bullets.erase(it2);
                    else
                        _Bullets.erase(it2);
                    a=1;
                    break;
                }
            }
            if(a==0)
                it2++;
        }
    }
}

void Interface::DetectFindings()
{
    Collision pozycja;

    if(_Findings.empty()==false)
    {
        it2=_Findings.begin();
        while(it2!=_Findings.end())
        {
            pozycja=(*it2)->DoTheyCover(*_Hero);
            if(pozycja.typ==ObjectTypes::Hero)
            {
                (*it2)->react(pozycja);
                if(it2==_Findings.end())
                {
                    _Findings.erase(it2);
                }
                else
                    it2=_Findings.erase(it2);
            }
            else
                it2++;
        }
    }
}

void Interface::MustBeDetectedFirst()
{
    Collision pozycja;
    pozycja.typ=ObjectTypes::None;
    _Hero->react(pozycja);
}

void Interface::DetectSpecialPoints()
{
    Collision pozycja;
    for(it3=_SpecialPoints.begin(); it3!=_SpecialPoints.end(); it3++)
    {
    pozycja=(*it3)->DoTheyCover(*_Hero);
    if(pozycja.typ==ObjectTypes::Hero)
    {
        (*it3)->react(pozycja);
    }
    }
}
void Interface::DetectFirstPlan()
{
    Collision pozycja;
    for(it3=_FirstPlan.begin(); it3!=_FirstPlan.end(); it3++)
    {
        pozycja=_Hero->DoTheyCover(**it3);
        if(pozycja.typ==ObjectTypes::GroundFloor)
        {
            _Hero->react(pozycja);
        }
        else if(pozycja.typ==ObjectTypes::Platforma)
        {
            _Hero->react(pozycja);
            if(_Hero->ConnectionToMove())
                _Hero->SetDependent(*it3);
        }
        else if(pozycja.typ==ObjectTypes::End)
        {
            _Hero->react(pozycja);
        }
    }
}
void Interface::DetectMonsters()
{
    Collision pozycja;
    for(it2=_Monsters.begin(); it2!=_Monsters.end(); it2++)
    {
        pozycja=(*it2)->DoTheyCover(*_Hero);
        if(pozycja.typ==ObjectTypes::Hero)
            (*it2)->react(pozycja);
    }

}

void Interface::DetectCollisions()
{
    MustBeDetectedFirst();
    DetectFirstPlan();
    DetectSpecialPoints();
    DetectFindings();
    DetectMonsters();
    DetectBullets();

}

void Interface::DeleteNoNeededObservators()
{
    it1=_Observers.begin();
    while(it1!=_Observers.end())
    {
        if((*it1)->IsItSenseToExist())
        {
            it1++;
        }
        else
        {
            if(it1!=_Observers.end())
            {
                it1=_Observers.erase(it1);
            }
            else
            {
                _Observers.erase(it1);
                break;
            }

        }
    }
}

void Interface::DistributeCommands(CommandQueue& Orders, sf::Time& dt)
{
    sf::Vector2f w {0,0};
    while(Orders.IsEmpty()==0)
    {
        command bufor=Orders.pop();
        bufor.GetAFunction()(*_Hero,dt,w);
    }
}

void Interface::update()
{
    for(it2=_SecondPlan.begin(); it2!=_SecondPlan.end(); it2++)
        (*it2)->update();
    for(it3=_FirstPlan.begin(); it3!=_FirstPlan.end(); it3++)
        (*it3)->update();
    for(it3=_SpecialPoints.begin(); it3!=_SpecialPoints.end(); it3++)
        (*it3)->update();
    for(it2=_Findings.begin(); it2!=_Findings.end(); it2++)
        (*it2)->update();
    for(it2=_Monsters.begin(); it2!=_Monsters.end(); it2++)
        (*it2)->update();
    for(it2=_Bullets.begin(); it2!=_Bullets.end(); it2++)
        (*it2)->update();
    _Hero->update();
}

void Interface::AutomaticMove(sf::Time& dt)
{
    for(it2=_SecondPlan.begin(); it2!=_SecondPlan.end(); it2++)
        (*it2)->AutomaticMove(dt);
    for(it3=_FirstPlan.begin(); it3!=_FirstPlan.end(); it3++)
        (*it3)->AutomaticMove(dt);
    for(it3=_SpecialPoints.begin(); it3!=_SpecialPoints.end(); it3++)
        (*it3)->AutomaticMove(dt);
    for(it2=_Findings.begin(); it2!=_Findings.end(); it2++)
        (*it2)->AutomaticMove(dt);
    for(it2=_Monsters.begin(); it2!=_Monsters.end(); it2++)
        (*it2)->AutomaticMove(dt);
    for(it2=_Bullets.begin(); it2!=_Bullets.end(); it2++)
        (*it2)->AutomaticMove(dt);
    _Hero->AutomaticMove(dt);
}

void Interface::draw(sf::RenderWindow& appwindow)
{
    for(it2=_SecondPlan.begin(); it2!=_SecondPlan.end(); it2++)
        (*it2)->draw(appwindow);
    for(it3=_FirstPlan.begin(); it3!=_FirstPlan.end(); it3++)
        (*it3)->draw(appwindow);
    for(it3=_SpecialPoints.begin(); it3!=_SpecialPoints.end(); it3++)
        (*it3)->draw(appwindow);
    for(it2=_Findings.begin(); it2!=_Findings.end(); it2++)
        (*it2)->draw(appwindow);
    for(it2=_Monsters.begin(); it2!=_Monsters.end(); it2++)
        (*it2)->draw(appwindow);
    for(it2=_Bullets.begin(); it2!=_Bullets.end(); it2++)
        (*it2)->draw(appwindow);
    _Hero->draw(appwindow);
}
