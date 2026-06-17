/* --- Header files --- */

#include "timer.h"
/* --- ------------ --- */


/* --- Static global variables --- */

static float constantFPS = 0.0f;
static Time virtualTime;
/* --- ----------------------- --- */


/* --- Main methods --- */

void SetupGameTime(const float targetFPS, const float scale)
{
	SetTargetFPS(targetFPS);
	constantFPS = targetFPS;
	virtualTime.scale = scale;
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
	if (sw->running) sw->elapsed = virtualTime.elapsed - sw->startTime;
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
/* --- ------------ --- */


/* --- Methods --- */

float GetConstantFPS(void)
{
	return constantFPS;
}

Time *GetVirtualTime(void)
{
	return &virtualTime;
}

meduint ExtractTime(float fsecs, smalluint measure)
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
/* --- ------- --- */
