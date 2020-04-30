//------------------------------------------------------------------------------
// Player.hpp
//
// Authors: Martin Schachl 11907003
//
//------------------------------------------------------------------------------
//
#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>

//------------------------------------------------------------------------------
namespace Oop
{
	class CreatureCard;
	class SpellCard;
	class Card;
	
	//--------------------------------------------------------------------------
	// Player Class
	// This class provides an obj for storing all necessary player data.
	//
	class Player
	{
		private:

			std::string name_;
			int life_points_;
			int mana_points_;
			CreatureCard* game_field_ [7];
			std::vector<Card*> pick_up_stack_;
			std::vector<Card*> hand_;				//max size is missing! TODO
			std::vector<CreatureCard> graveyard_;

		public:

			//------------------------------------------------------------------
			// Standard constructor
			//
			Player();

			//------------------------------------------------------------------
			// Name constructor
			//
			Player(std::string name);

			//------------------------------------------------------------------
			// Destructor
			//
			~Player();
			
			//------------------------------------------------------------------
			// The getName function
			// Returns the name of the player
			//
			// @return string containing the name of the player
			//
			std::string getName() const;
			
			//------------------------------------------------------------------
			// The getLifePoints function
			// Returns the lifepoints of the player
			//
			// @return int containing the lifepoints of the player
			//
			int getLifePoints() const;
			
			//------------------------------------------------------------------
			// The addLifePoints function
			// Adding lifepoits to the players health
			//
			// @param int the lifepoits to add
			//
			void addLifePoints(int points);
			
			//------------------------------------------------------------------
			// The getManaPoints function
			// Returns the manapoints of the player
			//
			// @return int containing the manapoints of the player
			//
			int getManaPoints() const;
			
			//------------------------------------------------------------------
			// The addMana function
			// Adding manapoints to the players manapool
			// Max mana points = 15 so shoot over gets ignored
			//
			// @param int the mana to add
			//
			void addMana(int mana);
			
			//------------------------------------------------------------------
			// The reduceMana function
			// Reducing manapoints from the players manapool
			// Min mana points = 0 so shoot over gets ignored
			//
			// @param int the mana to reduce
			//
			void reduceMana(int mana);
			
			//------------------------------------------------------------------
			// The getHandCards function
			// Returning the cards of the player
			//
			// @return vector<Card*> containing the cards of the player
			//
			const std::vector<Card*> getHandCards() const;

			//------------------------------------------------------------------
			// The getHandSize function
			// Returning the number of cards from the player
			//
			// @return int containing the number of cards form the player
			//
			int getHandSize() const;

			//------------------------------------------------------------------
			// The getGameField function
			// Returning the gamefield
			//
			// @return CreatureCard* containing the gamefield
			//
			const CreatureCard* const* getGameField() const;

			//------------------------------------------------------------------
			// The copyPickUpStack function
			// Makes a deep copy of the original pick up stack
			//
			void copyPickUpStack(std::vector<Card*> &pick_up_stack);

			//------------------------------------------------------------------
			// The setName function
			// Sets the name of the player
			//
			void setName(std::string name);
			
			//------------------------------------------------------------------
			// The shufflePickUpStack function
			// shuffles the pick up stack with function of class Random
			//
			void shufflePickUpStack();
	};
	
}

#endif
