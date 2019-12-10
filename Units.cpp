#include <iostream>
#include <functional>
#include <utility>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Physics.hpp"
#include "Units.hpp"

////////////////// Entity

void Entity::SetScale(sf::Vector2f& skala)
{
    sprite.setScale(skala);
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

