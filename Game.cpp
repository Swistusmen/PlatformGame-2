#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Units.hpp"
#include "Utilities.hpp"
#include "Commands.hpp"
#include "Game.hpp"
#include <typeinfo>

Game::Game():interfejs(Holder)
{
    stanGry=GameStates::Play;
}

void Game::DistributeTheCommands(sf::Time & a)
{
    interfejs.AutomaticMove(a);
    interfejs.DetectCollisions();

    interfejs.DistributeCommands(Kontroler.ReturnValidCommands(),a);
}

void Game::draw()
{
    interfejs.RespNewObjects(Holder);
    interfejs.draw(appwindow);
    appwindow.display();
    appwindow.clear();
}

void Game::ManageGameMechanics(GameMechanisms& d)
{
    switch(d)
             {
             case GameMechanisms::Win:
                {
                    std::cout<<"Win\n";
                    stanGry=GameStates::Winner;
                }break;
             case GameMechanisms::GetACoin:
                {
                    std::cout<<"Zdobyto pieniazek\n";
                }break;
            case GameMechanisms::WalkiIntoEnemy:
                {
                    std::cout<<"Otrzymano obrazenia\n";
                }break;
            case GameMechanisms::Empty:
                {

                }break;
             }
}

void Game::update()
{

    interfejs.StartSearchingForMechanics(); //ustaw na 0
    while(interfejs.IsEnd())
    {

        GameMechanisms d=interfejs.ReturnMechanismFromTheObserwver();// zwroc wartosc nie sprwadzaj niczego
        ManageGameMechanics(d);

        if(interfejs.Increment_Observers_IteratorPosition()==-1) //jesli nie jest koncowym elementem inkrementuj
        {
            break;
        }
    }

    interfejs.DeleteNoNeededObservators();
    interfejs.update();
}


void Game::Run()
{
    appwindow.create(sf::VideoMode(SZEROKOSCOKNA,WYSOKOSCOKNA,32),"okno");
    sf::Time TimeSinceLastUpdate;
    sf::Clock timer;
    sf::Time DeltaTime=sf::seconds(1.f/20.f);
    bool c=0;
    while(appwindow.isOpen())
    {

            HandleEvent();


            if(stanGry==GameStates::Pause){
            TimeSinceLastUpdate+=timer.restart();
            TimeSinceLastUpdate=TimeSinceLastUpdate%DeltaTime;
            }
            if(stanGry==GameStates::Play){
            TimeSinceLastUpdate+=timer.restart();
            if(TimeSinceLastUpdate>=DeltaTime)
            {
            ProcessInput();

            DistributeTheCommands(TimeSinceLastUpdate);

            update();
            draw();

            TimeSinceLastUpdate-=DeltaTime;
            }
        }
        ProcessEvent();
    }
}

void Game::ProcessInput()
{
    Kontroler.ManageControl();
}

void Game::ProcessEvent()
{
    if((stanGry==GameStates::Closing)||(stanGry==GameStates::Winner))
    {
        appwindow.close();
        exit(EXIT_SUCCESS);
    }
}

void Game::HandleEvent()
{
    sf::Event zdarzenie;
   while(appwindow.pollEvent(zdarzenie))
   {
       switch (zdarzenie.type)
       {
           case sf::Event::Closed:
           {
               stanGry=GameStates::Closing;
           }break;
        default:{
        }break;

       }
   }
   if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
   {
       if(stanGry==GameStates::Play)
        stanGry=GameStates::Pause;
       else if(stanGry==GameStates::Pause)
        stanGry=GameStates::Play;
   }
}
