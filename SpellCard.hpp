//------------------------------------------------------------------------------
// SpellCard.hpp
//
// Group: Group 9, study assistant David Kerschbaumer 
//
// Authors: Michael Zweimüller 		11916150
//		    	Martin Schachl 		  	11907003
// 		    	Johannes Aigner		  	11907005
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

  //------------------------------------------------------------------------
  // Enum for all given spellcards
  //
  enum SpellType {HEALER, RELIEF, REBIRTH, DRACULA, TRAITOR};

  //----------------------------------------------------------------------------
  // SpellCard Class
  // This class defines a spell card, it's types and the function to cast it
  // 
  class SpellCard : public Card
  {
    private:

      SpellType spell_type_;

      //------------------------------------------------------------------------
      // The determine functions
      // determines Name/Mana Cost for a card with fixed values
      // 
      // @param spell type
      //
      // @return string/int name or mana cost of specific spell card
      //
      std::string determineName(SpellType type);
      
      int determineManaCosts(SpellType type);

      //------------------------------------------------------------------------
      // The checkTraitorInput functions
      // Traitor spell: asks for playerinput, checks on input
      // 
      // @param player to ask, message for output, 
      //        empty_field: true: check for nullptr false: check for creature,
      //        reference to game
      //
      // @return gamefield index,  -1 if not accepted
      //
      int checkTraitorInput(Player* player, std::string msg, 
        bool empty_field, Game& game);

    public:
      
      //------------------------------------------------------------------------
      // Constructor
      //
      SpellCard(SpellType type);

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~SpellCard();
      
      //------------------------------------------------------------------------
      // Copy constructor
      //  
      SpellCard(const SpellCard &temp);

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      SpellCard& operator=(const SpellCard& original) = delete;

      //------------------------------------------------------------------------
      // The action function
      // Checks on the spell type and performs the spell
      // 
      // @param refernce of game
      //
      // @return bool true: card needed to be deleted false: not needed
      //
      bool action(Game& game);
  };
}

#endif    
