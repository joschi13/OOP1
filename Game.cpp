//------------------------------------------------------------------------------
// Game.cpp
//
// Author: Michael Zweimüller
//
//------------------------------------------------------------------------------
//
#include <iostream>
#include "Game.hpp"


using Oop::Game;
using Oop::Interface;

Game::Game(Oop::Interface &io) : io_(io){}


bool Game::loadConfig(std::string config_file)
{
  if(/*invalid config file*/true)
  {
    std::cout << Oop::Interface::ERROR_INVALID_CONFIG  << std::endl;
    return false;
  }
  //TO-DO
}

void Game::run()
{
  //TO-DO
}
