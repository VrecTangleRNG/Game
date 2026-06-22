/* --- User-defined header files --- */

#include "stateList.h"
/* --- ------------------------- --- */


/* --- Global variables --- */

const States stateList[STATE_COUNT] =
{
	STATE_LIST_DECLARATION(Base, base),
	#define X(enum, function, string) STATE_LIST_DECLARATION(function, string),
	GAME_STATES
	#undef X
};
/* --- ---------------- --- */
