#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <utility>
#include <map>
#include "Utilities.hpp"

/////////////////////////// OSERWATOR

void Observer::SawSomething(ObjectTypes moj,ObjectTypes obcy)
{
    if((moj==ObjectTypes::End)&&(obcy==ObjectTypes::Hero))
    {
        Detection=1;
        stan=GameMechanisms::Win;
    }
    if((moj==ObjectTypes::Dolar)&&(obcy==ObjectTypes::Hero))
    {
        Detection=1;
        stan=GameMechanisms::GetACoin;
    }
    if(((moj==ObjectTypes::BWEnemy)||(moj==ObjectTypes::BFEnemy)||(moj==ObjectTypes::Bomba))&&(obcy==ObjectTypes::Hero))
    {
        Detection=1;
        stan=GameMechanisms::WalkiIntoEnemy;
    }
    //std::cout<<WasSomethingObserved()<<"g\n";
}

////////////// Texture

TextureHolder::TextureHolder()
{
    LoadFromFile(ObjectTypes::GroundFloor,"dirt.jpg");
    LoadFromFile(ObjectTypes::Hero,"player1.jpg");
    LoadFromFile(ObjectTypes::End,"endingPoint.jpg");
    LoadFromFile(ObjectTypes::Bomba,"bomb.jpg");
    LoadFromFile(ObjectTypes::Platforma,"steel.jpg");
    LoadFromFile(ObjectTypes::Dolar,"coin.jpg");
    LoadFromFile(ObjectTypes::BFEnemy,"BFEnemy.jpg");
    LoadFromFile(ObjectTypes::BWEnemy,"BWEnemy.jpg");
}

void TextureHolder::LoadFromFile(ObjectTypes przyporzadkowanie,std::string&& pathname)
{
    std::unique_ptr<sf::Texture> wsk (new sf::Texture);
    if(!wsk->loadFromFile(pathname))
    {
        std::cerr<<"Blad we wczytywaniu tekstury z pliku\n";
        exit(EXIT_FAILURE);
    }
    mapka.insert(std::make_pair(przyporzadkowanie,std::move(wsk)));
}

sf::Texture& TextureHolder::GetTexture(ObjectTypes rodzaj)
{
    auto znalezione=mapka.find(rodzaj);
    if(znalezione==mapka.end())
    {
        std::cerr<<"Nie znaleziono tekstury "<<rodzaj<<std::endl;
        exit(EXIT_FAILURE);
    }
    return *znalezione->second;
}
