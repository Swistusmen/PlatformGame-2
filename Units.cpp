#include <iostream>
#include <functional>
#include <utility>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Physics.hpp"
#include "Units.hpp"
/*
class BasicFlyingEnemy:public Entity, public CellularAutomata
{
public:
    void update() override;
    void MoveEntity(sf::Vector2f& ,sf::Time& ,sf::Vector2f&w){};
    void react(Collision& ) override;
    void AutomaticMove(sf::Time&) override;
    void SetDependent(std::shared_ptr<Entity> &d);

    BasicFlyingEnemy(ObjectTypes &&, sf::Vector2f &&,sf::Texture& ,sf::Vector2f&&= sf::Vector2f(1,1));

private:
sf::Vector2f velocity {100,100};
};
*/

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

BasicFlyingEnemy::BasicFlyingEnemy(ObjectTypes &&a, sf::Vector2f &&b,sf::Texture& c,sf::Vector2f&& d):ActiveEntity(std::move(a),std::move(b),c,std::move(d)),CellularAutomata(velocity)
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

BasicWalkingEnemy::BasicWalkingEnemy(ObjectTypes &&a, sf::Vector2f &&b,sf::Texture& c,sf::Vector2f&& d):ActiveEntity(std::move(a),std::move(b),c,std::move(d)),CellularAutomata(velocity)
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

Coin::Coin(ObjectTypes && a, sf::Vector2f && b,sf::Texture& c,const std::shared_ptr<Entity>& wskaznik,sf::Vector2f&& d):PasiveEntity(std::move(a),std::move(b),c,std::move(d))
{
    stala=std::move(b);
    stala.x=-stala.x;
    stala.y=-stala.y;
SetDependent(wskaznik);
if(wskaznik!=nullptr)
{
placement.x=wskaznik->ReturnPosition().x+stala.x;
placement.y=wskaznik->ReturnPosition().y+stala.y;
}
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

Platform::Platform(ObjectTypes && a, sf::Vector2f && b,sf::Texture& c,sf::Vector2f&& d):PasiveEntity(std::move(a),std::move(b),c,std::move(d)),CellularAutomata(velocity)
{
    SetRange(sf::Vector2f{500,100},ReturnPosition());
}

Platform::Platform(ObjectTypes && a, sf::Vector2f && b, sf::IntRect && c,sf::Texture& d,sf::Vector2f&& e):PasiveEntity(std::move(a),std::move(b),std::move(c),d,std::move(e)),CellularAutomata(velocity)
{
    SetRange(sf::Vector2f{500,100},ReturnPosition());
}


////////////////////////////// BOMBA

/*Bomb::~Bomb()
{
    std::cout<<"Destruktor\n";

}*/

void Bomb::AutomaticMove(sf::Time& dt)
{
    int k=dt.asSeconds()*velocity.y;
    placement.y+=k;
}

Bomb::Bomb(ObjectTypes && a, sf::Vector2f && b,sf::Texture& c,sf::Vector2f&& d):ActiveEntity(std::move(a),std::move(b),c,std::move(d)){}

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

EndGate::EndGate(ObjectTypes && a, sf::Vector2f &&b,sf::Texture& c,sf::Vector2f&& d ):PasiveEntity(std::move(a),std::move(b),c,std::move(d))
{
    DoIWantAnObserwer=true;
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

Enemy::Enemy(ObjectTypes && a, sf::Vector2f && b,sf::Texture& c,sf::Vector2f&& d):ActiveEntity(std::move(a),std::move(b),c,std::move(d)),CellularAutomata(velocity)
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

Player::Player(ObjectTypes && a, sf::Vector2f && b,sf::Texture& c,sf::Vector2f&& d):ActiveEntity(std::move(a),std::move(b),c,std::move(d))
{
    sprite.setTextureRect(sf::IntRect(0,0,100,100));
velocity.x=POZIOM_GRACZ;
velocity.y=PION_GRACZ;
}

////////////////////////////// GroundFloor
void gf::GroundFloor::update()
{
    sprite.setPosition(placement);
}

void gf::GroundFloor::AutomaticMove(sf::Time& a)
{
}

gf::GroundFloor::GroundFloor(ObjectTypes && a, sf::Vector2f && b,sf::Texture& c,sf::Vector2f&& d):PasiveEntity(std::move(a),std::move(b),c,std::move(d)){};

gf::GroundFloor::GroundFloor(ObjectTypes && a, sf::Vector2f && b, sf::IntRect && c,sf::Texture& d,sf::Vector2f&& e):PasiveEntity(std::move(a),std::move(b),std::move(c),d,std::move(e))
{
d.setRepeated(true);
};

/////////////////////// ActiveEntity

ActiveEntity::ActiveEntity(ObjectTypes && a, sf::Vector2f && b,sf::Texture& c,sf::Vector2f&& d):Entity(std::move(a),std::move(b))
{
    tekstura=c;
    sprite.setTexture(tekstura);
    //sprite.setScale(std::move(d));
}


///////////////////////// Pasive Entity


void PasiveEntity::MoveEntity(sf::Vector2f& a,sf::Time& b, sf::Vector2f& c)
{
    placement+=a;
}

PasiveEntity::PasiveEntity(ObjectTypes && a, sf::Vector2f && b,sf::IntRect && c,sf::Texture& d,sf::Vector2f&& e):Entity(std::move(a),std::move(b))
{
    tekstura=d;
    sprite.setTexture(tekstura);
    sprite.setScale(std::move(e));
    sprite.setTextureRect(sf::IntRect(std::move(c)));
    tekstura.setRepeated(true);
}

PasiveEntity::PasiveEntity(ObjectTypes && a, sf::Vector2f && b,sf::Texture& c,sf::Vector2f&& d):Entity(std::move(a),std::move(b))
{
    tekstura=c;
    sprite.setTexture(tekstura);
    sprite.setScale(std::move(d));
}


////////////////// Entity

std::unique_ptr<Entity> Entity::ReturnBullet(TextureHolder& a)
{
    sf::Vector2f polozenie=placement;
    std::unique_ptr<Entity> tet(new Bomb(ObjectTypes::Bomba,std::move(polozenie),a.GetTexture(ObjectTypes::Bomba)));
    return tet;
}

void Entity::MoveEntity(sf::Vector2f& przemieszczenie)
{
    placement.x=przemieszczenie.x;

}

Entity::~Entity()
{
    obserwator=nullptr;
    dependent=nullptr;
}


void Entity::draw(sf::RenderWindow& appwindow)
{
    appwindow.draw(sprite);
}

Entity::Entity(ObjectTypes && a, sf::Vector2f && b)
{
    typ=std::move(a);
    placement=std::move(b);
    sprite.setPosition(placement);
}

ObjectTypes& Entity::RetTypeOfObject()
{
    return typ;
}

const sf::Vector2f& Entity::ReturnCurrentPlacement()
{
    return sprite.getPosition();
}

const sf::FloatRect Entity::ReturnTheShape()
{
    return sprite.getGlobalBounds();
}

Collision Entity::DoTheyCover(Entity& a)
{
    sf::FloatRect obcy=a.ReturnTheShape();
    sf::FloatRect rodzimy=this->ReturnTheShape();
    sf::Vector2f wektorek(0,0);
    ObjectTypes CoToZaObiekt=ObjectTypes::None;
    rodzimy.height+=1;
    obcy.top-=10;
    if(rodzimy.intersects(obcy)==1)
    {
        rodzimy.height-=1;
        obcy.top+=10;
        //std::cout<<"kolizja\n";
        int Ol=obcy.left;
        int Ot=obcy.top;
        int Or=obcy.width+Ol;
        int Ob=obcy.height+Ot+1;
        int Rl=rodzimy.left;
        int Rt=rodzimy.top;
        int Rr=rodzimy.width+Rl;
        int Rb=rodzimy.height+Rt;
        //warunki ktore dodajemy sa ujemne dlatego ponizej znaki musza byc na odwrot!
        if((Rb-Ob<0)&&(Rt<Ot))//nachodzenie z gory
        {
            //std::cout<<" Nachodzenie z gory\n";
            wektorek.y+=Ot-Rb;// zmiana ob na ot
        }
        else if((Ot-Rb<0)&&(Rt<Ob))//nachodzenie z dolu
        {
            //std::cout<<" Nachodzenie z dolu\n";
            wektorek.y-=(Rt-Ob);
        }
        else if((Or-Rl>0)&&(Rl>Ol))//nachodzenie z lewej strony  ((Ol-Rr<0)&&(Rl>Ol))
        {
            //std::cout<<" Nachodzenie z lewej\n";
            wektorek.x+=Rl-Or;
            wektorek.y=-1;
        }
        else if((Rr-Ol>0)&&(Ol>Rl))//nachodzenie z prawej storny
        {
            //std::cout<<" Nachodzenie z prawej\n";
            wektorek.x-=Rr-Ol;
            wektorek.y=-1;
        }

        CoToZaObiekt=a.RetTypeOfObject();

    }
    Collision kolizja (wektorek,CoToZaObiekt);
    return kolizja;
}

