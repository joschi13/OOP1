//------------------------------------------------------------------------------
// Random.hpp
//
// Authors: Tutors
//------------------------------------------------------------------------------

#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <vector>

namespace Oop
{
  class Card;

  //----------------------------------------------------------------------------
  // Random class
  // creates a random order for the Cards on the pickupstack
  class Random final
  {
  private:
    std::mt19937 mersenne_twister_;

    //--------------------------------------------------------------------------
    // returns an integer suitable to seed the random number generator
    //
    static unsigned int getSeed();

		//--------------------------------------------------------------------------
		// Constructor of Random Class is private, only getInstance possible
		//
		Random();


  public:

		//--------------------------------------------------------------------------
		// singleton pattern returns Instance of Random class
		//
  	static Random& getInstance();

    //--------------------------------------------------------------------------
    // deleted copy constructor
    //
    Random(const Random& other) = delete;

    //--------------------------------------------------------------------------
    // deleted assignment operator
    //
    Random& operator=(const Random& rhs) = delete;

    //--------------------------------------------------------------------------
    // shuffles the pickupstack
    //
    void shufflePickupstack(std::vector<Card*>& pick_up_stack);
  };
}

#endif