#include <iostream>
#include <SFML/Graphics.hpp>
#include "Utilities.hpp"
#include "Units.hpp"
#include <functional>
#include "Commands.hpp"
#include <queue>

bool CommandQueue::IsEmpty()
{
    return kolejka.empty();
}

command CommandQueue::pop()
{
    command bufor=kolejka.front();
    kolejka.pop();
    return bufor;
}

void CommandQueue::push(const command& komenda)
{
    kolejka.push(komenda);
}

std::function<void (Entity&, sf::Time&,sf::Vector2f&)>& command::GetAFunction()
{
    return akcja;
}

ObjectTypes& command::GetObjectTypes()
{
return przyporzadkowanie;
}

command::command(std::function<void (Entity&, sf::Time&,sf::Vector2f&)>& funkcja, ObjectTypes && typobiektu)
{
    przyporzadkowanie=std::move(typobiektu);
    //akcja=std::move(funkcja);
    akcja=funkcja;
}

command::command(std::function<void (Entity&, sf::Time&,sf::Vector2f&)>&& funkcja, ObjectTypes && typobiektu)
{
    przyporzadkowanie=std::move(typobiektu);
    akcja=std::move(funkcja);
}
