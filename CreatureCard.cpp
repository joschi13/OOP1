//------------------------------------------------------------------------------
// CreatureCard.cpp
//
// Group: Group 9, study assistant David Kerschbaumer 
//
// Authors: Michael Zweimüller 		11916150
//			Martin Schachl 			11907003
// 			Johannes Aigner			11907005
//------------------------------------------------------------------------------
//

#include "CreatureCard.hpp"

using Oop::Card;
using Oop::CreatureCard;

//------------------------------------------------------------------------------
CreatureCard::CreatureCard(std::string name, int mana_cost, int damage_points, 
  int life_points, bool shield, bool mana_drain, bool speedy) : 
    Card(name, mana_cost, CardType::CREATURE), 
      damage_points_(damage_points), 
      life_points_(life_points), 
      current_life_points_(life_points), 
      shield_(shield), 
      mana_drain_(mana_drain),
      ready_to_fight_(speedy ? true : false),
      already_attacked_(false),
      speedy_(speedy)
{
}

//------------------------------------------------------------------------------
CreatureCard::CreatureCard(const CreatureCard &temp) : Card(temp), 
  damage_points_(temp.getDamagePoints()), 
  life_points_(temp.getLifePoints()),
  current_life_points_(temp.getCurrentLifePoints()),
  shield_(temp.getShield()),
  mana_drain_(temp.getManaDrain()),
  ready_to_fight_(temp.getReadyToFight()),
  already_attacked_(temp.getAlreadyAttacked()),
  speedy_(temp.getSpeedy())
{
}

//------------------------------------------------------------------------------
CreatureCard::~CreatureCard()
{
}

//------------------------------------------------------------------------------
int CreatureCard::getLifePoints() const
{
  return life_points_;
}

//------------------------------------------------------------------------------
int CreatureCard::getDamagePoints() const
{
  return damage_points_;
}

//------------------------------------------------------------------------------
bool CreatureCard::getManaDrain() const
{
  return mana_drain_;
}

//------------------------------------------------------------------------------
bool CreatureCard::getShield() const
{
  return shield_;
}

//------------------------------------------------------------------------------
int CreatureCard::getCurrentLifePoints() const
{
  return current_life_points_;
}

//------------------------------------------------------------------------------
bool CreatureCard::getReadyToFight() const
{
  return ready_to_fight_;
}

//------------------------------------------------------------------------------
bool CreatureCard::getAlreadyAttacked() const
{
  return already_attacked_;
}

//------------------------------------------------------------------------------
bool CreatureCard::getSpeedy() const
{
  return speedy_;
}

//------------------------------------------------------------------------------
void CreatureCard::setAlreadyAttacked(bool ready)
{
  already_attacked_ = ready;
}

//------------------------------------------------------------------------------
void CreatureCard::setReadyToFight(bool ready)
{
  ready_to_fight_ = ready;
}

//------------------------------------------------------------------------------
void CreatureCard::reduceLifePoints(int amount)
{
  current_life_points_ = current_life_points_ - amount;

  if(current_life_points_ > 9)
  {
    current_life_points_ = 9;
  }
}

//------------------------------------------------------------------------------
void CreatureCard::resetAttributes()
{
  current_life_points_ = life_points_;
  ready_to_fight_ = speedy_ ? true : false;
  already_attacked_ = false;
}