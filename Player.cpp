//------------------------------------------------------------------------------
// Player.hpp
//
// Authors: Michael Zweimüller 		11916150
//			Martin Schachl 			11907003
// 			Johannes Aigner			11907005
//
//------------------------------------------------------------------------------
//
#include "Player.hpp"
#include "Card.hpp"
#include "SpellCard.hpp"
#include "CreatureCard.hpp"
#include "Random.hpp"
#include "Interface.hpp"

using Oop::Player;
using Oop::Card;
using Oop::CreatureCard;
using Oop::Interface;

Player::Player() : Player("")
{
}

//------------------------------------------------------------------------------
Player::Player(std::string name)
{
	name_ = name;
	life_points_ = 30;
	mana_points_ = 0;

	for(size_t i = 0; i < (sizeof(game_field_)/ sizeof(game_field_[0])); i++)
  {
    game_field_[i] = nullptr;
  }

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
	
	for (auto card : game_field_)
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
	name_ = name;
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
	while((amount > 0) && (pick_up_stack_.size() > 0) && (getHandSize() < 7))
	{
		hand_.push_back(pick_up_stack_.back());
		pick_up_stack_.pop_back();
		
		amount--;
	}
}



void Player::setCardOnGameField(long x, long y)
{
	game_field_[y] = dynamic_cast <CreatureCard *> (hand_.at(size_t(x)));
	hand_.erase(hand_.begin()+x);
	game_field_[y]->setReadyToFight(false);
}


void Player::setAllFieldCardsRdy()
{
  for(size_t temp = 0; temp < Interface::NUM_OF_GAMEFIELD_CARDS; temp++)
  {
    if(game_field_[temp] != nullptr)
    {
      game_field_[temp]->setReadyToFight(true);
      game_field_[temp]->setAlreadyAttacked(false);
    }
  }
}
  
bool Player::reduceLifePoints(int life_points)
{
  life_points_ = life_points_ - life_points;
  if(life_points_ <= 0)
  {
    return false;
  }
  return true;
}

