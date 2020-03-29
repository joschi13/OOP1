//------------------------------------------------------------------------------
// Card.hpp
//
// Group: Group 9, study assistant David Kerschbaumer 
//
// Authors: Johannes Aigner 11907005
//------------------------------------------------------------------------------
//

#ifndef CARD_HPP
#define CARD_HPP

#include <string>

//------------------------------------------------------------------------------
namespace Oop
{
  //----------------------------------------------------------------------------
  // Card Class
  // This class defines a game card and provides setter and getter methodes.
  //
  class Card
  {
    public:

      //------------------------------------------------------------------------
      // Enum for type of card
      //
      enum CardType {CREATURE, SPELL};

      //------------------------------------------------------------------------
      // Constructor
      //
      Card(std::string name, int mana_cost, CardType type);

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Card() noexcept;

      //------------------------------------------------------------------------
      // Getter Methods
      //
      std::string getName() const;

      int getManaCost() const;

      CardType getType() const;

    private:

      std::string name_;
      int mana_cost_;
      CardType type_;  
  };
}

#endif