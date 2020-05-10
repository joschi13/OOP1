//------------------------------------------------------------------------------
// Player.hpp
//
// Group: Group 9, study assistant David Kerschbaumer 
//
// Authors: Michael Zweimüller 		11916150
//					Martin Schachl 				11907003
// 					Johannes Aigner				11907005
//------------------------------------------------------------------------------
//
#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include <string>
#include <vector>

//------------------------------------------------------------------------------
namespace Oop
{
	class CreatureCard;
	class SpellCard;
	class Card;
	class Interface;
	
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
			std::vector<Card*> hand_;
			std::vector<CreatureCard*> graveyard_;

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
      // Deleted copy constructor
      //
      Player(const Player& original) = delete;

      //------------------------------------------------------------------
      // Deleted assignment operator
      //
      Player& operator=(const Player& original) = delete;

			
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

			//------------------------------------------------------------------
			// The takeOffCards function
			// Taking off number of cards and adding to hand cards
			//
			// @param amount of taken cards and maximal hand size
			//
			void takeOffCards(int amount, int max_hand_size);
			
			//------------------------------------------------------------------
			// The setCardOnGameField function
			// Moving the cards from the hand to the playfield
			//
			// @param pos_hand position of card in the hand vector
			// @param pos_gamefield position where the card should go
			//
			bool setCardOnGameField(long pos_hand, long pos_gamefield);
			
			//------------------------------------------------------------------
			// The setAllFieldCardsRdy function
			// Setts rdy_to_attack and allready_attackt back so the card
			// can make a move in the round.
			//
			//
			void setAllFieldCardsRdy();

			//------------------------------------------------------------------
			// The setAllFieldShieldCardsRdy function
			// Makes sure shield cars can be attackt at the first round
			//
			//
			void setAllFieldShieldCardsRdy();
			
			//------------------------------------------------------------------
			// The reduceLifePoins function
			// is reucing the Lifepoints of the player by a given amount
			//
			// @param life_points amount how much lifepoins are getting removed
			//
			bool reduceLifePoints(int life_points);

			//------------------------------------------------------------------
			// The healCratures function
			// is healing the creatures for 1 Lp
			//
			void healCreatures();

			//------------------------------------------------------------------
			// The eraseSpellHandCard function
			// deletes a casted spellcard from the heap
			//
			// @param index postiton of the card that should be deleted
			//
			void eraseSpellHandCard(int index);

			//------------------------------------------------------------------
			// The getPickUpStackSize function
			// returns the size of the pickup stack
			//
			int getPickUpStackSize();
			
			//------------------------------------------------------------------
			// The damageMonster function
			// attacks monster on the playfield and checks if its dead
			//
			// @param damage amount of lp that sould get removed
			// @param pos_gamefield position of the monster that should get damaged
			//
			void damageMonsters(int damage, long pos_gamefield);
			
			//------------------------------------------------------------------
			// The setAlreadyAttacked function
			// is set the allready attacked function to true
			//
			// @param pos_gamefield position of the monster
			// 
			void setAlreadyAttacked(long pos_gamefield);

			//------------------------------------------------------------------
			// The moveToGraveyard function
			// moves a dead card to the graveyard
			//
			// @param pos_gamefield position of the monster
			// 			
			void moveToGraveyard(long pos_gamefield);

			//------------------------------------------------------------------
			// The lastCreatureRebirth function
			// is rebirthing a dead card from the graveyard
			// 			
			bool lastCreatureRebirth();

			//------------------------------------------------------------------
			// The removeFromGameField function
			// removes a card from the gamefield
			// 		
			// @param index position of the card that gets removed
			//
			void removeFromGameField(size_t index);

			//------------------------------------------------------------------
			// The setCreatureControl function
			// set a card to the gamefield
			// 		
			// @param index position where the card gets placed
			// @param creature that gets placed
			//
			bool setCreatureControl(CreatureCard* creature, size_t index);
			
			//------------------------------------------------------------------
			// The getGamefieldCreature function
			// returns the card on a certant spot
			// 		
			// @param index position of the card that gets returned
			//
			CreatureCard* getGamefieldCreature(size_t index);

	};
	
}

#endif
