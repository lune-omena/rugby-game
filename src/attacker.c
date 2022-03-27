// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter
#define LOCK_STRATEGY 3 // number of round to get stuck and to leave stuck

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

// Strategy is randomly walk to the last column
direction_t atk_directions[] =  {
  DIR_STAY,
  DIR_UP,
  DIR_UP_RIGHT,
  DIR_RIGHT,
  DIR_DOWN,
  DIR_DOWN_RIGHT
};

// In case of being stuck, use the stuck directions
direction_t atk_stuck_directions[] = {
	DIR_DOWN_LEFT,
	DIR_LEFT,
	DIR_UP_LEFT
};

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {
  // TODO: unused parameters, remove these lines later
  srand(time(NULL));
  static position_t previous_position = INVALID_POSITION;
  static int previous_dir = 0;
  static int lucky_number = 0;
  static int stuck_index = 0; // count rounds of being stucked
  static int stuck_lock = 0; // lock at stuck strategy for LOCK_STRATEGY rounds

  int dir;
  direction_t new_position;
  
  if (equal_positions(attacker_position, previous_position) && previous_dir != 0) {
    stuck_index++;
  }

  if (stuck_index == LOCK_STRATEGY || stuck_lock != 0){
	// INITIATE STUCK STRATEGY!
	// start lock status, and do lock strategy moves (retreat for LOCK_STRATEGY turns)
	if (!stuck_lock) stuck_lock = LOCK_STRATEGY;

	dir = lucky_number % 3;
    lucky_number = (lucky_number % 3) + rand();

	new_position = atk_stuck_directions[dir];

	// reset lock status
	stuck_lock--;
	if (!stuck_lock) stuck_index = 0;
  } 
  else {
    dir = lucky_number % 6;
    lucky_number = (lucky_number % 10) + rand();

	new_position = atk_directions[dir];
  }

  // strategy doesn't consider spy
  UNUSED(defender_spy);

  previous_position = attacker_position;
  previous_dir = dir;

  return new_position;
}




/*----------------------------------------------------------------------------*/
