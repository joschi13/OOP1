//------------------------------------------------------------------------------
// Card.cpp
//
// Group: Group 9, study assistant David Kerschbaumer 
//
// Authors: Michael Zweimüller 		11916150
//			Martin Schachl 			11907003
// 			Johannes Aigner			11907005
//------------------------------------------------------------------------------
//

#include "Card.hpp"

using Oop::Card;

//------------------------------------------------------------------------------
Card::Card(std::string name, int mana_cost, CardType type) : 
name_(name), mana_cost_(mana_cost), type_(type)
{
}

//------------------------------------------------------------------------------
Card::Card(const Card& other) :
name_(other.getName()), mana_cost_(other.getManaCost()), type_(other.getType())
{
}

//------------------------------------------------------------------------------
Card::~Card() noexcept
{
}

//------------------------------------------------------------------------------
std::string Card::getName() const
{
  return name_;
}

//------------------------------------------------------------------------------
int Card::getManaCost() const
{
  return mana_cost_;
}

//------------------------------------------------------------------------------
Card::CardType Card::getType() const
{
  return type_;
}

//------------------------------------------------------------------------------
void Card::setName(std::string name)
{
	name_ = name;
}

//------------------------------------------------------------------------------
void Card::setManaCost(int mana_cost)
{
	mana_cost_ = mana_cost;
}

//------------------------------------------------------------------------------      
void Card::setType(CardType type)
{
	type_ = type;
}
