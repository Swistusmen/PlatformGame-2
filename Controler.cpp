#include <iostream>
#include <memory>
#include "Commands.hpp"
#include "Units.hpp"
#include "Utilities.hpp"
#include "Controler.hpp"
/*
class CommandHolder
{
public:
  command ReturnCommand(Letter& );
private:
    std::map<Letters, command> Commands;
};

class Controler
{
public:
    ManageControl();
    CommandQueue& ReturnValidCommands();
private:
    CommandHolder Holder;
    CommandQueue Queue;
};
*/

CommandQueue& Controler::ReturnValidCommands()
{
    return Queue;
}

void Controler::ManageControl()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        Queue.push(Holder.ReturnCommand(Letters::A));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        Queue.push(Holder.ReturnCommand(Letters::D));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        Queue.push(Holder.ReturnCommand(Letters::SPACE));
    }
}

command CommandHolder::ReturnCommand(Letters&& literka)
{
    auto znalezione=Commands.find(literka);
    if(znalezione==Commands.end())
    {
        std::cerr<<"Nie znaleziono tekstury "<<literka<<std::endl;
        exit(EXIT_FAILURE);
    }
    return znalezione->second;
}

CommandHolder::CommandHolder()
{
    auto f=[](Entity& obiekt, sf::Time& a,sf::Vector2f& b){sf::Vector2f wektorek=sf::Vector2f(-1,0);obiekt.MoveEntity(wektorek,a,b);};
    command bufor {f,ObjectTypes::Hero};
    Commands.insert(std::make_pair(Letters::A,bufor));

    auto g=[](Entity& obiekt, sf::Time& a,sf::Vector2f& b){sf::Vector2f wektorek= sf::Vector2f(1,0);obiekt.MoveEntity(wektorek,a,b);};
    Commands.insert(std::make_pair(Letters::D,command({g,ObjectTypes::Hero})));

    auto h=[](Entity& obiekt, sf::Time& a,sf::Vector2f& b){sf::Vector2f wektorek= sf::Vector2f(0,-1);obiekt.MoveEntity(wektorek,a,b);};
    Commands.insert(std::make_pair(Letters::SPACE,command({h,ObjectTypes::Hero})));
}
