//------------------------------------------------------------------------------
// SpellCard.hpp
//
// Authors: Johannes Aigner
//
//------------------------------------------------------------------------------
//

#ifndef SPELLCARD_HPP
#define SPELLCARD_HPP

#include <string>
#include "Game.hpp"
//#include "Interface.hpp"
#include "Card.hpp"

//------------------------------------------------------------------------------
namespace Oop
{
  //----------------------------------------------------------------------------
  // SpellCard Class
  // This class defines a creature card and provides setter and getter methodes
  // 

  enum SpellType {HEALER, RELIEF, REBIRTH, DRACULA};

  class Card;
  class Game;
  
  class SpellCard : public Card
  {
    private:

      SpellType spell_type_;

      std::string determineName(SpellType type);
      int determineManaCosts(SpellType type);

    public:

      SpellCard(SpellType type) : Card(determineName(type), determineManaCosts(type), CardType::SPELL)
      {
        spell_type_ = type;
      }

      bool action(Game& game);
  };
}

#endif    