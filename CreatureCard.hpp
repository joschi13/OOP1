//------------------------------------------------------------------------------
// CreatureCard.hpp
//
// Authors: Johannes Aigner
//
//------------------------------------------------------------------------------
//

#ifndef CREATURECARD_HPP
#define CREATURECARD_HPP

#include <string>
#include "Card.hpp"

//------------------------------------------------------------------------------
namespace Oop
{
  //----------------------------------------------------------------------------
  // CreatureCard Class
  // This class defines a creature card and provides setter and getter methodes
  // 

  class Card;
  
  class CreatureCard : public Card
  {
    private:

      const int damage_points_;   // range 0-9
      const int life_points_;     // range 1-9      
      int current_life_points_;   // range 0-9      
      const bool shield_;
      bool mana_drain_;
      bool ready_to_fight_;
      bool already_attacked_;
      bool speedy_;

    public:

      CreatureCard(std::string name, int mana_cost, int damage_points, int life_points, bool shield, bool mana_drain, bool speedy) : \
      Card(name, mana_cost, CardType::CREATURE), damage_points_(damage_points), life_points_(life_points), shield_(shield)
      {
        mana_drain_ = mana_drain;
        ready_to_fight_ = false;
        already_attacked_ = false;
        speedy_ = false;
        
        //current_life_points_ = life_points;   /TODO
        //speedy_ = speedy; for bonus task (Deliverable 3)
      }

      int getLifePoints() const;

      int getDamagePoints() const;

      bool getManaDrain() const;

      bool getShield() const;

      int getCurrentLifePoints() const;

      bool getReadyToFight() const;

      bool getAlreadyAttacked() const;

      bool getSpeedy() const;
  };
}

#endif