#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false, 1 };

static float fade;


// Initialize // Runs only once at directly before game loop
INIT_STATE(Splash)
{
	return;
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(Splash)
{
	Stopwatch *sw = RunStopwatch("splash", true);
	if (sw->elapsed < 2.0f) fade = LinearTween("in", .0f, 255.0f, .5f, true);
	else fade = LinearTween("out", 255.0f, .0f, .5f, true);
	if (sw->elapsed > 2.6f || EnterInput())
	{
		status.state = STATE_WELCOME;
		status.replace = true;
	}
	return &status;
}


// Pause // Do something in background
PAUSE_STATE(Splash)
{
	return;
}


// Draw // Generic draw function runs directly after update
DRAW_STATE(Splash)
{
	ClearBackground(WHITE);
	DrawText("splash Art 1", 10, 10, 30, (Color){ 0, 0, 0, fade });
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(Splash)
{
	CleanTimeStorage();
}
