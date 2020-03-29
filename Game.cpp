//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 9, study assistant David Kerschbaumer
//
// Authors: Michael Zweimüller 11916150
//------------------------------------------------------------------------------
//

#include "Interface.hpp"
#include "Game.hpp"

#include <iostream>

using Oop::Interface;
using Oop::Game;

//------------------------------------------------------------------------------
Game::Game(Oop::Interface &io) : io_(io)
{
}

//------------------------------------------------------------------------------
Game::~Game() noexcept
{
}

//------------------------------------------------------------------------------
bool Game::loadConfig(std::string config_file)
{
  if(/*invalid config file*/true)
  {
    std::cout << Oop::Interface::ERROR_INVALID_CONFIG  << std::endl;
    return false;
  }
  //TO-DO (D2)
}

//------------------------------------------------------------------------------
void Game::run()
{
  //TO-DO (D2)
}
