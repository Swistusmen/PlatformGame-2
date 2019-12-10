#ifndef LOADER_HPP_INCLUDED
#define LOADER_HPP_INCLUDED



#endif // LOADER_HPP_INCLUDED
#include <iostream>
#include <utility>
#include <memory>
#include "Utilities.hpp"
#include "Units.hpp"
#include "SFML/Graphics.hpp"
#include "ActiveUnits.hpp"
#include "PassiveUnits.hpp"
#include "Batch.hpp"
#pragma once


class LoadingMachine
{
public:
    std::unique_ptr<Batch>&& ReturnBatch();
    void LoadFromFile(std::string&, TextureHolder&);
private:
    void Parse(std::string& , std::vector<std::string>&);//parsuje
private:
    std::unique_ptr<Batch> batch=nullptr;
};
