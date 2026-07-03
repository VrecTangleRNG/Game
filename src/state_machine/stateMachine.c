/* --- User-defined header files --- */

#include "stateMachine.h"
/* --- ------------------------- --- */


/* --- Global static variables --- */

static StateStatus upcomingStateStat = {STATE_BASE, false, false};
static States *currentState = NULL;
static Deque *stateDeque = NULL;	// TODO: not yet freed
static uint1 switchCondition;
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
		switchCondition = (upcomingStateStat.replace * REPLACE) | (upcomingStateStat.pop * POP);

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

		// Control state flow
		if (switchCondition & (REPLACE | POP))
		{
			((States *)(stateDeque->front->valueptr))->exit();
			PopFrontDq(&stateDeque);
		}
		if (switchCondition & POP) continue;
		if (upcomingStateStat.state != STATE_CONTINUE) break;
		if (WindowShouldClose()) return 0;
	}
	return 1;
}
/* --- ------------ --- */
