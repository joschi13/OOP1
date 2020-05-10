//------------------------------------------------------------------------------
// SpellCard.cpp
//
// Group: Group 9, study assistant David Kerschbaumer 
//
// Authors: Michael Zweimüller 		11916150
//			    Martin Schachl 		  	11907003
// 		    	Johannes Aigner		  	11907005
//------------------------------------------------------------------------------
//

#include <vector>
#include "SpellCard.hpp"
#include "CreatureCard.hpp"
#include "Interface.hpp"
#include "Player.hpp"

using Oop::Card;
using Oop::SpellCard;
using Oop::Game;

//------------------------------------------------------------------------------
SpellCard::SpellCard(SpellType type) : Card(determineName(type),
determineManaCosts(type), CardType::SPELL), spell_type_(type)
{
}

//------------------------------------------------------------------------------
SpellCard::SpellCard(const SpellCard &temp) : Card(temp),
spell_type_(temp.spell_type_)
{
}

//------------------------------------------------------------------------------
SpellCard::~SpellCard()
{
}

//------------------------------------------------------------------------------
std::string SpellCard::determineName(SpellType type)
{
  switch(type){
    case Oop::HEALER:
      return Interface::STRING_HEALER;

    case Oop::RELIEF:
      return Interface::STRING_RELIEF;

    case Oop::REBIRTH:
      return Interface::STRING_REBIRTH;

    case Oop::DRACULA:
      return Interface::STRING_DRACULA;

    case Oop::TRAITOR:
      return Interface::STRING_TRAITOR;
  }
}

//------------------------------------------------------------------------------
int SpellCard::determineManaCosts(SpellType type)
{
  switch(type){
    case Oop::HEALER:
      return 5;

    case Oop::RELIEF:
      return 3;

    case Oop::REBIRTH:
      return 5;

    case Oop::DRACULA:
      return 2;

    case Oop::TRAITOR:
      return 9;
  }
}

//------------------------------------------------------------------------------
bool SpellCard::action(Game& game)
{
  Player* player = game.getPlayer()[game.getCurPlayer()];
  Player* other_player = game.getPlayer()[game.getCurPlayer() ^ 1];
  Interface* io = game.getInterface();

  if(player->getManaPoints() < determineManaCosts(spell_type_))
  {
    io->out(Interface::INFO, Interface::WARNING_NOT_ENOUGH_MANA);
    return false;
  }

  player->reduceMana(determineManaCosts(spell_type_));

  switch(spell_type_){
    case Oop::HEALER:
      player->healCreatures();
      return true;

    case Oop::RELIEF:
      player->takeOffCards(3, 8);
      return true;

    case Oop::REBIRTH:
      if(!player->lastCreatureRebirth())
      {
        io->out(Interface::INFO, Interface::WARNING_REBIRTH_UNSUCCESSFUL);
      }
      return true;

    case Oop::DRACULA:
      other_player->reduceLifePoints(2);
      player->reduceLifePoints(-2);
      return true;
      
    case Oop::TRAITOR:
      int get_index = checkTraitorInput(other_player, 
        Interface::TARGET_TRAITOR_SPELL, false, game);
      if(get_index < 0)
      {
        break;
      } 

      int set_index = checkTraitorInput(player, 
        Interface::SET_TRAITOR_SPELL, true, game);
      if(set_index < 0)
      {
        break;
      }
      size_t get_idx = static_cast<size_t>(get_index);
      size_t set_idx = static_cast<size_t>(set_index);

      CreatureCard* creature = other_player->getGamefieldCreature(get_idx);
      if(!player->setCreatureControl(creature, set_idx))
      {
        break;
      }
      other_player->removeFromGameField(get_idx);
      
      return true;
  }
  
  player->reduceMana(-determineManaCosts(spell_type_));
  io->out(Interface::INFO, Interface::WARNING_EXECUTION_NOT_POSSIBLE);
  return false;
}

//------------------------------------------------------------------------------
int SpellCard::checkTraitorInput(Player* player, std::string msg, 
  bool empty_field, Game& game)
{
  int index = 0;
  Interface* io = game.getInterface();
  std::string input = io->askPlayer(msg);
  std::vector <std::string> input_vec = game.tokenizeStr(input);
  
  if(input.size() > 1)
  {
    return -1;
  }

  input = input_vec.at(0);

  try
  {
    index = std::stoi(input, nullptr, 10);
  }
  catch(const std::exception& e)
  {
    return -1;
  }
  
  if(!game.inBetween(index, 1, 7))
  {
    return -1;
  }
  index--;

  if(empty_field)
  {
    if(player->getGameField()[index] == nullptr)
    {
      return index;
    }
    else
    {
      return -1;
    }
  }
  else
  {
    if(player->getGameField()[index] != nullptr)
    {
      return index;
    }
    else
    {
      return -1;
    }
  }
        
  return true;
}