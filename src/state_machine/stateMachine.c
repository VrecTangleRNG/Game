/* --- User-defined header files --- */

#include "stateMachine.h"
/* --- ------------------------- --- */


/* --- Global static variables --- */

static StateIndex currentStateIndex = STATE_BASE;
static StateIndex upcomingStateIndex;
static States currentState;
/* --- ----------------------- --- */


/* --- Main methods --- */

int RunStateMachine(void)
{
	// Initialize before entering loop
	currentState = stateList[currentStateIndex];
	currentState.init();

	// Game loop
	while (true)
	{
		UpdateGameTime();

		// Always check for game loop transition
		upcomingStateIndex = currentState.update(GetVirtualTime()->delta);
		BeginDrawing();
		ClearBackground(GRAY);
		currentState.draw();
		EndDrawing();

		// Exit game on player input or continue playing
		if (WindowShouldClose()) upcomingStateIndex = STATE_EXIT;
		if (upcomingStateIndex != STATE_CONTINUE) break;
	}

	// Do cleanups before state transition
	currentStateIndex = upcomingStateIndex;
	int isKeepRunning = currentState.escape(upcomingStateIndex);
	return isKeepRunning;
}
/* --- ------------ --- */
