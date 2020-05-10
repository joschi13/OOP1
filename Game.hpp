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
  // The run function
  // Starts the game and quits when the game is finished or the user quits
  //
  void run();

  //------------------------------------------------------------------------
  // The playerCommandInput function
  // asking player for command and excecuting provided functions
  // @return true if command accepted, false if player enters quit
  bool playerCommandInput();

  //------------------------------------------------------------------------
  // The setupPlayer function
  // creating player, asking for names, shuffling pick up stacks
  //
  bool setupPlayer();

  //------------------------------------------------------------------------
  // The checkOnCreatureEquality function
  // checking for CREATURE card equality
  //
  bool checkOnCreatureEquality(Card *card);

  //------------------------------------------------------------------------
  // The inBetween function
  // @params x: searched value, lower and higher limit
  // @return true if in between - false if not
  //
  bool inBetween(int x, int low, int high);

  //------------------------------------------------------------------------
  // The getPlayer function
  // @return array of players
  //
  Player** getPlayer(){return players;}

  int getCurPlayer(){return cur_player;}

  Interface* getInterface(){return &io_;}

  //------------------------------------------------------------------------
  // The compareCommandInput function
  // checks for correctness of the user-input and handles error-messages
  // @params arguments: the user-input string tokenized in a vector
  // @params prep: the preposition which is needed for the attack and set 
  //                commands; if not needed -> any arbitrary string
  // @params x_min: the minimum value of X for the appropriate command
  //                if not needed -> 0
  // @params x_max: the maximum value of X for the appropriate command
  //                if not needed -> 0
  // @params y_min: the minimum value of Y for the appropriate command
  //                if not needed -> 0
  // @params y_max: the maximum value of Y for the appropriate command
  //                if not needed -> 0
  // @return true if the input was correct, false otherwise
  //
  bool compareCommandInput(std::vector<std::string> arguments, 
    std::string prep, int x_min, int x_max, int y_min, int y_max);

  //------------------------------------------------------------------------
  // The tokenizeStr function
  // @params input: the string which will be split by whitespaces into tokens 
  // @return vector of the tokenized input string
  //
  std::vector<std::string> tokenizeStr(std::string input);

  //------------------------------------------------------------------------
  // The checkParamCount function
  // checks if the number of parameters from the user-input matches with the 
  // requested one from the system.
  // @params command: a string with the relevant command for comparing the 
  //                  different number of needed parameters
  // @return true if the right number of parameters are given, else otherwise
  //
  unsigned long checkParamCount(std::string command);

  //------------------------------------------------------------------------
  // The checkRanges function
  // converts the numbers of the arguments vector to a size_t value, 
  // checks if it worked and returns true depending if the user-input was 
  // in the requested range
  // @params arguments: the user-input string tokenized in a vector
  // @params prep: the preposition which is needed for the attack and set 
  //                commands; if not needed -> any arbitrary string
  // @params x_min: the minimum value of X for the appropriate command
  //                if not needed -> 0
  // @params x_max: the maximum value of X for the appropriate command
  //                if not needed -> 0
  // @params y_min: the minimum value of Y for the appropriate command
  //                if not needed -> 0
  // @params y_max: the maximum value of Y for the appropriate command
  //                if not needed -> 0
  // @return true if the input was correct according to the given range,
  //         false otherwise
  //
  bool checkRanges(std::vector<std::string> arguments, std::string prep, 
    int x_min, int x_max, int y_min, int y_max);

  //------------------------------------------------------------------------
  // The executeAtt function
  // manages the execution of the attack command and handles error messaging
  // for cases that the compareCommandInput function is not handling
  // @params arguments: the user-input string tokenized in a vector 
  // @return true if the execution of the attack-command was successful
  //
  bool executeAtt(std::vector<std::string> arguments);

  //------------------------------------------------------------------------
  // The executeSet function
  // manages the execution of the set command and handles error messaging
  // for cases that the compareCommandInput function is not handling
  // @params arguments: the user-input string tokenized in a vector 
  // @return true if the execution of the set-command was successful
  //
  void executeSet(std::vector<std::string> arguments);

  //------------------------------------------------------------------------
  // The executeCast function
  // manages the execution of the cast command and handles error messaging
  // for cases that the compareCommandInput function is not handling
  // @params arguments: the user-input string tokenized in a vector 
  // @return true if the execution of the cast-command was successful
  //
  void executeCast(std::vector<std::string> arguments);

  //------------------------------------------------------------------------
  // The executeSet function
  // manages the execution of the sacrifice command and handles error 
  // messaging for cases that the compareCommandInput function is not handling
  // @params arguments: the user-input string tokenized in a vector 
  //
  void executeSac(std::vector<std::string> arguments);
  
  //------------------------------------------------------------------------
  // The checkForShield function
  // checks if any of the cards on the gamefield has a shield
  // @params x: the position on the enemy gamefield which will be attacked
  //            (-1 for attacking the player, 0-7)
  // @return true if any card on the enemy gamefield has a shield, 
  //         else otherwise
  //
  bool checkForShield(long x) const;

  //------------------------------------------------------------------------
  // The isDead function
  // checks if the enemy player has less or equal to zero lifepoints
  // 
  // @return true if the lifepoints are equal or less than zero, 
  //          else otherwise
  //
  bool isDead();

};
} 

#endif
