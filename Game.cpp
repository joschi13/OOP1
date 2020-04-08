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
#include "rapidjson/document.h"
 
#include <iostream>


using Oop::Interface;
using Oop::Game;
using namespace rapidjson;

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
  Document doc;
  SizeType index;

  std::FILE* fptr = std::fopen(config_file.c_str(), "r");

  if (!fptr) {
    std::cout << Oop::Interface::ERROR_INVALID_CONFIG  << std::endl;
    return false;
  }

  std::fseek(fptr, 0, SEEK_END);
  size_t len = std::ftell(fptr);
  std::fseek(fptr, 0, SEEK_SET);
  std::string content(len + 1, '\0');
  std::fread(&content[0], 1, len, fptr);
  fclose(fptr);

  doc.Parse(content.c_str());

  if((doc.IsObject()) && (doc.HasMember("Creatures")) && \
     (doc.HasMember("Spells"))){
    Value& creatures = doc["Creatures"];
    Value& spells = doc["Spells"];

    if((creatures.IsArray()) && (spells.IsArray()) && \
       (creatures.Size() + spells.Size() >= 10))
    {
      for(index = 0; index < creatures.Size(); index++)
      {
        Value& temp = creatures[index];
        if(temp.HasMember("name") && temp.HasMember("mana_cost") && \
           temp.HasMember("damage_points") && temp.HasMember("life_points") &&  \
           temp.HasMember("shield") && temp.HasMember("mana_drain"))
          {
            if((1 < temp["mana_cost"].GetInt() < 15) && (0 < temp["damage_points"].GetInt() < 9) && \
               (1 < temp["life_points"].GetInt() < 9) && temp["shield"].IsBool() && \
                temp["mana_drain"].IsBool())
            {
              //TODO
            }else
            {
              break;
            }
            
          }else
          {
            break;
          }
      }

      if(index == creatures.Size()){
        for(index = 0; index < spells.Size(); index++)
        {
          Value& temp = spells[index];
          if(temp.HasMember("name") && temp.MemberCount() == 1)
          {
            
          }else
          {
            break;
          }
          
        }

        if(index == spells.Size())
        {
          //TODO
          return true;
        }
      }
    }
  }

  io_.error(Oop::Interface::ERROR_INVALID_CONFIG);
  return false;
}

//------------------------------------------------------------------------------
void Game::run()
{
  //TO-DO (D2)
}
