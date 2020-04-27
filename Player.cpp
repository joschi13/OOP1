//------------------------------------------------------------------------------
// Player.hpp
//
// Authors: Martin Schachl 11907003
//
//------------------------------------------------------------------------------
//
#include "Player.hpp"
#include "Card.hpp"
#include "SpellCard.hpp"
#include "CreatureCard.hpp"
#include "Random.hpp"

using Oop::Player;
using Oop::Card;
using Oop::CreatureCard;

std::string Player::getName() const
{
	return Player::name_;
}

int Player::getLifePoints() const
{
	return life_points_;
}
void Player::addLifePoints(int points)
{
	life_points_ = life_points_ + points;
}

int Player::getManaPoints() const
{
	return mana_points_;
}

void Player::addMana(int mana)
{
	mana_points_ = mana_points_ + mana;
	if(mana_points_ > 15)
	{
		mana_points_ = 15;
	}
}

void Player::reduceMana(int mana)
{
	mana_points_ = mana_points_ - mana;
	if(mana_points_ < 0)
	{
	mana_points_ = 0; 
	}
}

const std::vector<Card*> Player::getHandCards() const
{
	return hand_;
}

int Player::getHandSize() const
{
	return hand_.size();
}

const CreatureCard* const* Player::getGameField() const
{
	return game_field_;
}

void Player::setCreatureCard(std::vector<Card*> pick_up_stack)
{
	//pick_up_stack_ = pick_up_stack;
	
	SpellCard *s_card = NULL;
	CreatureCard *c_card = NULL;
	
	for(Card* cur : pick_up_stack_)
	{
		s_card = dynamic_cast <SpellCard*>(cur);
		c_card = dynamic_cast <CreatureCard*>(cur);
		if(s_card != NULL)
		{
			pick_up_stack_.push_back(new SpellCard(*s_card));
			s_card = NULL;
		}
		if(c_card != NULL)
		{
			pick_up_stack_.push_back(new CreatureCard(*c_card));
			c_card = NULL;
		}
	}
}
void Player::setName(std::string name) 
{
	name_ =name;
}

void Player::shufflePickupstackCall()
{
	//Random &rand = Random::getInstance();
	//rand.shufflePickupstack(&pick_up_stack_);
}
