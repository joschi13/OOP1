//------------------------------------------------------------------------------
// Game.hpp
//
// Group: Group 9, study assistant David Kerschbaumer
//
// Authors: Michael Zweimüller 		11916150
//			Martin Schachl 			11907003
// 			Johannes Aigner			11907005
//------------------------------------------------------------------------------
//

#ifndef INCLUDE_GAME_H
#define INCLUDE_GAME_H

#include <vector>

//------------------------------------------------------------------------------
namespace Oop
{
class Interface;
class Card;
class Player;

//----------------------------------------------------------------------------
// Game Class
// This class is responsible for loading the config-file, starting,
// administering and exiting the game.
//
class Game
{
private:
  Oop::Interface &io_;

  std::vector<Card *> pick_up_stack;

  Player *players[2];

  int cur_player;

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
  Game(const Game &original) = delete;

  //------------------------------------------------------------------------
  // Deleted assignment operator
  //
  Game &operator = (const Game &original) = delete;

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

  //------------------------------------------------------------------------
  // The playerCommandInput funciton
  // asking player for command and excecuting provided functions
  // @return true if command accepted, false if player enters quit
  bool playerCommandInput();

  //------------------------------------------------------------------------
  // The setupPlayer funciton
  // creating player, asking for names, shuffling pick up stacks
  //
  bool setupPlayer();

  //------------------------------------------------------------------------
  // The checkOnCreatureEquality funciton
  // checking for CREATURE card equality
  //
  bool checkOnCreatureEquality(Card *card);

  //------------------------------------------------------------------------
  // The inBetween funciton
  // @params x: searched value, lower and higher limit
  // @return true if in between - false if not
  //
  bool inBetween(int x, int low, int high);

  //------------------------------------------------------------------------
  // The getCurPlayer funciton
  // @return index of current player
  //
  int getCurPlayer() const;



  // TODO coments d3
  bool compareCommandInput(std::vector<std::string> arguments, 
    std::string prep, int x_min, int x_max, int y_min, int y_max);

  std::vector<std::string> tokenizeStr(std::string input);

  unsigned long checkParamCount(std::string command);

  bool checkRanges(std::vector<std::string> arguments, std::string prep, 
    int x_min, int x_max, int y_min, int y_max);

  bool executeAtt(std::vector<std::string> arguments);

  bool executeSet(std::vector<std::string> arguments);
};
} 

#endif
