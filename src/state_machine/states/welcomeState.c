#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false };


// Initialize // Runs only once at directly before game loop
INIT_STATE(Welcome)
{
	return;
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(Welcome)
{
	return &status;
}


// Pause // Do something in background
PAUSE_STATE(Welcome)
{
	return;
}


// Draw // Generic draw function runs directly after update
DRAW_STATE(Welcome)
{
	return;
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(Welcome)
{
	return;
}
