//------------------------------------------------------------------------------
// Game.hpp
//
// Group: Group 9, study assistant David Kerschbaumer
//
// Authors: Michael Zweimüller 11916150
//------------------------------------------------------------------------------
//

#ifndef INCLUDE_GAME_H
#define INCLUDE_GAME_H

//------------------------------------------------------------------------------
namespace Oop
{
  class Interface;

  //----------------------------------------------------------------------------
  // Game Class
  // This class is responsible for loading the config-file, starting, 
  // administering and exiting the game.
  //
  class Game
  {
    private:

      Oop::Interface& io_;
    
    public:

      //--------------------------------------------------------------------------
      // Constructor
      //
      Game(Interface &io);
    
      //--------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Game() noexcept;

      //--------------------------------------------------------------------------
      // Deleted copy constructor
      //
      //Game(const Game& original) = delete;

      //------------------------------------------------------------------------
      // The loadConfig function
      // Loading the config-file and checks its validity
      // Ouptuts an error-message if the file is not valid
      // @param config_file the path to the config-file as a string
      // @return bool true for valid file, else false
      //
      bool loadConfig(std::string config_file);

      //------------------------------------------------------------------------
      // The run funciton
      // Starts the game and quits when the game is finished or the user quits
      //
      void run();
  };
}

#endif
