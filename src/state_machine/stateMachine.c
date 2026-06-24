/* --- User-defined header files --- */

#include "stateMachine.h"
/* --- ------------------------- --- */


/* --- Global static variables --- */

static StateStatus upcomingStateStat = {STATE_BASE, false, false};
static States *currentState = NULL;
static Stack *stateStack = NULL;
/* --- ----------------------- --- */


/* --- Main methods --- */

int RunStateStack(void)
{
	currentState = (States *)(stateList + upcomingStateStat.state);

	// Determine whether the stateStack is empty or already filled (if so, Push)
	if (!stateStack)
	{
		stateStack = CreateStack();
		stateStack->valueptr = currentState;
	}
	else
	{
		Push(&stateStack, currentState);
	}
	currentState->init();	// Silly me

	// Game loop
	while (true)
	{
		bool firstIteration = true;
		Stack *layer = NULL;
		StackForEach(layer, stateStack)
		{
			// Update head, then pause tails
			UpdateGameTime();
			if (firstIteration)
			{
				upcomingStateStat = *(((States *)(layer->valueptr))->update(GetVirtualTime()->delta));
				firstIteration = false;
			}
			else
			{
				((States *)(layer->valueptr))->pause();
			}
		}

		// Draw
		layer = NULL;
		BeginDrawing();
		StackForEach(layer, stateStack)
		{
			((States *)(layer->valueptr))->draw();
		}
		EndDrawing();

		// Check for exit condition
		if (WindowShouldClose()) return 0;

		// If none of this was run, continue the loop
		// TODO: this was unoptimized
		if (upcomingStateStat.pop)
		{
			// Pop state and run state underneath it
			((States *)(stateStack->valueptr))->exit();
			Pop(&stateStack);
			continue;
		}
		if (upcomingStateStat.state != STATE_CONTINUE)
		{
			// Replace the head by poping head and pushing a new one
			if (upcomingStateStat.replace)
			{
				((States *)(stateStack->valueptr))->exit();
				Pop(&stateStack);
			}

			// Push new state
			break;
		}
	}
	return 1;
}
/* --- ------------ --- */
