/* --- User-defined header files --- */

#include "stateMachine.h"
/* --- ------------------------- --- */


/* --- Global static variables --- */

static StateIndex upcomingStateIndex = STATE_BASE;
static States *currentState;
static Stack *stateStack = NULL;
/* --- ----------------------- --- */


/* --- Main methods --- */

int RunStateStack(void)
{
	currentState = stateList + upcomingStateIndex;
	currentState->init();	// Silly me
	if (!stateStack)
	{
		stateStack = CreateStack();
		stateStack->valueptr = currentState;
	}
	else
	{
		Push(&stateStack, currentState);
	}

	// Game loop
	while (true)
	{
		// Update head
		UpdateGameTime();
		upcomingStateIndex = ((States *)(stateStack->valueptr))->update(GetVirtualTime()->delta);

		// Draw
		Stack *layer = NULL;
		StackForEach(layer, stateStack)
		{
			BeginDrawing();
			ClearBackground(GRAY);
			((States *)(layer->valueptr))->draw();
			EndDrawing();
		}

		// Continue, pop, or push
		if (upcomingStateIndex == STATE_BREAK) {Pop(&stateStack); continue;}
		if (upcomingStateIndex != STATE_CONTINUE) break;
	}
}

// int RunStateMachine(void)
// {
// 	// Initialize before entering loop
// 	currentState = stateList[currentStateIndex];
// 	currentState.init();
//
// 	// Game loop
// 	while (true)
// 	{
// 		UpdateGameTime();
//
// 		// Always check for game loop transition
// 		upcomingStateIndex = currentState.update(GetVirtualTime()->delta);
// 		BeginDrawing();
// 		ClearBackground(GRAY);
// 		currentState.draw();
// 		EndDrawing();
//
// 		// Exit game on player input or continue playing
// 		if (WindowShouldClose()) upcomingStateIndex = STATE_EXIT;
// 		if (upcomingStateIndex != STATE_CONTINUE) break;
// 	}
//
// 	// Do cleanups before state transition
// 	currentStateIndex = upcomingStateIndex;
// 	int isKeepRunning = currentState.escape(upcomingStateIndex);
// 	return isKeepRunning;
// }
/* --- ------------ --- */
