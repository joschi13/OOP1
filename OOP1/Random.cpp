#include "Random.hpp"

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <algorithm>

using Oop::Random;

//------------------------------------------------------------------------------
unsigned int Random::getSeed()
{
  bool seed_valid = false;
  char *rand_seed_from_env = getenv("RAND_SEED");
  unsigned int seed = 0;
  if (rand_seed_from_env)
  {
    std::stringstream rand_seed_sstream(rand_seed_from_env);
    rand_seed_sstream >> seed;
    if (!rand_seed_sstream.eof() || rand_seed_sstream.bad())
    {
      seed_valid = false;
      std::cerr << "[WARN] could not parse seed for RNG from environment\n";
    }
    else
    {
      seed_valid = true;
    }
  }
  if (!seed_valid)
  {
    std::random_device rand_dev;
    seed = rand_dev();
  }
  return seed;
}

//------------------------------------------------------------------------------
Random& Random::getInstance()
{
	static Random instance;
	return instance;
}

//------------------------------------------------------------------------------
Random::Random() : mersenne_twister_(getSeed())
{
}

//------------------------------------------------------------------------------
void Random::shufflePickupstack(std::vector<Card*>& pick_up_stack)
{
  std::shuffle(std::begin(pick_up_stack), std::end(pick_up_stack),
      mersenne_twister_);
}