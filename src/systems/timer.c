/* --- Header files --- */

#include "timer.h"
/* --- ------------ --- */


/* --- Static global variables --- */

static float constantFPS = 0.0f;
static Time virtualTime;
static Trie *timerStorage = NULL;
/* --- ----------------------- --- */


/* --- Main methods --- */

void SetupGameTime(const float targetFPS, const float scale)
{
	SetTargetFPS(targetFPS);
	constantFPS = targetFPS;
	virtualTime.scale = scale;
	if (!timerStorage) timerStorage = CreateTrie();
}

void UpdateGameTime(void)
{
	virtualTime.delta = GetFrameTime() * virtualTime.scale;
	virtualTime.elapsed += virtualTime.delta;
}

void StopwatchStart(Stopwatch *sw)
{
	sw->startTime = virtualTime.elapsed;
	sw->running = true;
}

void StopwatchUpdate(Stopwatch *sw)
{
	if (sw->running) sw->elapsed += virtualTime.delta;
}

void CountdownStart(Countdown *cdwn, float duration)
{
	cdwn->duration = duration;
	cdwn->remaining = cdwn->duration;
	cdwn->started = true;
	cdwn->finished = false;
}

void CountdownUpdate(Countdown *cdwn)
{
	if (cdwn->started && !cdwn->finished)
	{
		cdwn->remaining -= virtualTime.delta;
	}
	if (cdwn->remaining <= 0.0f)
	{
		cdwn->finished = true;
		cdwn->remaining = 0.0f;
	}
}

float GetConstantFPS(void)
{
	return constantFPS;
}

Time *GetVirtualTime(void)
{
	return &virtualTime;
}

meduint ExtractTime(float fsecs, TimeMeasurement measure)
{
	meduint scalar = 0;
	switch (measure)
	{
		case MSECONDS:
			scalar = ((meduint)(fsecs * 1000) % 1000);
			break;

		case SECONDS:
			scalar = (meduint)fsecs % 60;
			break;

		case MINUTES:
			scalar = (meduint)(fsecs / 60.0f) % 60;
			break;

		case HOURS:
			scalar = (meduint)(fsecs / 3600.0f) % 24;
			break;

		default: break;
	}
	return scalar;
}

float LinearTween(char *name, float start, float end, float duration)
{
	Stopwatch *currentStopwatch = (Stopwatch *)SearchTrie(timerStorage, name);
	if (!currentStopwatch)
	{
		currentStopwatch = calloc(1, sizeof(Stopwatch));
		if (!currentStopwatch) {printf("Unable to create space\n"); return .0f;}
		InsertTrie(timerStorage, name, currentStopwatch);
	}
	StopwatchStart(currentStopwatch);
	if (currentStopwatch->elapsed <= duration) StopwatchUpdate(currentStopwatch);
	float value = Lerp(start, end, currentStopwatch->elapsed / duration);
	// What the heck
	return (start < end) ? ((value >= end) ? end : value) : ((value <= end) ? end : value);
}

void CleanTimeStorage(void)
{
	FreeTrie(timerStorage);
}
/* --- ------------ --- */
