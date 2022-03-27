// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

// Strategy is to intercept the attacker in the last column
direction_t def_directions[] =  {
  DIR_STAY,
  DIR_UP,
  DIR_DOWN
};


direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {
  // TODO: unused parameters, remove these lines later
  srand(time(NULL));
  static int lucky_number = 0;

  direction_t new_position;
  int dir;

  dir = lucky_number % 3;
  lucky_number = (lucky_number % 10) + rand();

  new_position = def_directions[dir];
  
  // strategy doesn't consider spy use and being stuck
  UNUSED(defender_position);
  UNUSED(attacker_spy);

  return new_position;
}

/*----------------------------------------------------------------------------*/
