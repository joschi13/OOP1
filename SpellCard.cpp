//------------------------------------------------------------------------------
// SpellCard.cpp
//
// Group: Group 9, study assistant David Kerschbaumer 
//
// Authors: Johannes Aigner 11907005
//------------------------------------------------------------------------------
//

#include "SpellCard.hpp"
#include "Interface.hpp"

using Oop::Card;
using Oop::SpellCard;

//------------------------------------------------------------------------------
SpellCard::SpellCard(SpellType type) : Card(determineName(type), \
determineManaCosts(type), CardType::SPELL)
{
  spell_type_ = type;
}

//------------------------------------------------------------------------------
SpellCard::SpellCard(const SpellCard &temp) : Card(temp), \
spell_type_(temp.spell_type_)
{
	
	this->setName(temp.getName());
	this->setManaCost(temp.getManaCost());
	this->setType(temp.getType());
	
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
      return Interface::STRING_HEALER;

    case Oop::RELIEF:
      return Interface::STRING_RELIEF;

    case Oop::REBIRTH:
      return Interface::STRING_REBIRTH;

    case Oop::DRACULA:
      return Interface::STRING_DRACULA;
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
