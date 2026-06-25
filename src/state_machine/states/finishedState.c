#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false };


// Initialize // Runs only once at directly before game loop
INIT_STATE(Base)
{
	return;
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(Base)
{
	return &status;
}


// Pause // Do something in background
PAUSE_STATE(Base)
{
	return;
}


// Draw // Generic draw function runs directly after update
DRAW_STATE(Base)
{
	return;
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(Base)
{
	return;
}
