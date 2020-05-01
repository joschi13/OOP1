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

Player::Player()
{
	name_ = "";
	life_points_ = 30;
	mana_points_ = 0;

	for(auto card : game_field_)
	{
		card = nullptr;
	}
	
	//TODO stuff for the other attributs, depends on data struc 
}

//------------------------------------------------------------------------------
Player::Player(std::string name)
{
	name_ = name;
	life_points_ = 30;
	mana_points_ = 0;

	for(auto card : game_field_)
	{
		card = nullptr;
	}
	//TODO stuff for the other attributs, depends on data struc
}

//------------------------------------------------------------------------------
Player::~Player()
{
	for(auto card : pick_up_stack_)
	{
		delete card;
	}

	for(auto card : hand_)
	{
		delete card;
	}
}

//------------------------------------------------------------------------------
std::string Player::getName() const
{
	return Player::name_;
}

//------------------------------------------------------------------------------
int Player::getLifePoints() const
{
	return life_points_;
}

//------------------------------------------------------------------------------
void Player::addLifePoints(int points)
{
	life_points_ = life_points_ + points;
}

//------------------------------------------------------------------------------
int Player::getManaPoints() const
{
	return mana_points_;
}

//------------------------------------------------------------------------------
void Player::addMana(int mana)
{
	mana_points_ = mana_points_ + mana;
	if(mana_points_ > 15)
	{
		mana_points_ = 15;
	}
}

//------------------------------------------------------------------------------
void Player::reduceMana(int mana)
{
	mana_points_ = mana_points_ - mana;
	if(mana_points_ < 0)
	{
	mana_points_ = 0; 
	}
}

//------------------------------------------------------------------------------
const std::vector<Card*> Player::getHandCards() const
{
	return hand_;
}

//------------------------------------------------------------------------------
int Player::getHandSize() const
{
	return hand_.size();
}

//------------------------------------------------------------------------------
const CreatureCard* const* Player::getGameField() const
{
	return game_field_;
}

//------------------------------------------------------------------------------
void Player::copyPickUpStack(std::vector<Card*> &pick_up_stack)
{
	SpellCard *s_card = NULL;
	CreatureCard *c_card = NULL;
	
	for(Card* cur_card : pick_up_stack)
	{
		if(cur_card->getType() == Card::CardType::SPELL)
		{
			s_card = dynamic_cast <SpellCard*>(cur_card);
			pick_up_stack_.push_back(new SpellCard(*s_card));
		}

		if(cur_card->getType() == Card::CardType::CREATURE)
		{
			c_card = dynamic_cast <CreatureCard*>(cur_card);
			pick_up_stack_.push_back(new CreatureCard(*c_card));
		}
	}
}

//------------------------------------------------------------------------------
void Player::setName(std::string name) 
{
	name_ =name;
}

//------------------------------------------------------------------------------
void Player::shufflePickUpStack()
{
	Random &rand = Random::getInstance();
	rand.shufflePickupstack(pick_up_stack_);
}

//------------------------------------------------------------------------------
void Player::takeOffCards(int amount)
{
	while((amount > 0) && (pick_up_stack_.size() > 0))
	{
		hand_.push_back(pick_up_stack_.back());
		pick_up_stack_.pop_back();
	}
}
