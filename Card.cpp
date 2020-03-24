#include "Card.hpp"

using Oop::Card;

std::string getName() const
{
  return name_;
}

int getManaCost() const
{
  return mana_cost_;
}

CardType getType() const
{
  return type_;
}    