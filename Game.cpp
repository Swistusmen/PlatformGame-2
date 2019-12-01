#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Units.hpp"
#include "Utilities.hpp"
#include "Commands.hpp"
#include "Game.hpp"
#include <typeinfo>

//zaimplementowanie poziomego przeciwnika

//do zrobienia w poziomym preciwniku
//- zaimplementowanie zaleznosci od platformy

//w jaki sposob uzywac pociskow?
//  pocisk musi miec dane obiektu go wysylajacego
//  pociskow moze byc wiele
//  musi byc mozliwosc odpalenia pocisku za pomoca komendy
// pierwszy pomysl- bullet manager jako zewnetrzny obiekt poza obiektami
//  ma referencje do wszystkich klas wysylajacych pociski- przeglada je sprawdzajac flagi
//  w razie czego pobiera dane obiektu i tworzy nowy pocisk
//drugi pomysl: niech kazdy obiekt ma swoj wektor pociskow- problem co gdy zgina?
// odpowiedz niech wtedy bedzie przekazywany obiekt


Game::Game()
{
    Holder.LoadFromFile(ObjectTypes::GroundFloor,"dirt.jpg");
    Holder.LoadFromFile(ObjectTypes::Hero,"player1.jpg");
    Holder.LoadFromFile(ObjectTypes::End,"endingPoint.jpg");
    Holder.LoadFromFile(ObjectTypes::Bomba,"bomb.jpg");
    Holder.LoadFromFile(ObjectTypes::Platforma,"steel.jpg");
    Holder.LoadFromFile(ObjectTypes::Dolar,"coin.jpg");
    Holder.LoadFromFile(ObjectTypes::BFEnemy,"BFEnemy.jpg");
    Holder.LoadFromFile(ObjectTypes::BWEnemy,"BWEnemy.jpg");

    std::unique_ptr<Entity> wsk(new Player(ObjectTypes::Hero,sf::Vector2f{2100,100},Holder.GetTexture(ObjectTypes::Hero)));
    Gracz=std::move(wsk);

    std::unique_ptr<Entity> wskk(new Enemy(ObjectTypes::Hero,sf::Vector2f{1500,500},Holder.GetTexture(ObjectTypes::Hero)));
    wrog=std::move(wskk);

    std::unique_ptr<Entity> ptr(new gf::GroundFloor(ObjectTypes::GroundFloor,sf::Vector2f(0,1300),sf::IntRect(0,1300,2800,100),Holder.GetTexture(ObjectTypes::GroundFloor)));
    ziemia=std::move(ptr);

    std::unique_ptr<Entity> platf(new gf::GroundFloor(ObjectTypes::GroundFloor,sf::Vector2f(1000,900),sf::IntRect(1000,900,300,100),Holder.GetTexture(ObjectTypes::GroundFloor)));
    ziemia_wyspa=std::move(platf);

    std::shared_ptr<Observer> obs (new Observer);
    obserwatorzy.push_back(std::move(obs));

    std::unique_ptr<Entity> ptrr(new EndGate(ObjectTypes::End,sf::Vector2f{2000,1200},Holder.GetTexture(ObjectTypes::End)));
    brama=std::move(ptrr);
    brama->SetObserver((obserwatorzy.back()));

    std::unique_ptr<Entity> te (new Platform(ObjectTypes::Platforma,sf::Vector2f(1800,800),sf::IntRect(1800,800,300,100),Holder.GetTexture(ObjectTypes::Platforma)));
    test=std::move(te);

    std::shared_ptr<Observer> obss (new Observer);
    obserwatorzy.push_back(std::move(obss));

    //std::unique_ptr<Entity> tet(new Bomb(ObjectTypes::Bomba,sf::Vector2f{1000,100},Holder.GetTexture(ObjectTypes::Bomba)));

    std::unique_ptr<Entity> tet(new Coin(ObjectTypes::Dolar,sf::Vector2f{-100,200},Holder.GetTexture(ObjectTypes::Dolar)));
    tet->SetDependent(test);
    tet->SetObserver(obserwatorzy.back());
    wektor.push_back(std::move(tet));
    //drugi pieniazek
    obss.reset(new Observer);
    obserwatorzy.push_back(obss);//nowe
    tet.reset(new Coin(ObjectTypes::Dolar,sf::Vector2f{100,1200},Holder.GetTexture(ObjectTypes::Dolar)));
    tet->SetObserver(obserwatorzy.back());
    wektor.push_back(std::move(tet));

    //potwory
    tet.reset(new BasicWalkingEnemy(ObjectTypes::BWEnemy,sf::Vector2f{600,1200},Holder.GetTexture(ObjectTypes::BWEnemy)));
    obss.reset(new Observer);
    //tet->SetDependent(test);
    obserwatorzy.push_back(obss);//nowe
    tet->SetObserver(obserwatorzy.back());
    potwory.push_back(std::move(tet));

    tet.reset(new BasicFlyingEnemy(ObjectTypes::BFEnemy,sf::Vector2f{1000,100},Holder.GetTexture(ObjectTypes::BFEnemy)));
    obss.reset(new Observer);
    obserwatorzy.push_back(obss);//nowe
    tet->SetObserver(obserwatorzy.back());
    potwory.push_back(std::move(tet));

    stanGry=GameStates::Play;
}

void Game::DistributeTheCommands(sf::Time & a)
{
    //if(!wektor.empty())
       // wektor.back()->AutomaticMove(a);
    for(it2=wektor.begin();it2!=wektor.end();it2++)
        (*it2)->AutomaticMove(a);

    for(it2=potwory.begin();it2!=potwory.end();it2++)
        (*it2)->AutomaticMove(a);

     for(it2=pociski.begin();it2!=pociski.end();it2++)
        (*it2)->AutomaticMove(a);



        test->AutomaticMove(a);
        Gracz->AutomaticMove(a);
        wrog->AutomaticMove(a);

        Collision pozycja;
    pozycja.typ=ObjectTypes::None;
    Gracz->react(pozycja);

    pozycja=Gracz->DoTheyCover(*ziemia);   //etap wykrycia kolizji

    if(pozycja.typ==ObjectTypes::GroundFloor)       //etap reakcji na kolizje
    {
        Gracz->react(pozycja);
    }


    pozycja=Gracz->DoTheyCover(*ziemia_wyspa);
    if(pozycja.typ==ObjectTypes::GroundFloor)       //etap reakcji na kolizje
    {
        Gracz->react(pozycja);
    }

    pozycja=Gracz->DoTheyCover(*test);
    if(pozycja.typ==ObjectTypes::Platforma)       //etap reakcji na kolizje
    {
        //std::cout<<"ccc\n";
        Gracz->react(pozycja);
        if(Gracz->ConnectionToMove())
            Gracz->SetDependent(test);

    }

    if(wektor.empty()==false)
    {//tylko do obslugi pieniedzy
       it2=wektor.begin();
    while(it2!=wektor.end()){
        pozycja=(*it2)->DoTheyCover(*Gracz);
    if(pozycja.typ==ObjectTypes::Hero)
    {
        (*it2)->react(pozycja);
        if(it2==wektor.end()){
        wektor.erase(it2);
        }
        else
            it2=wektor.erase(it2);
    }
    else
        it2++;
    }
    }

    for(it2=potwory.begin();it2!=potwory.end();it2++)
        {
        pozycja=(*it2)->DoTheyCover(*Gracz);
        if(pozycja.typ==ObjectTypes::Hero)
            (*it2)->react(pozycja);
        }

    /*if(pociski.empty()==false)
    {//tylko do obslugi pieniedzy
       it2=pociski.begin();
    while(it2!=pociski.end()){
        pozycja=(*it2)->DoTheyCover(*Gracz);
    if(pozycja.typ==ObjectTypes::Hero)
    {
        (*it2)->react(pozycja);
        if(it2==pociski.end()){
        pociski.erase(it2);
        }
        else
            it2=pociski.erase(it2);
    }
    else
        it2++;
    }
    }*/

    /*
    for(it2=pociski.begin();it2!=pociski.end();it2++)
        {
        pozycja=(*it2)->DoTheyCover(*Gracz);
        if(pozycja.typ==ObjectTypes::Hero)
            (*it2)->react(pozycja);
        }
        */

        if(pociski.empty()==false)
        {
         it2=pociski.begin();
    while(it2!=pociski.end())
        //while(it2!=pociski.end());
        {
        pozycja=(*it2)->DoTheyCover(*Gracz);
        if(pozycja.typ==ObjectTypes::Hero)
            (*it2)->react(pozycja);
            //it2++;
       // }
        //}

        /*for(it3=wektor.begin();it3!=wektor.end();it3++)//nie dziala bo wektor ma pieniadze, nic innego
        {
            pozycja=(*it2)->DoTheyCover(*(*it3));
        if((pozycja.typ==ObjectTypes::GroundFloor)||(pozycja.typ==ObjectTypes::Platforma))
            (*it2)->react(pozycja);
        }*/

        bool a=0;
        pozycja=(*it2)->DoTheyCover(*ziemia);
        if(pozycja.typ==ObjectTypes::GroundFloor)
        {
            (*it2)->react(pozycja);
            if(it2!=pociski.end())
            it2=pociski.erase(it2);
            else
                pociski.erase(it2);
            a=1;
            //std::cout<<"Nie ma juz pocisku w kontenerze\n";
        }
        //std::cout<<"A ja sprawdzam\n";
        //pozycja=(*it2)->DoTheyCover(*ziemia_wyspa);
        /*if(pozycja.typ==ObjectTypes::GroundFloor)
        {
            (*it2)->react(pozycja);
            if(it2!=pociski.end())
            it2=pociski.erase(it2);
            else
                pociski.erase(it2);
            a=1;
        }*/
        //std::cout<<"Czy sprawdzilem po usuniecie\n";
        //if
            else //(a==0)
            it2++;
        }
        }


    pozycja=brama->DoTheyCover(*Gracz);
    if(pozycja.typ==ObjectTypes::Hero)
    {
        brama->react(pozycja);
    }
    sf::Vector2f w {0,0};
    while(Orders.IsEmpty()==0)
    {
        command bufor=Orders.pop();
        bufor.GetAFunction()(*Gracz,a,w);
    }
}

void Game::draw()
{
    //if(!wektor.empty())
    //wektor.back()->draw(appwindow);
    /*for(it2=wektor.begin();it2!=wektor.end();it2++)
        (*it2)->draw(appwindow);

    for(it2=potwory.begin();it2!=potwory.end();it2++)
        (*it2)->draw(appwindow);*/
    test->draw(appwindow);
    ziemia->draw(appwindow);
    ziemia_wyspa->draw(appwindow);
    wrog->draw(appwindow);
    brama->draw(appwindow);
    for(it2=wektor.begin();it2!=wektor.end();it2++)
        (*it2)->draw(appwindow);

    for(it2=pociski.begin();it2!=pociski.end();it2++)
        (*it2)->draw(appwindow);

    for(it2=potwory.begin();it2!=potwory.end();it2++)
    {
        (*it2)->draw(appwindow);
        if((*it2)->DoItWannaFire()==true)
        {
            pociski.push_back((*it2)->ReturnBullet(Holder));
            std::shared_ptr<Observer> ob (new Observer);
            obserwatorzy.push_back(std::move(ob));
            pociski.back()->SetObserver((obserwatorzy.back()));
        }
    }

    Gracz->draw(appwindow);
    appwindow.display();
    appwindow.clear();
}

void Game::update()
{
     //DO BOMBY
    /*
    //test zmieniony na wektor.back()->
    pozycja=wektor.back()->DoTheyCover(*Gracz);
    if(pozycja.typ==ObjectTypes::Hero)
    {
        wektor.back()->react(pozycja);
    }

    pozycja=wektor.back()->->DoTheyCover(*ziemia);
    if(pozycja.typ==ObjectTypes::GroundFloor)       //etap reakcji na kolizje
    {
        wektor.back()->->react(pozycja);
    }

    pozycja=wektor.back()->->DoTheyCover(*ziemia_wyspa);
    if(pozycja.typ==ObjectTypes::GroundFloor)       //etap reakcji na kolizje
    {
        wektor.back()->->react(pozycja);
    }
    */
    //
    /*
    if(wektor.empty()==false)
    {
    if((*obserwatorzy.front()).WasSomethingObserved())
    {
        auto c=(obserwatorzy.front())->ReturnObserwation();
        if(typeid(c).name()==typeid(GameStates).name())
            stanGry=c;
        else
            std::cout<<"Zebrano pieniazek\n";
    }
    wektor.back()->update();
    }*/

    if(obserwatorzy.empty()==false)
    {
        std::vector<std::shared_ptr<Observer>>::iterator it=obserwatorzy.begin();
         while(it!=obserwatorzy.end())  //konieczne przy usuwaniu elementow z wektora podczas iteracji
         //taka operacja zwraca wskaznik do nastepengo elementu-> w forze po usunieciu, przeskakiwalibysmy obiekt
        {
         bool c=(*it)->WasSomethingObserved();
         if(c==true)
         {
             GameMechanisms d=(*it)->ReturnObserwation();
             switch(d)
             {
             case GameMechanisms::Win:
                {
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
             }

         }
         c=(*it)->IsItSenseToExist();
         if(c==false)
         {
             if(it!=obserwatorzy.end())
             it=obserwatorzy.erase(it);
             else
                {
                obserwatorzy.erase(it);
                break;
                }
         }
         else
            it++;
        }
    }

    /*if(wektor.size()!=0)
    {
    if(wektor.back()!=nullptr)
    wektor.back()->update();
    }
    else{}*/

    test->update();
    ziemia_wyspa->update();
    Gracz->update();
    brama->update();                              //etap aktualizacji dancyh
    ziemia->update();

    for(it2=wektor.begin();it2!=wektor.end();it2++)
        (*it2)->update();

    for(it2=potwory.begin();it2!=potwory.end();it2++)
        (*it2)->update();

    for(it2=pociski.begin();it2!=pociski.end();it2++)
        (*it2)->update();

    wrog->update();
    //poziom.CheckCollisions();
    //poziom.update();
}


void Game::Run()
{
    appwindow.create(sf::VideoMode(SZEROKOSCOKNA,WYSOKOSCOKNA,32),"okno");
    sf::Time TimeSinceLastUpdate;
    sf::Clock timer;
    sf::Time DeltaTime=sf::seconds(1.f/20.f);
    //int i=0;
    bool c=0;
    while(appwindow.isOpen())
    {
        //if(obserwatorzy.at(1)==nullptr)
        //std::cout<<"Obserwatorzy: "<<obserwatorzy.size()<<std::endl;
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
            //if(c==1)std::cout<<"c\n";
            update();//funkcja sprawdzajaca kolizje znajduje sie w update, ma byc w kodzie jak najpozniej, to dlatego
            draw();
            //if(c==1)std::cout<<"c\n";
            TimeSinceLastUpdate-=DeltaTime;
            }
        }
        ProcessEvent();
    }
}

void Game::ProcessInput()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        auto f=[](Entity& obiekt, sf::Time& a,sf::Vector2f& b){sf::Vector2f wektorek=sf::Vector2f(-1,0);obiekt.MoveEntity(wektorek,a,b);};
        command bufor {f,ObjectTypes::Hero};
        Orders.push(bufor);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        auto f=[](Entity& obiekt, sf::Time& a,sf::Vector2f& b){sf::Vector2f wektorek= sf::Vector2f(1,0);obiekt.MoveEntity(wektorek,a,b);};
        command bufor {f,ObjectTypes::Hero};
        Orders.push(bufor);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        auto f=[](Entity& obiekt, sf::Time& a,sf::Vector2f& b){sf::Vector2f wektorek= sf::Vector2f(0,-1);obiekt.MoveEntity(wektorek,a,b);};
        command bufor {f,ObjectTypes::Hero};
        Orders.push(bufor);
    }
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
