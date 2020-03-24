//------------------------------------------------------------------------------
// Game.cpp
//
// Author: Michael Zweimüller
//
//------------------------------------------------------------------------------
//
#include <iostream>
#include "Interface.hpp"
#include "Game.hpp"


using Oop::Game;

Game::Game(Oop::Interface &io) : io_(io){}


bool loadConfig(std::string config_file)
{
  if(/*invalid config file*/true)
  {
    std::cout << Oop::Interface::ERROR_INVALID_CONFIG  << std::endl;
    return false;
  }
  //TO-DO
}

void run()
{
  //TO-DO
}