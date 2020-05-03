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
#include <math.h>

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdlib.h>

using std::ifstream; //*
using std::ofstream; //*
using std::string;   //*

using Oop::Game;
using Oop::Interface;
using namespace rapidjson;

//------------------------------------------------------------------------------
Game::Game(Oop::Interface &io) : io_(io)
{
}

//------------------------------------------------------------------------------
Game::~Game() noexcept
{
  for (auto const card : pick_up_stack)
  {
    delete card;
  }

  delete players[0];
  delete players[1];
}

//------------------------------------------------------------------------------
bool Game::loadConfig(std::string config_file)
{
  Document doc;
  SizeType index;

  std::string name;
  int stack_size, mana_costs, damage_points, life_points;
  bool shield, mana_drain;
  const char *spell_name;
  SpellType type;

  Card *cur_card;

  //read file
  std::FILE *fptr = std::fopen(config_file.c_str(), "r");

  if (!fptr)
  {
    io_.error(Oop::Interface::ERROR_INVALID_CONFIG);
    return false;
  }

  std::fseek(fptr, 0, SEEK_END);
  size_t len = size_t(std::ftell(fptr));
  std::fseek(fptr, 0, SEEK_SET);
  std::string content(len + 1, '\0');
  std::fread(&content[0], 1, len, fptr);
  fclose(fptr);

  doc.Parse(content.c_str());

  //check json structure
  if ((doc.IsObject()) && (doc.MemberCount() == 2) &&
      (doc.HasMember("Creatures")) && (doc.HasMember("Spells")))
  {
    Value &creatures = doc["Creatures"];
    Value &spells = doc["Spells"];

    if ((creatures.IsArray()) && (spells.IsArray()) &&
        (stack_size = creatures.Size() + spells.Size() >= 10))

    { //check creatures
      for (index = 0; index < creatures.Size(); index++)
      {
        Value &temp = creatures[index];
        if (temp.HasMember("name") && temp.HasMember("mana_cost") &&
            temp.HasMember("damage_points") && temp.HasMember("life_points") &&
            temp.HasMember("shield") && temp.HasMember("mana_drain"))
        {

          if ((temp["mana_cost"].IsInt()) && (temp["damage_points"].IsInt()) &&
              (temp["life_points"].IsInt()) && temp["shield"].IsBool() &&
              temp["mana_drain"].IsBool() && temp["name"].IsString() &&
              (temp.MemberCount() == 6))
          {
            name = temp["name"].GetString();
            mana_costs = temp["mana_cost"].GetInt();
            damage_points = temp["damage_points"].GetInt();
            life_points = temp["life_points"].GetInt();
            shield = temp["shield"].GetBool();
            mana_drain = temp["mana_drain"].GetBool();

            if (inBetween(mana_costs, 1, 15) && inBetween(damage_points, 0, 9) &&
                inBetween(life_points, 1, 9))
            {
              cur_card = new CreatureCard(name, mana_costs, damage_points, life_points,
                                          shield, mana_drain, false);

              if (!checkOnCreatureEquality(cur_card))
              {
                delete cur_card;
                break;
              }

              pick_up_stack.push_back(cur_card);
            }
            else
            {
              break;
            }
          }
          else
          {
            break;
          }
        }
        else
        {
          break;
        }
      }

      if (index == creatures.Size())
      { //check spells
        for (index = 0; index < spells.Size(); index++)
        {
          Value &temp = spells[index];
          if (temp.HasMember("name") && temp["name"].IsString() &&
              (temp.MemberCount() == 1))
          {
            name = temp["name"].GetString();
            spell_name = name.c_str();

            if (std::strcmp(spell_name, Interface::STRING_HEALER.c_str()))
            {
              if (std::strcmp(spell_name, Interface::STRING_RELIEF.c_str()))
              {
                if (std::strcmp(spell_name, Interface::STRING_REBIRTH.c_str()))
                {
                  if (std::strcmp(spell_name, Interface::STRING_DRACULA.c_str()))
                  {
                    break;
                  }
                  else
                  {
                    type = Oop::DRACULA;
                  }
                }
                else
                {
                  type = Oop::REBIRTH;
                }
              }
              else
              {
                type = Oop::RELIEF;
              }
            }
            else
            {
              type = Oop::HEALER;
            }

            cur_card = new SpellCard(type);
            pick_up_stack.push_back(cur_card);
          }
          else
          {
            break;
          }
        }

        if (index == spells.Size())
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
bool Game::checkOnCreatureEquality(Card *card)
{
  CreatureCard *cur_creature;
  CreatureCard *new_creature = dynamic_cast<CreatureCard *>(card);

  for (Card *cur : pick_up_stack)
  {
    if (cur->getType() == Card::CardType::CREATURE &&
        !(std::strcmp(cur->getName().c_str(), new_creature->getName().c_str())))
    {
      cur_creature = dynamic_cast<CreatureCard *>(cur);

      if (!((cur_creature->getManaCost() == new_creature->getManaCost()) &&
            (cur_creature->getLifePoints() == new_creature->getLifePoints()) &&
            (cur_creature->getShield() == new_creature->getShield()) &&
            (cur_creature->getManaDrain() == new_creature->getManaDrain()) &&
            (cur_creature->getSpeedy() == new_creature->getSpeedy()) &&
            (cur_creature->getDamagePoints() == new_creature->getDamagePoints())))
      {
        return false;
      }
    }
  }
  return true;
}

//------------------------------------------------------------------------------
bool Game::setupPlayer()
{
  players[0] = new Player();
  players[1] = new Player();

  players[0]->copyPickUpStack(pick_up_stack);
  players[1]->copyPickUpStack(pick_up_stack);

  players[0]->shufflePickUpStack();
  players[1]->shufflePickUpStack();

  players[0]->setName(io_.readPlayerName(0));
  players[1]->setName(io_.readPlayerName(1));

  players[0]->takeOffCards(3);
  players[1]->takeOffCards(3);

  return true;
}

//------------------------------------------------------------------------------
void Game::run()
{
  int round_counter = -1;
  cur_player = 1;

  setupPlayer();

  while (true)
  {
    cur_player = cur_player ^ 1;

    if (cur_player == 0)
    {
      round_counter++;
      io_.out(Oop::Interface::OutputType::INFO, Oop::Interface::INFO_ROUND + std::to_string(round_counter));
    }

    (round_counter < 3) ? (players[cur_player]->addMana(pow(2, round_counter))) : (players[cur_player]->addMana(8));

    io_.out(Oop::Interface::OutputType::INFO, Oop::Interface::INFO_CURRENT_PLAYER + players[cur_player]->getName());

    players[cur_player]->takeOffCards(1);

    io_.out(players[cur_player], players[cur_player ^ 1]);

    if (!playerCommandInput())
    {
      return; //TODO
    }
  }
}

//------------------------------------------------------------------------------
bool Game::playerCommandInput()
{
  std::string input;

  while (true)
  {
    io_.printCommandPrompt(players[cur_player]->getName());
    input = io_.in();
    if (!input.size())
    {
      continue;
    }
    

    if (!strcasecmp(Oop::Interface::COMMAND_QUIT.c_str(), input.c_str()))
    {
      io_.out(Oop::Interface::OutputType::INFO, Oop::Interface::ENDLINE_PART_ONE +
                                                    players[cur_player ^ 1]->getName() + Oop::Interface::ENDLINE_PART_TWO);
      return false;
    }

    if (!strcasecmp(Oop::Interface::COMMAND_HELP.c_str(), input.c_str()))
    {
      input = Oop::Interface::INFO_HELP_MSGS.at(0);
      for (size_t index = 1; index < Oop::Interface::INFO_HELP_MSGS.size(); index++)
      {
        input = input + "\n" + Oop::Interface::INFO_HELP_MSGS.at(index);
      }
      io_.out(Oop::Interface::OutputType::INFO, input);
      continue;
    }

    if (!strcasecmp(Oop::Interface::COMMAND_STATE.c_str(), input.c_str()))
    {
      io_.out(players[cur_player], players[cur_player ^ 1]);
      continue;
    }

    if (!strcasecmp(Oop::Interface::COMMAND_FINISH.c_str(), input.c_str()))
    {
      return true;
    }

    //attack command
    std::vector<std::string> arguments = tokenizeStr(input);

    if (!strcasecmp(Oop::Interface::COMMAND_ATTACK.c_str(), arguments[0].c_str()))
    {
      long x = 0;
      long y = 0;
      if (arguments.size() != 4)
      {
        io_.out(Oop::Interface::OutputType::INFO, Oop::Interface::WARNING_WRONG_PARAM_COUNT);
        continue;
      }
      if ((x = std::strtol(arguments[1].c_str(), nullptr, 10)) && Game::inBetween(x, 0, 7) &&
          !strcasecmp("with", arguments[2].c_str()) &&
          (y = std::strtol(arguments[3].c_str(), nullptr, 10)) && Game::inBetween(y, 1, 7))
      {
        if (players[cur_player ^ 1]->getGameField()[x] == nullptr || players[cur_player]->getGameField()[y] == nullptr || !players[cur_player]->getGameField()[y]->getAlreadyAttacked())
        {
          io_.out(Oop::Interface::OutputType::INFO, Oop::Interface::WARNING_EXECUTION_NOT_POSSIBLE);
          continue;
        }
        else if (true /*validate if shields are up*/)
        {
          io_.out(Oop::Interface::OutputType::INFO, "test");
          //TODO attack command itself
        }
      }
      else
      {
        io_.out(Oop::Interface::OutputType::INFO, Oop::Interface::WARNING_WRONG_PARAMETER);
        continue;
      }
    }
    else
    {
      io_.out(Oop::Interface::OutputType::INFO, Oop::Interface::WARNING_UNKNOWN_COMMAND);
    }
  }

  return false;
  ;
}
/*
const std::string Interface::COMMAND_HELP = "help";
const std::string Interface::COMMAND_ATTACK = "attack";
const std::string Interface::COMMAND_SET = "set";
const std::string Interface::COMMAND_CAST = "cast";
const std::string Interface::COMMAND_SACRIFICE = "sacrifice";
const std::string Interface::COMMAND_STATE = "state";
const std::string Interface::COMMAND_FINISH = "finish";
const std::string Interface::COMMAND_QUIT = "quit";
*/

//------------------------------------------------------------------------------
bool Game::compareCommandInput(std::string cmd, std::string input)
{
  
  return false;
}

//------------------------------------------------------------------------------
int Game::getCurPlayer() const
{
  return cur_player;
}

//------------------------------------------------------------------------------
std::vector<std::string> Game::tokenizeStr(std::string input)
{
  std::istringstream iss(input);
  std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};

  return tokens;
}
