//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 9, study assistant David Kerschbaumer
//
// Authors: Michael Zweimüller  11916150
//          Johannes Aigner     11907005  
//------------------------------------------------------------------------------
//

#include "Interface.hpp"
#include "Game.hpp"
#include "Card.hpp"
#include "Player.hpp"
#include "CreatureCard.hpp"
#include "SpellCard.hpp"
#include "rapidjson/document.h"

#include <iostream> //LÖSCHEN


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
  for(auto const card : pick_up_stack)
  {
    delete card;
  }
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
  SpellType type;

  Card* cur_card;

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

      pick_up_stack.reserve(stack_size);
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
                cur_card = new CreatureCard(name, mana_costs, damage_points, life_points, \
                                                 shield, mana_drain, false);

                if(!checkForCardEquality(cur_card))
                {
                  delete cur_card;
                  break;
                }
                
                pick_up_stack.push_back(cur_card);
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

            if(std::strcmp(spell_name, Interface::STRING_HEALER.c_str()))
            {
              if(std::strcmp(spell_name, Interface::STRING_RELIEF.c_str()))
              {
                if(std::strcmp(spell_name, Interface::STRING_REBIRTH.c_str()))
                {
                  if(std::strcmp(spell_name, Interface::STRING_DRACULA.c_str()))
                  {
                    break;
                  }else
                  {
                    type = Oop::DRACULA;
                  }
                }else
                {
                  type = Oop::REBIRTH;
                }
              }else
              {
                type = Oop::RELIEF;
              }
            }else
            {
              type = Oop::HEALER;
            }
            
            cur_card = new SpellCard(type);
            pick_up_stack.push_back(cur_card);
            
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
bool Game::checkForCardEquality(Card* card)
{
  CreatureCard* cur_creature;
  CreatureCard* new_creature = dynamic_cast <CreatureCard*>(card);

  for(Card* cur : pick_up_stack)
  {
    if(cur->getType() == Card::CardType::CREATURE && \
      !(std::strcmp(cur->getName().c_str(), new_creature->getName().c_str())))
    {
      cur_creature = dynamic_cast <CreatureCard*>(cur);

      if(!((cur_creature->getManaCost() == new_creature->getManaCost()) && \
           (cur_creature->getLifePoints() == new_creature->getLifePoints()) && \
           (cur_creature-> getShield() == new_creature->getShield()) && \
           (cur_creature->getManaDrain() == new_creature->getManaDrain()) && \
           (cur_creature->getSpeedy() == new_creature->getSpeedy()) && \
           (cur_creature->getDamagePoints() == new_creature->getDamagePoints())))
      {
        return false;                                                                                                                                                                                                         
      }
    }
  }
  return true;
}


bool Game::setupPlayer()
{
	Player *Player1 = new Player();
	
	Player *Player2 = new Player();

	Player1->setCreatureCard(pick_up_stack);
	
	Player2->setCreatureCard(pick_up_stack);
	
	Player1->shufflePickupstackCall();
	
	Player2->shufflePickupstackCall();
		
	delete Player1;
	
	delete Player2;
	
	return false;
}


//------------------------------------------------------------------------------
void Game::run()
{ 
  
  //setupPlayer();

  //TO-DO (D2)
}
