#include <iostream>
#include <functional>
#include <utility>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Physics.hpp"
#include <memory>
#include "Units.hpp"
#include "ActiveUnits.hpp"

void BasicFlyingEnemy::AutomaticMove(sf::Time& dt)
{
    if(!ConnectionToMove())
    placement=RealizeTheMove(dt);
    else
    {

    }

    if(licznik==100){
        WannaFire=1;
        licznik=0;
    }
    else
    {
        WannaFire=0;
        licznik++;
    }
}

void BasicFlyingEnemy::update()
{
    sprite.setPosition(placement);
}

BasicFlyingEnemy::BasicFlyingEnemy(ObjectTypes &&a, sf::Vector2f &&b,sf::Texture& c):ActiveEntity(std::move(a),std::move(b),c),CellularAutomata(velocity)
{
    SetRange(sf::Vector2f{600,300},ReturnPosition());
}

void BasicFlyingEnemy::react(Collision& kolizja)
{
    if(obserwator!=nullptr)
    obserwator->SawSomething(this->RetTypeOfObject(),kolizja.typ);
}


///////////////////////////////////// BasicWalkingEnemy
void BasicWalkingEnemy::SetDependent(std::shared_ptr<Entity> &d)
{
    Entity::SetDependent(d);
    placement=d->ReturnPosition();
}

BasicWalkingEnemy::BasicWalkingEnemy(ObjectTypes &&a, sf::Vector2f &&b,sf::Texture& c):ActiveEntity(std::move(a),std::move(b),c),CellularAutomata(velocity)
{
    SetRange(sf::Vector2f{400,0},ReturnPosition());
}

void BasicWalkingEnemy::react(Collision& kolizja)
{
    if(obserwator!=nullptr)
    obserwator->SawSomething(this->RetTypeOfObject(),kolizja.typ);
}

void BasicWalkingEnemy::AutomaticMove(sf::Time& dt)
{
    if(dependent!=nullptr)
    {
    //sf::Vector2f bufor=
    //std::cout<<placement.x<<" "<<placement.y<<std::endl;
    //placement-=dependent->ReturnPosition();
    //std::cout<<placement.x<<" "<<placement.y<<std::endl;
    dt=dt;
    sf::Vector2f buf=RealizeTheMoveAndReturnDelta(dt);
    placement=dependent->ReturnPosition();
    //std::cout<<dependent->ReturnPosition().x<<std::endl;
    placement.y-=100;
    std::cout<<placement.x<<std::endl;
   // buf.x+=200;
    placement+=buf;
    std::cout<<placement.x<<std::endl;
    //placement+=dependent->ReturnPosition();
     //buf trzyma przemieszczenie jakiego dokonalismy z poprzedniego do tego obiegu petli
     //bufor trzyma poprzednia czysta pozycje petli
    }

    //if(!ConnectionToMove())
    //else
    else{
    sf::Vector2f buf=RealizeTheMoveAndReturnDelta(dt);
    placement+=buf;
    }
    //std::cout<<"b\n";
    //placement=RealizeTheMove(dt);//zwraca mi pozycje po wykonaniu ruchu
}

void BasicWalkingEnemy::update()
{
    sprite.setPosition(placement);
}

////////////////////////////// BOMBA

void Bomb::AutomaticMove(sf::Time& dt)
{
    int k=dt.asSeconds()*velocity.y;
    placement.y+=k;
}

Bomb::Bomb(ObjectTypes && a, sf::Vector2f && b,sf::Texture& c):ActiveEntity(std::move(a),std::move(b),c){}

void Bomb::react(Collision& kolizja)
{
    if(kolizja.typ!=ObjectTypes::None)
    {
        //musi sie zniszczyc
        std::cout<<"Niszczenie\n";
        if(obserwator!=nullptr)
        {
        obserwator->MarkMeAsNoNedeed();
        obserwator->SawSomething(typ,kolizja.typ);
        FreeObserver();
        }
    }
}

void Bomb::update()
{
    sprite.setPosition(placement);
}

///////////////////////////// Enemy
void Enemy::MoveEntity(sf::Vector2f& a,sf::Time& b, sf::Vector2f& w)
{

}

void Enemy::react(Collision& )
{

}

void Enemy::AutomaticMove(sf::Time& dt)
{
    if(!ConnectionToMove())
    placement=RealizeTheMove(dt);
    else
    {

    }
}

void Enemy::update()
{
    sprite.setPosition(placement);
}

Enemy::Enemy(ObjectTypes && a, sf::Vector2f && b,sf::Texture& c):ActiveEntity(std::move(a),std::move(b),c),CellularAutomata(velocity)
                {
                   SetRange(sf::Vector2f{400,400},ReturnPosition());
                }

//////////////////////////////////// Player
void Player::AutomaticMove( sf::Time& dt)
{
    //

        if(ConnectionToMove())
    {
        placement.x=dependent->ReturnPosition().x+wzlgedem.x;
    }


    //

    placement=RealizeTheFall(placement,velocity,dt);
}

void Player::react(Collision& a)
{
    //ChangeState(HumanStates::Stand);
    switch(a.typ)
    {
        case ObjectTypes::Platforma:
        case ObjectTypes::GroundFloor :
            {
        placement.x+=a.nachodzenie.x;
        std::cout<<a.nachodzenie.y<<std::endl;
        placement.y+=a.nachodzenie.y;

        if(a.nachodzenie.y<=0)
        {
        //std::cout<<"stanie\n";
        ChangeState(HumanStates::Stand);
        }
        if(a.nachodzenie.y>0)
        ChangeState(HumanStates::Fall);
        }break;
        case ObjectTypes::None:
            {
                //std::cout<<"Spadanie\n";
                if((ReturnHumanState()!=HumanStates::Jump)&&(!ConnectionToMove()))
                ChangeState(HumanStates::Fall);
            }break;
        default:{
        }break;
    }
    if(a.typ==ObjectTypes::Platforma) isConnectedToMove=1;
    else isConnectedToMove=0;
}

void Player::update()
{
     sprite.setPosition(placement);
}

//1. wspolrzedne ruchu, 2.czas, 3. ruch wzglêdny
void Player::MoveEntity(sf::Vector2f& a,sf::Time& b, sf::Vector2f& w)
{
    //if(w!=sf::Vector2f(0,0))
        //placement.x+=w.x;
    if((ReturnHumanState()==HumanStates::Fall)||(ReturnHumanState()==HumanStates::Jump)){
       isConnectedToMove=0;
       FreeDependent();
       wzlgedem.x=0;
    }


    bool isZero;
    a.y!=0?isZero=false:isZero=true;
    if(ReturnHumanState()==HumanStates::Stand)
    placement=RealizeTheMove(placement,velocity,isZero,b);

    if(a.x!=0){
            int c=velocity.x*15;
        int k=c*b.asSeconds()*a.x;
        //dodane
        if(ConnectionToMove())
    {
        wzlgedem.x+=k;
        placement.x=dependent->ReturnPosition().x+wzlgedem.x;
    }
    else//dotad
        placement.x+=k;

        if(placement.x<0)
            placement.x=0;
        if(placement.x>SZEROKOSCOKNA-101)
            placement.x=SZEROKOSCOKNA-100;
    }
}

Player::Player(ObjectTypes && a, sf::Vector2f && b,sf::Texture& c):ActiveEntity(std::move(a),std::move(b),c)
{
    sprite.setTextureRect(sf::IntRect(0,0,100,100));
velocity.x=POZIOM_GRACZ;
velocity.y=PION_GRACZ;
}

/////////////////////// ActiveEntity

ActiveEntity::ActiveEntity(ObjectTypes && a, sf::Vector2f && b,sf::Texture& c):Entity(std::move(a),std::move(b))
{
    tekstura=c;
    sprite.setTexture(tekstura);
}

std::unique_ptr<Entity> ActiveEntity::ReturnBullet(TextureHolder& a)
{
    sf::Vector2f polozenie=placement;
    std::unique_ptr<Entity> tet(new Bomb(ObjectTypes::Bomba,std::move(polozenie),a.GetTexture(ObjectTypes::Bomba)));
    return tet;
}

