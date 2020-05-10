//------------------------------------------------------------------------------
// CreatureCard.hpp
//
// Group: Group 9, study assistant David Kerschbaumer 
//
// Authors: Michael Zweimüller 		11916150
//		    	Martin Schachl  			11907003
// 		    	Johannes Aigner		  	11907005
//------------------------------------------------------------------------------
//

#ifndef CREATURECARD_HPP
#define CREATURECARD_HPP

#include <string>
#include "Card.hpp"

//------------------------------------------------------------------------------
namespace Oop
{
  class Card;

  //----------------------------------------------------------------------------
  // CreatureCard Class
  // This class defines a creature card and provides setter and getter methodes
  // 
  class CreatureCard : public Card
  {
    private:

      const int damage_points_;  
      const int life_points_;          
      int current_life_points_;     
      const bool shield_;
      bool mana_drain_;
      bool ready_to_fight_;
      bool already_attacked_;
      bool speedy_;

    public:

      //------------------------------------------------------------------------
      // Constructor
      //
      CreatureCard(std::string name, int mana_cost, int damage_points,
      int life_points, bool shield, bool mana_drain, bool speedy);

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~CreatureCard();
      
      //------------------------------------------------------------------------
      // Copy constructor
      //      
      CreatureCard(const CreatureCard &temp);

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      CreatureCard& operator=(const CreatureCard& original) = delete;

      //------------------------------------------------------------------
			// The reduceLifePoints function
			// reducing life points by amount
			//
			void reduceLifePoints(int amount);
      
      //------------------------------------------------------------------
			// The resetAttributes function
			// resetting attributes current lifepoints, already attacked and
      // ready to fight
			//
      void resetAttributes();      
      
      //------------------------------------------------------------------------
      // Getter Methods
      //
      int getLifePoints() const;

      int getDamagePoints() const;

      bool getManaDrain() const;

      bool getShield() const;

      int getCurrentLifePoints() const;

      bool getReadyToFight() const;

      bool getAlreadyAttacked() const;
      
      bool getSpeedy() const;

      //------------------------------------------------------------------------
      // Setter Methods
      //
      void setAlreadyAttacked(bool ready);
      
      void setReadyToFight(bool ready);
  };
}

#endif
