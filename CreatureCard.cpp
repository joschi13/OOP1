//------------------------------------------------------------------------------
// CreatureCard.cpp
//
// Group: Group 9, study assistant David Kerschbaumer 
//
// Authors: Johannes Aigner 11907005
//------------------------------------------------------------------------------
//

#include "CreatureCard.hpp"

using Oop::Card;
using Oop::CreatureCard;

//------------------------------------------------------------------------------
CreatureCard::CreatureCard(std::string name, int mana_cost, int damage_points, \
int life_points, bool shield, bool mana_drain, bool speedy) : \
Card(name, mana_cost, CardType::CREATURE), damage_points_(damage_points), \
life_points_(life_points), shield_(shield)
{
  mana_drain_ = mana_drain;
  ready_to_fight_ = false;
  already_attacked_ = false;
  speedy_ = false;

  //TODO
  //current_life_points_ = life_points;
  //speedy_ = speedy; for bonus task (Deliverable 3)
}

CreatureCard::CreatureCard(const CreatureCard &temp) : Card(temp), \
damage_points_(temp.getDamagePoints()), life_points_(temp.getLifePoints()), \
shield_(temp.getShield())
{
	
	this->setName(temp.getName());
	this->setManaCost(temp.getManaCost());
	this->setType(temp.getType());
	
	this->current_life_points_ = temp.getCurrentLifePoints();
	this->mana_drain_ = temp.getManaDrain();
	this->ready_to_fight_ = temp.getReadyToFight();
	this->already_attacked_ = temp.getAlreadyAttacked();
	this->speedy_ = temp.getSpeedy();
	
}

//------------------------------------------------------------------------------
CreatureCard::~CreatureCard() noexcept
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
