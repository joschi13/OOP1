//------------------------------------------------------------------------------
// Interface.cpp
//
// Authors: Tutors
//
//------------------------------------------------------------------------------
//

#include "Interface.hpp"
#include "Player.hpp"
#include "Card.hpp"
#include "CreatureCard.hpp"
#include "SpellCard.hpp"

#include <iostream>
#include <algorithm>
#include <iomanip>

using Oop::Interface;

//------------------------------------------------------------------------------
// static constants
const std::string Interface::ERROR_WRONG_ARGUMENTS 
  = "Usage: ./game <config-file>";
const std::string Interface::ERROR_INVALID_CONFIG = 
  "Invalid config file!";
const std::string Interface::ERROR_BAD_ALLOC = "Memory error!";

const std::string Interface::WARNING_INVALID_NAME = 
  "This name is not valid! Try a different one!";
const std::string Interface::WARNING_UNKNOWN_COMMAND = "Unknown command!";
const std::string Interface::WARNING_WRONG_PARAMETER = 
  "Invalid command parameter!";
const std::string Interface::WARNING_WRONG_PARAM_COUNT =
	"Wrong parameter count!";
const std::string Interface::WARNING_NOT_ENOUGH_MANA = 
  "Not enough mana for this move!";
const std::string Interface::WARNING_EXECUTION_NOT_POSSIBLE = 
  "Execution not possible!";
const std::string Interface::WARNING_SHIELD_MONSTER = 
  "Destroy all shields first!";
const std::string Interface::WARNING_REBIRTH_UNSUCCESSFUL =
	"Rebirth unsuccessful!";

const std::vector<std::string> Interface::INFO_HELP_MSGS =
{
  "Available Commands:",
  "- Attack <x> with <y>",
  "    Attack position x on the enemy side with creature at position y on your side.",
  "    The value x is the position of the victim [0=enemy, 1-7=enemy card]",
  "    The value y is the position of your monster on the gamefield [1-7=enemy card]",
  "- Set <x> to <y>",
  "    Place creature card with number x in hand at position y on your side.",
  "    The value x and y has to be between 1 and 7.",
  "- Cast <x>",
  "    Cast spell from the card on gamefield index x.",
  "    The value x has to be between 1 and 7.",
  "- Sacrifice <x>",
  "    Sacrifice hand card with index x and gain +1 health in exchange.",
  "    The value x has to be between 1 and 7.",
  "- State",
  "    Prints the current game",
  "- Finish",
  "    End your turn.",
  "- Quit",
  "    Terminates the game, which leads to the winning of the opponent player!",
  "- Help",
  "    Display this help."
};

const std::string Interface::PLAYER_1_NAME = 
  "Please enter the name of player 1: ";
const std::string Interface::PLAYER_2_NAME = 
  "Please enter the name of player 2: ";
const std::string Interface::TARGET_TRAITOR_SPELL = 
  "Please enter the target creature: ";
const std::string Interface::SET_TRAITOR_SPELL = 
  "Please enter where you would like to set the creature: ";

const std::string Interface::COMMAND_HELP = "help";
const std::string Interface::COMMAND_ATTACK = "attack";
const std::string Interface::COMMAND_SET = "set";
const std::string Interface::COMMAND_CAST = "cast";
const std::string Interface::COMMAND_SACRIFICE = "sacrifice";
const std::string Interface::COMMAND_STATE = "state";
const std::string Interface::COMMAND_FINISH = "finish";
const std::string Interface::COMMAND_QUIT = "quit";

const std::string Interface::INFO_ROUND = "Round: ";
const std::string Interface::INFO_CURRENT_PLAYER = "Current player is ";

const std::string Interface::ENDLINE_PART_ONE = "Game ended. Player ";
const std::string Interface::ENDLINE_PART_TWO = " won!";

const std::string Interface::STRING_HEALER = "Healer";
const std::string Interface::STRING_REBIRTH = "Rebirth";
const std::string Interface::STRING_DRACULA = "Dracula";
const std::string Interface::STRING_RELIEF = "Relief";
const std::string Interface::STRING_TRAITOR = "Traitor"; // BONUS

const std::map<const Interface::OutputType, const std::string>
  Interface::PROTOCOL =
{
  {DEBUG, "[DEBUG]"},
  {ERROR, "[ERROR]"},
  {WARNING, "[WARNING]"},
  {INFO, "[INFO]"},
};

const std::map<const Interface::OutputType, const std::string>
  Interface::COLOR_TEXT =
{
  {DEBUG, "\033[34m"}, //BLUE
  {ERROR, "\033[31m"}, //RED
  {WARNING, "\033[33m"}, //YELLOW
  {INFO, "\033[37m"}, //WHITE
};

const std::string Interface::COLOR_END = "\033[0m";

const std::string Interface::MAP_GAME = " GAME ";
const std::string Interface::MAP_HAND = " HAND ";
const std::string Interface::MAP_SEPERATOR = "\n=============================="
  "====================================================\n";
const std::string Interface::MIDFIELD_SEPERATOR = "\n~~~~~~ 01 ~~~~~~~ 02 ~~~~"
  "~~~ 03 ~~~~~~~ 04 ~~~~~~~ 05 ~~~~~~~ 06 ~~~~~~~ 07 ~~~~~~\n";
const std::string Interface::CARD_SEPERATOR = "   ";
const std::string Interface::PLAYER_PADDING = "=============================";
const std::vector<std::string> Interface::CARD_EMTPY = 
{
  " ______ ",
  "|      |",
  "|      |",
  "|      |",
  "|      |",
  "|______|"
};

const int Interface::MAX_NAME_LENGTH = 8;
const int Interface::MIN_LETTERS_NAME = 1;
const int Interface::MAX_LETTERS_NAME = 20;

const int Interface::MAX_MANA = 15;
const int Interface::MAX_MANA_GAIN = 8;

const int Interface::MAX_HAND_CARDS = 7;
const int Interface::NUM_OF_BOARD_LINES = 6;

//------------------------------------------------------------------------------
Interface::Interface()
{
}

//------------------------------------------------------------------------------
Interface::~Interface() noexcept
{
}

//------------------------------------------------------------------------------
void Interface::out(const OutputType type, const std::string msg) const
{
  std::cout << PROTOCOL.at(type) + " " + msg << std::endl;
}

//------------------------------------------------------------------------------
void Interface::out(const Oop::Player* current_player, 
                    const Oop::Player* opponent_player) const
{
  std::cout << MAP_SEPERATOR << std::endl;

  // Enemy Hand and Gamefield
  printHandCards(opponent_player, false);
  printPlayerInfo(opponent_player);
  printGamefieldCards(opponent_player);

  std::cout << MIDFIELD_SEPERATOR << std::endl;

  // Player Gamefield and Hand
  printGamefieldCards(current_player);
  printPlayerInfo(current_player);
  printHandCards(current_player, true);

  std::cout << MAP_SEPERATOR << std::endl;
}

//------------------------------------------------------------------------------
void Interface::printHandCards(const Oop::Player* player, bool show_hand_cards)
{
  std::vector<std::string> board;
  for (size_t index = 0; index < NUM_OF_BOARD_LINES; index++) 
  {
    std::string line;
    line += MAP_HAND.at(index);
    board.push_back(line);
  }

  // collect all data
  const std::vector<Card*> hand_cards = player->getHandCards();
  for (auto card : hand_cards)
  {
    if (card != nullptr && show_hand_cards)
    {
      bool mana_drain = false;
      bool shield = false;
      bool speedy = false;
      int mana_costs = card->getManaCost(); // 1..15
      int life_points = 0; // 0..9
      int damage_points = 0; // 0..9
      if (card->getType() == Card::CardType::CREATURE)
      {
        mana_drain = static_cast<CreatureCard*>(card)->getManaDrain();
        shield = static_cast<CreatureCard*>(card)->getShield();
        speedy = static_cast<CreatureCard*>(card)->getSpeedy();
        life_points = static_cast<CreatureCard*>(card)->getCurrentLifePoints();
        damage_points = static_cast<CreatureCard*>(card)->getDamagePoints();
      }

      std::string card_modifier = "";
      card_modifier += (mana_drain) ? "M" : "";
      card_modifier += (shield) ? "S" : "";
      card_modifier += (speedy) ? "A" : "";
      if (card_modifier.length() == 0)
      {
        card_modifier = "__ ";
      }
      else if (card_modifier.length() == 1)
      {
        card_modifier = "__" + card_modifier;
      }
      else if (card_modifier.length() == 2)
      {
        card_modifier = "_" + card_modifier;
      }

      board.at(0) += CARD_SEPERATOR + getAsStringWithPad(mana_costs) + "___" 
                     + card_modifier;
      board.at(1) += CARD_SEPERATOR + "|      |";
      board.at(2) += CARD_SEPERATOR + card->getName()
                     + std::string(8 - card->getName().length(), ' ');
      board.at(3) += CARD_SEPERATOR + "|      |";
      board.at(4) += CARD_SEPERATOR + "|      |";
      board.at(5) += CARD_SEPERATOR 
                     + (card->getType() == Card::CardType::CREATURE ? 
                     getAsStringWithPad(damage_points) : "x_") + "____"
                     + (card->getType() == Card::CardType::CREATURE ? 
                     getAsStringWithPad(life_points) : "_x");
    }
    else
    {
      for (size_t index = 0; index < board.size(); index++) 
      {
        board.at(index) += CARD_SEPERATOR + CARD_EMTPY.at(index);
      }
    }
  }

  int hand_size = player->getHandSize();
  for (int count = hand_size; count < NUM_OF_GAMEFIELD_CARDS; count++)
  {
    for (unsigned long index = 0; index < NUM_OF_BOARD_LINES; index++)
    {
      board.at(index) += CARD_SEPERATOR + "        ";
    }
  }

  // print cards
  for (size_t index = 0; index < board.size(); index++) 
  {
    std::cout << board.at(index) << CARD_SEPERATOR << MAP_HAND.at(index) 
              << std::endl;
  }
}

//------------------------------------------------------------------------------
void Interface::printPlayerInfo(const Oop::Player* player)
{
  int life_points = player->getLifePoints();
  int mana_points = player->getManaPoints();

  std::cout << std::endl << PLAYER_PADDING << " LP : " << std::setw(2) 
            << life_points << " | MANA : " << std::setw(2) << mana_points
            << "/15 " << PLAYER_PADDING << std::endl << std::endl;
}

//------------------------------------------------------------------------------
void Interface::printGamefieldCards(const Oop::Player* player)
{
  std::vector<std::string> board;
  for (size_t index = 0; index < NUM_OF_BOARD_LINES; index++) 
  {
    std::string line;
    line += MAP_GAME.at(index);
    board.push_back(line);
  }

  // collect all data
  auto game_field = player->getGameField();
  for (size_t index = 0; index < NUM_OF_GAMEFIELD_CARDS; index++)
  {
    const Oop::CreatureCard* card = game_field[index];
    if (card != nullptr)
    {
      int damage_points = card->getDamagePoints(); // 0..9
      int life_points = card->getCurrentLifePoints(); // 0..9
      bool shield = card->getShield();
      bool mana_drain = card->getManaDrain();

      std::string card_modifier = "";
      card_modifier += (mana_drain) ? "M" : "";
      card_modifier += (shield) ? "S" : "";
      if (card_modifier.length() == 0)
      {
        card_modifier = "_ ";
      }
      else if (card_modifier.length() == 1)
      {
        card_modifier = "_" + card_modifier;
      }

      std::string ready_string = "  ";
      if (!card->getReadyToFight())
      {
        ready_string = "zz";
      }
      else if (card->getAlreadyAttacked())
      {
        ready_string = "==";
      }

      board.at(0) += CARD_SEPERATOR + " _____" + card_modifier;
      board.at(1) += CARD_SEPERATOR + "|      |";
      board.at(2) += CARD_SEPERATOR + card->getName()
                     + std::string(8 - card->getName().length(), ' ');
      board.at(3) += CARD_SEPERATOR + "|  " + ready_string + "  |";
      board.at(4) += CARD_SEPERATOR + "|      |";
      board.at(5) += CARD_SEPERATOR + getAsStringWithPad(damage_points) 
                     + "____" + getAsStringWithPad(life_points);
    }
    else
    {
      // there is no card on that position
      for (unsigned long line = 0; line < NUM_OF_BOARD_LINES; line++)
      {
        board.at(line) += CARD_SEPERATOR + "        ";
      }
    }
  }

  // print cards
  for (size_t index = 0; index < board.size(); index++) 
  {
    std::cout << board.at(index) << CARD_SEPERATOR << MAP_GAME.at(index) 
              << std::endl;
  }
}

//------------------------------------------------------------------------------
std::string Interface::getAsStringWithPad(int value) 
{ 
  return (std::string(2 - std::to_string(value).length(), '0') + 
    std::to_string(value));
}

//------------------------------------------------------------------------------
std::string Interface::in() const
{
  std::string input_string;
  std::getline(std::cin, input_string);
  if(std::cin.eof())
  {
    input_string = Interface::COMMAND_QUIT;
  }
  return input_string;
}

//------------------------------------------------------------------------------
std::string Interface::readPlayerName(bool player)
{
  std::string player_name;
  while(1)
  {
    player_name = askPlayer(INFO, 
      ((player) ? (PLAYER_2_NAME) : (PLAYER_1_NAME)));
    if(player_name.length() >= MIN_LETTERS_NAME 
       && player_name.length() <= MAX_LETTERS_NAME)
    {
      return player_name;
    }
    out(WARNING, WARNING_INVALID_NAME);
  }
}

//------------------------------------------------------------------------------
std::string Interface::askPlayer(const std::string msg)
{
  std::string answer;
  std::cout << msg;
  answer = in();
  return answer;
}

//------------------------------------------------------------------------------
std::string Interface::askPlayer(const OutputType type, const std::string msg) 
{
  std::string answer;
  std::cout << PROTOCOL.at(type) + " " + msg;
  answer = in();
  return answer;
}

//------------------------------------------------------------------------------
void Interface::printCommandPrompt(const std::string player_name)
{
  std::cout << player_name << " > " << std::flush;
}

//------------------------------------------------------------------------------
void Interface::log(const std::string msg) const
{
  #ifndef RELEASE
    out(DEBUG, msg);
  #endif
}

//------------------------------------------------------------------------------
void Interface::error(const std::string msg)
{
  std::cout << PROTOCOL.at(ERROR) << " " << msg << std::endl;
}