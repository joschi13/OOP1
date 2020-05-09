//------------------------------------------------------------------------------
// SpellCard.cpp
//
// Group: Group 9, study assistant David Kerschbaumer 
//
// Authors: Michael Zweimüller 		11916150
//			Martin Schachl 			11907003
// 			Johannes Aigner			11907005
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
      
      CreatureCard* creature = other_player->getGamefieldCreature(0);
      if(!player->setCreatureControl(creature, 0))
      {
        player->reduceMana(-determineManaCosts(spell_type_));
        io->out(Interface::INFO, Interface::WARNING_EXECUTION_NOT_POSSIBLE);
        return false;
      }
      other_player->removeFromGameField(0);
      
      return true;
  }
  
  return false;
}