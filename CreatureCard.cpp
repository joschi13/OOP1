#include "CreatureCard.hpp"

using Oop::Card;
using Oop::CreatureCard;

int CreatureCard::getLifePoints() const
{
  return life_points_;
}

int CreatureCard::getDamagePoints() const
{
  return damage_points_;
}

bool CreatureCard::getManaDrain() const
{
  return mana_drain_;
}

bool CreatureCard::getShield() const
{
  return shield_;
}

int CreatureCard::getCurrentLifePoints() const
{
  return current_life_points_;
}

bool CreatureCard::getReadyToFight() const
{
  return ready_to_fight_;
}

bool CreatureCard::getAlreadyAttacked() const
{
  return already_attacked_;
}

bool CreatureCard::getSpeedy() const
{
  return speedy_;
}