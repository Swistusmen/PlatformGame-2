#include <iostream>
#include <utility>
#include <memory>
#include "Utilities.hpp"
#include "Units.hpp"
#include "SFML/Graphics.hpp"
#include "ActiveUnits.hpp"
#include "PassiveUnits.hpp"
#include "Batch.hpp"
#include "Loader.hpp"
#include <fstream>

void LoadingMachine::LoadFromFile(std::string& filename,TextureHolder& Holder)
{
    fstream plik;
    plik.open(filename,"r");
    if(plik.good())
    {

    }
}

std::unique_ptr<Batch>&& LoadingMachine::ReturnBatch()
{
    return std::move(batch);
}

/*
void parse(std::string& napis,std::vector<std::string>& wek)
{
    std::string bufor;
    std::string::iterator it;
    it=napis.begin();
    do
    {
        std::cout<<*it<<std::endl;

        if((*it)!=' ')
        {
            bufor+=*it;
        }
        else
        {
          wek.push_back(bufor);
          bufor="";
        }
        it++;
    }while(it!=napis.end());
    wek.push_back(bufor);
}
*/
