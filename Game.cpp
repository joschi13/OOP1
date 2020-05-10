//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 9, study assistant David Kerschbaumer
//
// Authors: Michael Zweimüller 		11916150
//			    Martin Schachl 			  11907003
// 			    Johannes Aigner			  11907005
//------------------------------------------------------------------------------
//

#include "Interface.hpp"
#include "Game.hpp"
#include "Card.hpp"
#include "Player.hpp"
#include "CreatureCard.hpp"
#include "SpellCard.hpp"
#include "rapidjson/document.h"

#include <math.h>

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdlib.h>

using Oop::Game;
using Oop::Interface;
using rapidjson::Value;

const int CMD_MIN = 1;
const int CMD_MAX = 7;

//------------------------------------------------------------------------------
Game::Game(Oop::Interface &io) : io_(io)
{
  players[0] = NULL;
  players[1] = NULL;
}

//------------------------------------------------------------------------------
Game::~Game() noexcept
{
  for (auto const card : pick_up_stack)
  {
    delete card;
  }

  if (players[0] != NULL || players[1] != NULL)
  {
    delete players[0];
    delete players[1];
  }
}

//------------------------------------------------------------------------------
bool Game::loadConfig(std::string config_file)
{
  rapidjson::Document doc;
  rapidjson::SizeType index;

  std::string name;
  int mana_costs, damage_points, life_points;
  bool found, shield, mana_drain, speedy;
  bool first_creature = true;
  bool BONUS = false;
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
  if ((!doc.IsObject()) || (doc.MemberCount() != 2) ||
      (!doc.HasMember("Creatures")) || (!doc.HasMember("Spells")))
  {
    io_.error(Oop::Interface::ERROR_INVALID_CONFIG);
    return false;
  }

  Value &creatures = doc["Creatures"];
  Value &spells = doc["Spells"];

  if ((!creatures.IsArray()) || (!spells.IsArray()) ||
      (creatures.Size() + spells.Size() < 10))

  {
    io_.error(Oop::Interface::ERROR_INVALID_CONFIG);
    return false;
  }

  //check creatures
  for (index = 0; index < creatures.Size(); index++)
  {
    Value &temp = creatures[index];
    if (!temp.HasMember("name") || !temp.HasMember("mana_cost") ||
        !temp.HasMember("damage_points") || !temp.HasMember("life_points") ||
        !temp.HasMember("shield") || !temp.HasMember("mana_drain"))
    {
      io_.error(Oop::Interface::ERROR_INVALID_CONFIG);
      return false;
    }

    if (first_creature)
    {
      if (temp.HasMember("speedy"))
      {
        BONUS = true;
      }
      first_creature = false;
    }

    if ((temp["mana_cost"].IsInt()) && (temp["damage_points"].IsInt()) &&
        (temp["life_points"].IsInt()) && temp["shield"].IsBool() &&
        temp["mana_drain"].IsBool() && temp["name"].IsString() &&
        (temp.MemberCount() == (BONUS ? 7 : 6)))
    {
      if (BONUS)
      {
        if (!temp["speedy"].IsBool())
        {
          break;
        }
      }
      name = temp["name"].GetString();
      mana_costs = temp["mana_cost"].GetInt();
      damage_points = temp["damage_points"].GetInt();
      life_points = temp["life_points"].GetInt();
      shield = temp["shield"].GetBool();
      mana_drain = temp["mana_drain"].GetBool();
      speedy = BONUS ? temp["speedy"].GetBool() : false;

      if (!inBetween(mana_costs, 1, 15) ||
          !inBetween(damage_points, 0, 9) ||
          !inBetween(life_points, 1, 9) ||
          !(name.length() < 9))
      {
        io_.error(Oop::Interface::ERROR_INVALID_CONFIG);
        return false;
      }

      cur_card = new CreatureCard(name, mana_costs, damage_points,
                                  life_points, shield, mana_drain, speedy);

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
  if (index != creatures.Size())
  {
    io_.error(Oop::Interface::ERROR_INVALID_CONFIG);
    return false;
  }

  //check spells
  for (index = 0; index < spells.Size(); index++)
  {
    found = false;
    Value &temp = spells[index];
    if (!temp.HasMember("name") || !temp["name"].IsString() ||
        (temp.MemberCount() != 1))
    {
      io_.error(Oop::Interface::ERROR_INVALID_CONFIG);
      return false;
    }
    name = temp["name"].GetString();
    spell_name = name.c_str();

    if (!std::strcmp(spell_name, Interface::STRING_HEALER.c_str()))
    {
      type = Oop::HEALER;
      found = true;
    }

    if (!std::strcmp(spell_name, Interface::STRING_RELIEF.c_str()))
    {
      type = Oop::RELIEF;
      found = true;
    }

    if (!std::strcmp(spell_name, Interface::STRING_REBIRTH.c_str()))
    {
      type = Oop::REBIRTH;
      found = true;
    }

    if (!std::strcmp(spell_name, Interface::STRING_DRACULA.c_str()))
    {
      type = Oop::DRACULA;
      found = true;
    }

    if (!std::strcmp(spell_name, Interface::STRING_TRAITOR.c_str()))
    {
      type = Oop::TRAITOR;
      found = true;
    }

    if (found)
    {
      cur_card = new SpellCard(type);
      pick_up_stack.push_back(cur_card);
    }
    else
    {
      io_.error(Oop::Interface::ERROR_INVALID_CONFIG);
      return false;
    }
  }
  return true;
}

//------------------------------------------------------------------------------
bool Game::inBetween(int x_pos, int low, int high)
{
  return ((x_pos >= low) && (x_pos <= high));
}

//------------------------------------------------------------------------------
bool Game::checkOnCreatureEquality(Card *card)
{
  CreatureCard *cur_creature;
  CreatureCard *new_creature = dynamic_cast<CreatureCard *>(card);

  for (Card *cur : pick_up_stack)
  {
    if (cur->getType() == Card::CardType::CREATURE &&
        !(std::strcmp(cur->getName().c_str(), 
          new_creature->getName().c_str())))
    {
      cur_creature = dynamic_cast<CreatureCard *>(cur);

      if (!((cur_creature->getManaCost() ==
             new_creature->getManaCost()) &&
            (cur_creature->getLifePoints() ==
             new_creature->getLifePoints()) &&
            (cur_creature->getShield() ==
             new_creature->getShield()) &&
            (cur_creature->getManaDrain() ==
             new_creature->getManaDrain()) &&
            (cur_creature->getSpeedy() ==
             new_creature->getSpeedy()) &&
            (cur_creature->getDamagePoints() ==
             new_creature->getDamagePoints())))
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

  players[0]->takeOffCards(3, 7);
  players[1]->takeOffCards(3, 7);

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

    players[cur_player]->setAllFieldCardsRdy();

    if (cur_player == 0)
    {
      round_counter++;
      io_.out(Oop::Interface::OutputType::INFO, 
        Oop::Interface::INFO_ROUND + std::to_string(round_counter));
    }

    (round_counter < 3) ? (players[cur_player]->addMana(pow(2, round_counter)))
                        : (players[cur_player]->addMana(8));

    io_.out(Oop::Interface::OutputType::INFO,
            Oop::Interface::INFO_CURRENT_PLAYER + 
              players[cur_player]->getName());

    players[cur_player]->takeOffCards(1, 7);

    if (isDead())
    {
      return;
    }

    io_.out(players[cur_player], players[cur_player ^ 1]);

    if (!playerCommandInput())
    {
      return;
    }
    players[cur_player]->setAllFieldShieldCardsRdy();
  }
}

//------------------------------------------------------------------------------
bool Game::playerCommandInput()
{
  std::string helpstr;
  std::vector<std::string> arguments;

  while (true)
  {
    io_.printCommandPrompt(players[cur_player]->getName());
    arguments = tokenizeStr(io_.in());
    if (!arguments.size())
    {
      continue;
    }

    if (!strcasecmp(Oop::Interface::COMMAND_HELP.c_str(), 
          arguments[0].c_str()))
    {
      if (Game::compareCommandInput(arguments, "nullptr", 0, 0, 0, 0))
      {
        for (size_t index = 0; index < Oop::Interface::INFO_HELP_MSGS.size(); 
          index++)
        {
          io_.out(Oop::Interface::OutputType::INFO, 
            Oop::Interface::INFO_HELP_MSGS.at(index));
        }
      }
      continue;
    }

    if (!strcasecmp(Oop::Interface::COMMAND_STATE.c_str(),
          arguments[0].c_str()))
    {
      if (Game::compareCommandInput(arguments, "nullptr", 0, 0, 0, 0))
      {
        io_.out(players[cur_player], players[cur_player ^ 1]);
      }
      continue;
    }

    if (!strcasecmp(Oop::Interface::COMMAND_QUIT.c_str(), 
      arguments[0].c_str()))
    {
      if (Game::compareCommandInput(arguments, "nullptr", 0, 0, 0, 0))
      {
        io_.out(Oop::Interface::OutputType::INFO,
                Oop::Interface::ENDLINE_PART_ONE +
                    players[cur_player ^ 1]->getName() +
                    Oop::Interface::ENDLINE_PART_TWO);
      }
      return false;
    }

    if (!strcasecmp(Oop::Interface::COMMAND_FINISH.c_str(),
                    arguments[0].c_str()))
    {
      if (Game::compareCommandInput(arguments, "nullptr", 0, 0, 0, 0))
      {
        return true;
      }
      continue;
    }

    if (!strcasecmp(Oop::Interface::COMMAND_ATTACK.c_str(),
                    arguments[0].c_str()))
    {
      if (Game::compareCommandInput(arguments, "with",
            CMD_MIN - 1, CMD_MAX, CMD_MIN, CMD_MAX))
      {
        if (Game::executeAtt(arguments))
        {
          return false;
        }
      }
      continue;
    }
    
    if (!strcasecmp(Oop::Interface::COMMAND_SET.c_str(), arguments[0].c_str()))
    {
      if (Game::compareCommandInput(arguments, "to", CMD_MIN,
            players[cur_player]->getHandSize(), CMD_MIN, CMD_MAX))
      {
        Game::executeSet(arguments);
      }
      continue;
    }

    if (!strcasecmp(Oop::Interface::COMMAND_CAST.c_str(), 
          arguments[0].c_str()))
    {
      if (Game::compareCommandInput(arguments, "nullstr", 
            CMD_MIN, players[cur_player]->getHandSize(), 0, 0))
      {
        Game::executeCast(arguments);
      }
      continue;
    }

    if (!strcasecmp(Oop::Interface::COMMAND_SACRIFICE.c_str(), 
          arguments[0].c_str()))
    {
      if (Game::compareCommandInput(arguments, "nullstr", 
            CMD_MIN, players[cur_player]->getHandSize(), 0, 0))
      {
        Game::executeSac(arguments);
      }
      continue;
    }

    else
    {
      io_.out(Oop::Interface::OutputType::INFO,
              Oop::Interface::WARNING_UNKNOWN_COMMAND);
    }
  }

  return false;
}

//------------------------------------------------------------------------------
bool Game::compareCommandInput(std::vector<std::string> arguments,
      std::string prep, int x_min, int x_max, int y_min, int y_max)
{
  if (arguments.size() != checkParamCount(arguments[0]))
  {
    io_.out(Oop::Interface::OutputType::INFO,
              Oop::Interface::WARNING_WRONG_PARAM_COUNT);
    return false;
  }

  if (arguments.size() > 1 &&
      !checkRanges(arguments, prep, x_min, x_max, y_min, y_max))
  {
    io_.out(Oop::Interface::OutputType::INFO,
              Oop::Interface::WARNING_WRONG_PARAMETER);
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------
unsigned long Game::checkParamCount(std::string command)
{
  if (!strcasecmp(command.c_str(),
                  Oop::Interface::COMMAND_ATTACK.c_str()) ||
      !strcasecmp(command.c_str(), Oop::Interface::COMMAND_SET.c_str()))
  {
    return 4;
  }

  if (!strcasecmp(command.c_str(),
                  Oop::Interface::COMMAND_CAST.c_str()) ||
      !strcasecmp(command.c_str(), Oop::Interface::COMMAND_SACRIFICE.c_str()))
  {
    return 2;
  }

  if (!strcasecmp(command.c_str(), Oop::Interface::COMMAND_FINISH.c_str()) ||
      !strcasecmp(command.c_str(), Oop::Interface::COMMAND_QUIT.c_str()) ||
      !strcasecmp(command.c_str(), Oop::Interface::COMMAND_STATE.c_str()) ||
      !strcasecmp(command.c_str(), Oop::Interface::COMMAND_HELP.c_str()))
  {
    return 1;
  }

  return 0;
}

//------------------------------------------------------------------------------
bool Game::checkRanges(std::vector<std::string> arguments,
      std::string prep, int x_min, int x_max, int y_min, int y_max)
{
  size_t x_pos = 0;
  size_t y_pos = 0;
  std::istringstream x_pos_stringstream(arguments[1]);
  x_pos_stringstream >> x_pos;

  if (arguments.size() <= 2)
  {
    return (!x_pos_stringstream.fail() && 
            Game::inBetween(x_pos, x_min, x_max));
  }
  else
  {
    std::istringstream y_pos_stringstream(arguments[3]);
    y_pos_stringstream >> y_pos;
    return (!x_pos_stringstream.fail() && 
            Game::inBetween(x_pos, x_min, x_max) && 
            !strcasecmp(prep.c_str(), arguments[2].c_str()) &&
            !y_pos_stringstream.fail() && 
            Game::inBetween(y_pos, y_min, y_max));
  }
  return false;
}
//------------------------------------------------------------------------------
bool Game::executeAtt(std::vector<std::string> arguments)
{
  long x_pos = std::strtol(arguments[1].c_str(), nullptr, 10);
  long y_pos = std::strtol(arguments[3].c_str(), nullptr, 10);

  if (x_pos == 0) //attacking the enemy himself
  {
    y_pos--;

    if (players[cur_player]->getGameField()[y_pos] == nullptr ||
        !players[cur_player]->getGameField()[y_pos]->getReadyToFight()||
        players[cur_player]->getGameField()[y_pos]->getAlreadyAttacked())
    {
      io_.out(Oop::Interface::OutputType::INFO, 
                Oop::Interface::WARNING_EXECUTION_NOT_POSSIBLE);
      return false;
    }

    if (!checkForShield(-1))
    {
      players[cur_player ^ 1]->reduceLifePoints(players[cur_player]->
        getGameField()[y_pos]->getDamagePoints());

      if (isDead())
      {
        return true;
      }

      if (players[cur_player]->getGameField()[y_pos]->getManaDrain())
      {
        players[cur_player ^ 1]->reduceMana(15);
      }
    }

    else
    {
      io_.out(Oop::Interface::OutputType::INFO, 
                Oop::Interface::WARNING_SHIELD_MONSTER);
      return false;
    }
  }

  if (x_pos > 0) //attacking enemy cards
  {
    x_pos--;
    y_pos--;

    if (players[cur_player ^ 1]->getGameField()[x_pos] == nullptr ||
        players[cur_player]->getGameField()[y_pos] == nullptr ||
        players[cur_player]->getGameField()[y_pos]->getAlreadyAttacked()||
        !players[cur_player]->getGameField()[y_pos]->getReadyToFight()||
        !players[cur_player ^ 1]->getGameField()[x_pos]->getReadyToFight())
    {
      io_.out(Oop::Interface::OutputType::INFO,
                Oop::Interface::WARNING_EXECUTION_NOT_POSSIBLE);
      return false;
    }

    if (checkForShield(x_pos))
    {
      io_.out(Oop::Interface::OutputType::INFO,
                Oop::Interface::WARNING_SHIELD_MONSTER);
      return false;
    }

    players[cur_player ^ 1]->damageMonsters(players[cur_player]->
      getGameField()[y_pos]->getDamagePoints(), x_pos);
  }

  players[cur_player]->setAlreadyAttacked(y_pos);
  return false;
}

//------------------------------------------------------------------------------
void Game::executeSet(std::vector<std::string> arguments)
{
  long x_pos = std::strtol(arguments[1].c_str(), nullptr, 10) - 1;
  long y_pos = std::strtol(arguments[3].c_str(), nullptr, 10) - 1;


  if (players[cur_player]->getGameField()[y_pos] != nullptr ||
      x_pos >= (players[cur_player]->getHandSize()) ||
      players[cur_player]->getHandCards().at(static_cast<size_t>(x_pos))
        ->getType() != Card::CardType::CREATURE)
  {
    io_.out(Oop::Interface::OutputType::INFO,
            Oop::Interface::WARNING_EXECUTION_NOT_POSSIBLE);
    return;
  }

  if (!players[cur_player]->setCardOnGameField(x_pos, y_pos))
  {
    io_.out(Oop::Interface::OutputType::INFO,
            Oop::Interface::WARNING_NOT_ENOUGH_MANA);
    return;
  }

  return;
}

//------------------------------------------------------------------------------
void Game::executeCast(std::vector<std::string> arguments)
{
  int x_pos = atoi(arguments[1].c_str()) - 1;

  if (players[cur_player]->getHandCards().at(static_cast<size_t>(x_pos)) 
      == nullptr || 
      players[cur_player]->getHandCards().at(static_cast<size_t>(x_pos))
        ->getType() != Card::CardType::SPELL)
  {
    io_.out(Oop::Interface::OutputType::INFO,
            Oop::Interface::WARNING_EXECUTION_NOT_POSSIBLE);
    return;
  }

  SpellCard *card = dynamic_cast<SpellCard *>(players[cur_player]->
    getHandCards().at(static_cast<size_t>(x_pos)));

  if (card->action(*this))
  {
    players[cur_player]->eraseSpellHandCard(x_pos);
  }

  if (isDead())
  {
    return;
  }

  return;
}

//------------------------------------------------------------------------------
void Game::executeSac(std::vector<std::string> arguments)
{
  size_t y_pos = static_cast<size_t>(atoi(arguments[1].c_str())) - 1;

  if (players[cur_player]->getHandCards().at(y_pos) == nullptr)
  {
    io_.out(Oop::Interface::OutputType::INFO,
            Oop::Interface::WARNING_EXECUTION_NOT_POSSIBLE);
    return;
  }

  if (players[cur_player]->getHandCards().at(y_pos)->getType() ==
      Card::CardType::CREATURE)
  {
    players[cur_player]->moveToGraveyard(static_cast<long>(y_pos));
  }

  else if (players[cur_player]->getHandCards().at(y_pos)->getType() == 
            Card::CardType::SPELL)
  {
    players[cur_player]->eraseSpellHandCard(y_pos);
  }

  players[cur_player]->addLifePoints(1);
}

//------------------------------------------------------------------------------
std::vector<std::string> Game::tokenizeStr(std::string input)
{
  std::istringstream iss(input);
  std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                  std::istream_iterator<std::string>{}};

  return tokens;
}

//------------------------------------------------------------------------------
bool Game::checkForShield(long x_pos) const
{
  for (size_t index = 0; index < Interface::NUM_OF_GAMEFIELD_CARDS; index++)
  {
    if (players[cur_player ^ 1]->getGameField()[index] != nullptr &&
        players[cur_player ^ 1]->getGameField()[index]->getShield())
    {
      if (x_pos == -1)
      {
        return true;
      }

      else if (players[cur_player ^ 1]->getGameField()[x_pos] != nullptr &&
               players[cur_player ^ 1]->getGameField()[x_pos]->getShield())
      {
        return false;
      }

      else
      {
        return true;
      }
    }
  }
  
  return false;
}

//------------------------------------------------------------------------------
bool Game::isDead()
{
  if (players[cur_player ^ 1]->getLifePoints() <= 0)
  {
    io_.out(Oop::Interface::OutputType::INFO, 
              Oop::Interface::ENDLINE_PART_ONE + players[cur_player]->getName()
               + Oop::Interface::ENDLINE_PART_TWO);
    return true;
  }

  return false;
}