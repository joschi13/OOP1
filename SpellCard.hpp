//------------------------------------------------------------------------------
// SpellCard.hpp
//
// Group: Group 9, study assistant David Kerschbaumer 
//
// Authors: Johannes Aigner 11907005
//------------------------------------------------------------------------------
//

#ifndef SPELLCARD_HPP
#define SPELLCARD_HPP

#include <string>
#include "Game.hpp"
#include "Card.hpp"

//------------------------------------------------------------------------------
namespace Oop
{
  class Card;
  class Game;

  enum SpellType {HEALER, RELIEF, REBIRTH, DRACULA};

  //----------------------------------------------------------------------------
  // SpellCard Class
  // This class defines a creature card and provides setter and getter methodes
  // 
  class SpellCard : public Card
  {
    private:

      SpellType spell_type_;

      //--------------------------------------------------------------------------
      // The Card constructor functions
      // determines Name/Mana Cost for a card with fixed values
      // 
      // @param spell type
      //
      // @return string/int name or mana cost of specific spell card
      //
      std::string determineName(SpellType type);
      int determineManaCosts(SpellType type);

    public:

      //--------------------------------------------------------------------------
      // Constructor
      //
      SpellCard(SpellType type);
      
      
      SpellCard(const SpellCard &temp);

      //--------------------------------------------------------------------------
      // Destructor
      //
      virtual ~SpellCard() noexcept;

      //--------------------------------------------------------------------------
      // The action function
      // Checks on the spell type and performs the spell
      // 
      // @param refernce of game
      //
      // @return bool true: performed false: not performed
      //
      bool action(Game& game);
      
  };
}

#endif    
