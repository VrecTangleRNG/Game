/* --- User-defined header files --- */

#include "stateList.h"
/* --- ------------------------- --- */


/* --- Global variables --- */

const States stateList[STATE_COUNT] =
{
	STATE_LIST_DECLARATION(Base),
	#define X(enum, function) STATE_LIST_DECLARATION(function), 
	GAME_STATES
	#undef X
};
/* --- ---------------- --- */

