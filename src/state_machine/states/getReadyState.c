#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false, 1 };

static char blink = 0;


// Initialize // Runs only once at directly before game loop
INIT_STATE(GetReady)
{
	status.state = STATE_CONTINUE;
	status.replace = false;
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(GetReady)
{
	blink = ((char)(RunStopwatch("blnk", true)->elapsed * 1.75f) % 2) ? 0 : 255;
	if (EnterInput())
	{
		status.state = STATE_COUNTDOWN;
		status.replace = true;
	}
	return &status;
}


// Pause // Do something in background
PAUSE_STATE(GetReady)
{
	return;
}


// Draw // Generic draw function runs directly after update
DRAW_STATE(GetReady)
{
	DrawText
	(
		"Click to start", GetScreenWidth() * .25f, GetScreenHeight() * .75f,
		30, (Color){ 255, 255, 255, blink }
	);
	return;
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(GetReady)
{
	return;
}
