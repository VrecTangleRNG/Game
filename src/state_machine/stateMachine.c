/* --- User-defined header files --- */

#include "stateMachine.h"
/* --- ------------------------- --- */


/* --- Global static variables --- */

static StateStatus upcomingStateStat = {STATE_BASE, false, false};
static States *currentState = NULL;
static Deque *stateDeque = NULL;	// TODO: not yet freed
/* --- ----------------------- --- */


/* --- Main methods --- */

int RunStateStack(void)
{
	// Initialization of currentState so this not trigger segmentation fault
	currentState = (States *)(stateList + upcomingStateStat.state);

	// Check whether stateDeque is empty or already filled (if so, Push)
	if (!stateDeque) stateDeque = CreateDeque();
	InsertFrontDq(&stateDeque, currentState);

	// Game loop
	currentState->init();	//<- Silly me
	while (true)
	{
		// Update head
		UpdateGameTime();
		upcomingStateStat = *((States *)stateDeque->front->valueptr)->update(GetVirtualTime()->delta);

		// Pause tails
		DLL *layer = stateDeque->front;
		while (layer)
		{
			((States *)(layer->valueptr))->pause(GetVirtualTime()->delta);
			layer = layer->next;
		}

		// Draw from rear
		layer = stateDeque->rear;
		BeginDrawing();
		while (layer)
		{
			((States *)(layer->valueptr))->draw();
			layer = layer->prev;
		}
		EndDrawing();

		// If none of this was run, continue the loop
		// TODO: this was unoptimized
		if (upcomingStateStat.pop)
		{
			// Pop state and run state underneath it
			((States *)(stateDeque->front->valueptr))->exit();
			PopFrontDq(&stateDeque);
			continue;
		}
		if (upcomingStateStat.state != STATE_CONTINUE)
		{
			// Replace the head by poping head and pushing a new one
			if (upcomingStateStat.replace)
			{
				((States *)(stateDeque->front->valueptr))->exit();
				PopFrontDq(&stateDeque);
			}

			// Push new state
			break;
		}

		// Check for exit condition
		if (WindowShouldClose()) return 0;
	}
	return 1;
}
/* --- ------------ --- */
