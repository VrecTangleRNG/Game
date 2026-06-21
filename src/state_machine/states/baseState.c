#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false };


// Global variables
static Stopwatch transition;


// Initialize // Runs only once at directly before game loop
INIT_STATE(Base)
{
	StopwatchStart(&transition);
}


// Update // Control the program flow with the return value
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
	StopwatchUpdate(&transition);
	if (transition.elapsed >= 4.0f) transition.running = false;
	DrawText("Hello, world!", 10, LinearTween("test", 10, GetScreenHeight() / 2, 3.0f), 30, BLACK);
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(Base)
{
	return;
}
