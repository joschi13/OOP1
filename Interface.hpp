//------------------------------------------------------------------------------
// Interface.h
//
// Authors: Tutors
//
//------------------------------------------------------------------------------
//

#ifndef INCLUDE_INTERFACE_H
#define INCLUDE_INTERFACE_H

#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>

//------------------------------------------------------------------------------
namespace Oop
{
  class Player;
  class CreatureCard;

  //----------------------------------------------------------------------------
  // Interface Class
  // This class provides an API to either use the Web-GUI or
  // the command-line-interface
  //
  class Interface
  {
    private:

      const static std::string MAP_GAME;
      const static std::string MAP_HAND;
      const static std::string MAP_SEPERATOR;
      const static std::string MIDFIELD_SEPERATOR;
      const static std::string CARD_SEPERATOR;
      const static std::string PLAYER_PADDING;
      const static std::vector<std::string> CARD_EMTPY;

      static void printHandCards(const Oop::Player* player, bool show_hand_cards);
      static void printPlayerInfo(const Oop::Player* player);
      static void printGamefieldCards(const Oop::Player* player);
      static std::string getAsStringWithPad(int value);

    public:

      //------------------------------------------------------------------------
      // Standard constructor
      //
      Interface();

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Interface() noexcept;

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Interface(const Interface& original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      Interface& operator=(const Interface& original) = delete;

      //------------------------------------------------------------------------
      // Enumeration of all supported output formats
      //
      enum OutputType {DEBUG, ERROR, WARNING, INFO};

      //------------------------------------------------------------------------
      // Constants
      // "All" strings required for the desired outputs (to minimize typos)
      //
      // OutputType: ERROR
      const static std::string ERROR_WRONG_ARGUMENTS;
      const static std::string ERROR_INVALID_CONFIG;
      const static std::string ERROR_BAD_ALLOC;
      const static std::string ERROR_FRAMEWORK;

      // OutputType: WARNING
      const static std::string WARNING_INVALID_NAME;
      const static std::string WARNING_UNKNOWN_COMMAND;
      const static std::string WARNING_WRONG_PARAMETER;
      const static std::string WARNING_WRONG_PARAM_COUNT;
      const static std::string WARNING_NOT_ENOUGH_MANA;
      const static std::string WARNING_EXECUTION_NOT_POSSIBLE;
      const static std::string WARNING_SHIELD_MONSTER;
			const static std::string WARNING_REBIRTH_UNSUCCESSFUL;

      // OutputType: INFO
      const static std::string PLAYER_1_NAME;
      const static std::string PLAYER_2_NAME;
      const static std::vector<std::string> INFO_HELP_MSGS;
      const static std::string TARGET_TRAITOR_SPELL;
      const static std::string SET_TRAITOR_SPELL;

      // command types
      const static std::string COMMAND_HELP;
      const static std::string COMMAND_ATTACK;
      const static std::string COMMAND_SET;
      const static std::string COMMAND_CAST;
      const static std::string COMMAND_SACRIFICE;
      const static std::string COMMAND_STATE;
      const static std::string COMMAND_FINISH;
      const static std::string COMMAND_QUIT;

      // spell cards strings and others
      const static std::string INFO_ROUND;
      const static std::string INFO_CURRENT_PLAYER;

      const static std::string ENDLINE_PART_ONE;
      const static std::string ENDLINE_PART_TWO;

      const static std::string STRING_HEALER;
      const static std::string STRING_REBIRTH;
      const static std::string STRING_DRACULA;
      const static std::string STRING_RELIEF;
      const static std::string STRING_TRAITOR;

      // protocol types and there colors
      const static std::map<const OutputType, const std::string> PROTOCOL;
      const static std::map<const OutputType, const std::string> COLOR_TEXT;
      const static std::string COLOR_END;

      // fixed values throughout the game
      const static int MAX_NAME_LENGTH;
      const static int MIN_LETTERS_NAME;
      const static int MAX_LETTERS_NAME;

      const static int MAX_MANA;
      const static int MAX_MANA_GAIN;

      const static int MAX_HAND_CARDS;
      const static int NUM_OF_BOARD_LINES;
      const static int NUM_OF_GAMEFIELD_CARDS = 7;

      //------------------------------------------------------------------------
      // The in funciton
      // Getting the user input from the chosen interface
      // Should be used instead of std::cin
      // @return std::string one line of input
      //
      std::string in() const;

      //------------------------------------------------------------------------
      // The out funciton
      // Writes an output to the chosen interface
      // Should be used instead of std::cout
      // @param type the output type of the message
      // @param msg the actual message to print
      //
      void out(const OutputType type, const std::string msg) const;

      //------------------------------------------------------------------------
      // The gamefield-out function
      // Writes the current gamefield to the chosen Interface
      //
      // @param the current player 
      // @param the opponent of the current player
      //
      void out(const Player* current_player, const Player* opponent_player) const;


      //------------------------------------------------------------------------
      // The read Player Name function
      // Asks the Player to choose a name and reads the following input.
      //
      // @param bool the player ID (0/1)
      //
      // @return string containing the name of the player
      //
      std::string readPlayerName(bool player);

      //------------------------------------------------------------------------
      // The ask Player function
      // Prints the message on the screen without \n at the end and returns the 
      // input
      //
      // @return string containing the answer
      //
      std::string askPlayer(const std::string msg);

      //------------------------------------------------------------------------
      // The ask Player function
      // Prints the message with output type on the screen without \n at the end
      // and returns the input
      //
      // @return string containing the answer
      //
      std::string askPlayer(const OutputType type, const std::string msg);

      //------------------------------------------------------------------------
      // The print command prompt function
      // Prints the name of the current player as command prompt
      //
      // @param player_name the name of the current player
      //
      void printCommandPrompt(const std::string player_name);

      //------------------------------------------------------------------------
      // The log function
      // Writes debug messages to the chosen interface
      // (Automatically disabled in RELEASE mode)
      // @param msg the debug message to be printed
      //
      void log(const std::string msg) const;

      //------------------------------------------------------------------------
      // The error functions
      // Prints error messages to the chosen interface.
      // Must only be used before ending the game with an error
      // @param msg the error message to be printed
      //
      void error(const std::string msg);
  };
}

#endif
