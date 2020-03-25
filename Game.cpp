//------------------------------------------------------------------------------
// Game.cpp
//
// Author: Michael Zweimüller
//
//------------------------------------------------------------------------------
//

//* from 2_05.cpp

#include <iostream>//*
#include <fstream>//*
#include "Interface.hpp"
#include "Game.hpp"
#include "rapidjson/document.h"


using std::ofstream;//*
using std::ifstream;//*
using std::string;//*

using namespace rapidjson;
using Oop::Game;

Game::Game(Oop::Interface &io) : io_(io){}


bool loadConfig(std::string config_file)
{
  string json;
  ifstream infile(config_file);
  Document document;
  document.Parse(json);
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