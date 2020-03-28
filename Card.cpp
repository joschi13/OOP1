#include "Card.hpp"

using Oop::Card;

std::string Card::getName() const
{
  return name_;
}

int Card::getManaCost() const
{
  return mana_cost_;
}

Card::CardType Card::getType() const
{
  return type_;
}