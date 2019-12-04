#ifndef CONTROLER_HPP_INCLUDED
#define CONTROLER_HPP_INCLUDED



#endif // CONTROLER_HPP_INCLUDED
#include <iostream>
#include <memory>
#include "Commands.hpp"
#include "Units.hpp"
#include "Utilities.hpp"

class CommandHolder
{
public:
  command ReturnCommand(Letters&& );
  CommandHolder();
private:
    std::map<Letters, command> Commands;
};

class Controler
{
public:
    void ManageControl();
    CommandQueue& ReturnValidCommands();
private:
    CommandHolder Holder;
    CommandQueue Queue;
};
