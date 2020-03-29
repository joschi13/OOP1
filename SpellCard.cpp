//------------------------------------------------------------------------------
// SpellCard.cpp
//
// Group: Group 9, study assistant David Kerschbaumer 
//
// Authors: Johannes Aigner 11907005
//------------------------------------------------------------------------------
//

#include "SpellCard.hpp"

using Oop::Card;
using Oop::SpellCard;

//------------------------------------------------------------------------------
SpellCard::SpellCard(SpellType type) : Card(determineName(type), \
determineManaCosts(type), CardType::SPELL)
{
  spell_type_ = type;
}

//------------------------------------------------------------------------------
SpellCard::~SpellCard() noexcept
{
}

//------------------------------------------------------------------------------
std::string SpellCard::determineName(SpellType type)
{
  switch(type){
    case Oop::HEALER:
      return "Healer";

    case Oop::RELIEF:
      return "Relief";

    case Oop::REBIRTH:
      return "Rebirth";

    case Oop::DRACULA:
      return "Dracula";
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
  }
}

//------------------------------------------------------------------------------
bool SpellCard::action(Game& game)
{
  //TODO
  return false;
}