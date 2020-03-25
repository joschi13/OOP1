//------------------------------------------------------------------------------
// Card.hpp
//
// Authors: Johannes Aigner
//
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
  // This class defines a game card and provides setter and getter methodes
  // for name, mana cost and type of card
  //

  

  class Card
  {
    

    public:

      enum CardType {CREATURE, SPELL};

      Card(std::string name, int mana_cost, CardType type)
      {
        name_ = name;
        mana_cost_ = mana_cost;
        type_ = type;
      }

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