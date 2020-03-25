



#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include <string>
#include <vector>
#include <map>
#include <functional>


namespace Oop
{

	class CreatureCard;
	class Card;

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

			//standard constr

			Player()
			{
				name_ = "";
				life_points_ = 30;
				mana_points_ = 0;
				//TODO stuff for the other attributs, depends on data struc 
			}

			//name constr

			Player(std::string name)
			{
				name_ = name;
				life_points_ = 30;
				mana_points_ = 0;
				//TODO stuff for the other attributs, depends on data struc
			}


			std::string getName() const;
			
			int getLifePoints() const;
			
			void addLifePoints(int points);
			
			int getManaPoints() const;
			
			void addMana(int mana);
			
			void reduceMana(int mana);
			
			const std::vector<Card*> getHandCards() const;

			int getHandSize() const;

			const CreatureCard* const* getGameField() const;

	};
	
}

#endif
