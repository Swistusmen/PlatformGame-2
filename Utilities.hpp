#ifndef UTILITIES_HPP_INCLUDED
#define UTILITIES_HPP_INCLUDED



#endif // UTILITIES_HPP_INCLUDED
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <utility>
#include <map>
#pragma once

#define SZEROKOSCOKNA 2800
#define WYSOKOSCOKNA 1400
#define SKOK_GR 400
#define POZIOM_GRACZ 25
#define PION_GRACZ 30

enum GameStates{Play, Closing,Uninitialized,Pause,Winner};

enum HumanStates {Stand, Fall, Jump};

enum ObjectTypes {Hero, GroundFloor,End,None,Bomba,Platforma,Dolar,BWEnemy,BFEnemy};

enum Directions {North,East,South, West};

enum Dimension  {Horizontal,Vertical };

enum GameMechanisms {GetACoin, Win,Empty, WalkiIntoEnemy};

struct Collision{
sf::Vector2f nachodzenie;
ObjectTypes typ;

Collision(){typ=ObjectTypes::None;}
Collision(sf::Vector2f& a,ObjectTypes b):nachodzenie(a),typ(b){};
};

class TextureHolder{
public:
    void LoadFromFile(ObjectTypes,std::string&&);
    sf::Texture& GetTexture(ObjectTypes);
private:
    std::map<ObjectTypes, std::unique_ptr<sf::Texture>> mapka;
};

class Observer{
public:
    void SawSomething (ObjectTypes ,ObjectTypes);
    GameMechanisms ReturnObserwation(){Detection=0;return stan;};
    bool WasSomethingObserved(){return Detection;};
    bool IsItSenseToExist(){return SenseOfLiving;}
    void MarkMeAsNoNedeed(){SenseOfLiving=false;}
    Observer(){SenseOfLiving=true;stan=GameMechanisms::Empty;}
private:
    bool Detection=0;
    bool SenseOfLiving=true;
    GameMechanisms stan;
};
