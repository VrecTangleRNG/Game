#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false, 1 };

static Stopwatch *playerLapTime = NULL;


// Initialize // Runs only once at directly before game loop
INIT_STATE(Finished)
{
	playerLapTime = InitStopwatch("plyr");
	status.pop = false;
	status.dives = 1;
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(Finished)
{
	if (EnterInput())
	{
		status.pop = true;
		status.dives = 2;
	}
	return &status;
}


// Pause // Do something in background
PAUSE_STATE(Finished)
{
	return;
}


// Draw // Generic draw function runs directly after update
DRAW_STATE(Finished)
{
	DrawText("YOU FINISHED 1st!", 20, GetScreenHeight() * .5f - 25, 50, WHITE);
	DrawText
	(
		TextFormat
		(
			"Your lap time: %02d:%02d.%03d",
			ExtractTime(playerLapTime->elapsed, MINUTES),
			ExtractTime(playerLapTime->elapsed, SECONDS),
			ExtractTime(playerLapTime->elapsed, MSECONDS)
		),
		20, GetScreenHeight() * .5f + 25, 30, WHITE
	);
	DrawText("Press ENTER to Return to Main Menu", 20, GetScreenHeight() * .5f + 65, 30, BLACK);
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(Finished)
{
	return;
}
