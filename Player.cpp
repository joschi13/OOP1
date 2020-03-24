#include "Player.hpp"
#include "Card.hpp"
#include "CreatureCard.hpp"

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

std::vector<Card*> Player::getHandCards() const
{
	return hand_;
}

int Player::getHandSize() const
{
	return hand_.size();
}

const CreatureCard** Player::getGameField()
{
	return game_field_;
}

