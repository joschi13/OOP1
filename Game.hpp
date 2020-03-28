//------------------------------------------------------------------------------
// Game.hpp
//
// Author: Michael Zweimüller
//
//------------------------------------------------------------------------------
//

#ifndef INCLUDE_GAME_H
#define INCLUDE_GAME_H

#include "Interface.hpp"

namespace Oop
{
  class Interface;

  class Game
  {
  private:

    Oop::Interface& io_;
    
  public:
    //------------------------------------------------------------------------
    // Constructor
    //
    Game(Interface &io);
    
    //------------------------------------------------------------------------
    // Destructor
    //
    //virtual ~Game() noexcept;

    //------------------------------------------------------------------------
    // Deleted copy constructor
    //
    //Game(const Game& original) = delete;

    bool loadConfig(std::string config_file);

    void run();
  };
  
}

#endif
