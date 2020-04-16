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
#include "Card.hpp"
#include "CreatureCard.hpp"
#include "SpellCard.hpp"
#include "rapidjson/document.h"
 
//#include <iostream>


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
  
  std::string name;
  int stack_size, mana_costs, damage_points, life_points;
  bool shield, mana_drain;
  const char * spell_name;
/*
  Oop::CreatureCard creature_card;
  Oop::SpellCard spell_card;
*/
  //read file
  std::FILE* fptr = std::fopen(config_file.c_str(), "r");

  if (!fptr) {
    io_.error(Oop::Interface::ERROR_INVALID_CONFIG);
    return false;
  }

  std::fseek(fptr, 0, SEEK_END);
  size_t len = std::ftell(fptr);
  std::fseek(fptr, 0, SEEK_SET);
  std::string content(len + 1, '\0');
  std::fread(&content[0], 1, len, fptr);
  fclose(fptr);

  doc.Parse(content.c_str());
  
  //check json structure
  if((doc.IsObject()) && (doc.MemberCount() == 2) && \
     (doc.HasMember("Creatures")) && (doc.HasMember("Spells"))){
    Value& creatures = doc["Creatures"];
    Value& spells = doc["Spells"];

    if((creatures.IsArray()) && (spells.IsArray()) && \
       (stack_size = creatures.Size() + spells.Size() >= 10))
    {//check creatures
      for(index = 0; index < creatures.Size(); index++)
      {
        Value& temp = creatures[index];
        if(temp.HasMember("name") && temp.HasMember("mana_cost") && \
           temp.HasMember("damage_points") && temp.HasMember("life_points") &&  \
           temp.HasMember("shield") && temp.HasMember("mana_drain"))
          {

            if((temp["mana_cost"].IsInt()) && (temp["damage_points"].IsInt()) && \
               (temp["life_points"].IsInt()) && temp["shield"].IsBool() && \
                temp["mana_drain"].IsBool() && temp["name"].IsString() && \
               (temp.MemberCount() == 6))
            {
              name = temp["name"].GetString();
              mana_costs = temp["mana_cost"].GetInt();
              damage_points = temp["damage_points"].GetInt();
              life_points = temp["life_points"].GetInt();
              shield = temp["shield"].GetBool();
              mana_drain = temp["mana_drain"].GetBool();
              
              if(inBetween(mana_costs, 1, 15) && inBetween(damage_points, 0, 9) && \
                 inBetween(life_points, 1, 9))
              {
                //new Oop::CreatureCard(name, mana_costs, damage_points, life_points, \
                                      shield, mana_drain, false);

                //TODO Add and check for same attribues if same name
              }else
              {
                break;
              }
              
                            
            }else
            {
              break;
            }
            
          }else
          {
            break;
          }
      }

      if(index == creatures.Size())
      {//check spells
        for(index = 0; index < spells.Size(); index++)
        {
          Value& temp = spells[index];
          if(temp.HasMember("name") && temp["name"].IsString() && \
            (temp.MemberCount() == 1))
          {
            name = temp["name"].GetString();
            spell_name = name.c_str();
            if(!(std::strcmp(spell_name, "Healer") && std::strcmp(spell_name, "Relief") && \
                std::strcmp(spell_name, "Rebirth") && std::strcmp(spell_name, "Dracula")))
            {
              //pick_up_stack.push_back(new SpellCard())
            }else
            {
              break;
            }
            
          }else
          {
            break;
          }
        }

        if(index == spells.Size())
        {
          return true;
        }
      }
    }
  }

  io_.error(Oop::Interface::ERROR_INVALID_CONFIG);
  return false;
}

//------------------------------------------------------------------------------
bool Game::inBetween(int x, int low, int high)
{
  return ((x >= low) && (x <= high));
}


//------------------------------------------------------------------------------
void Game::run()
{
  //TO-DO (D2)
}
