#include "SpellCard.hpp"

using Oop::Card;
using Oop::SpellCard;

std::string SpellCard::determineName(SpellType type)
{
  switch(type){
    case Oop::HEALER:
      return "Healer";

    case Oop::RELIEF:
      return "Relief";

    case Oop::REBIRTH:
      return "Rebirth";

    case Oop::DRACULA:
      return "Dracula";
  }
}

int SpellCard::determineManaCosts(SpellType type)
{
  switch(type){
    case Oop::HEALER:
      return 5;

    case Oop::RELIEF:
      return 3;

    case Oop::REBIRTH:
      return 5;

    case Oop::DRACULA:
      return 2;
  }
}

bool SpellCard::action(Game& game)
{
  //TODO
  return false;
}