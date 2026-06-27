#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false };

static Countdown *countdown = NULL;


// Initialize // Runs only once at directly before game loop
INIT_STATE(Countdown)
{
	return;
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(Countdown)
{
	countdown = RunCountdown("321", 3.0f, false);
	if (countdown->finished)
	{
		status.pop = true;
	}
	return &status;
}


// Pause // Do something in background
PAUSE_STATE(Countdown)
{
	return;
}


// Draw // Generic draw function runs directly after update
DRAW_STATE(Countdown)
{
	DrawText(TextFormat("%d", (uint1)countdown->remaining + 1), GetScreenWidth() * .25f, GetScreenHeight() * .75f, 30, WHITE);
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(Countdown)
{
	CleanTimeStorage();
}
