/* --- Header files --- */

#include "timer.h"
/* --- ------------ --- */


/* --- Static global variables --- */

static float constantFPS = 0.0f;
static Time virtualTime;
static Trie *timerStorage = NULL;
/* --- ----------------------- --- */


/* --- Main methods --- */

void TimerInit(const float targetFPS, const float scale)
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


// TODO: optimize this
Stopwatch *InitStopwatch(char *strpath)
{
	Stopwatch *buffer = (Stopwatch *)SearchTrie(timerStorage, strpath);
	if (!buffer)
	{
		buffer = calloc(1, sizeof(Stopwatch));
		if (!buffer) {printf("Unable to create space\n"); return NULL;}
		InsertTrie(timerStorage, strpath, buffer);
	}
	buffer->startTime = GetTime();
	return buffer;
}

// NOTE: timing concern, idk what to do about it
Stopwatch *RunStopwatch(char *strpath, bool relative)
{
	Stopwatch *buffer = InitStopwatch(strpath);
	if (!buffer->running) buffer->running = true;
	if (buffer->running) buffer->elapsed += (relative) ? GetFrameTime() : virtualTime.delta;
	return buffer;
}

Countdown *InitCountdown(char *strpath)
{
	Countdown *buffer = (Countdown *)SearchTrie(timerStorage, strpath);
	if (!buffer)
	{
		buffer = calloc(1, sizeof(Countdown));
		if (!buffer) {printf("Unable to create space\n"); return NULL;}
		InsertTrie(timerStorage, strpath, buffer);
	}
	return buffer;
}

Countdown *RunCountdown(char *strpath, float duration, bool relative)
{
	Countdown *buffer = InitCountdown(strpath);
	// Holy ifs
	if (!buffer->started && !buffer->finished)
	{
		buffer->duration = duration;
		buffer->remaining = duration;
		buffer->started = true;
	}
	if (buffer->started && !buffer->finished)
	{
		buffer->remaining -= (relative) ? GetFrameTime() : virtualTime.delta;
		if (buffer->remaining <= .0f)
		{
			buffer->finished = true;
			buffer->remaining = .0f;
		}
	}
	return buffer;
}

float GetConstantFPS(void)
{
	return constantFPS;
}

Time *GetVirtualTime(void)
{
	return &virtualTime;
}

uint2 ExtractTime(float fsecs, TimeMeasurement measure)
{
	uint2 scalar = 0;
	switch (measure)
	{
		case MSECONDS:
			scalar = ((uint2)(fsecs * 1000) % 1000);
			break;

		case SECONDS:
			scalar = (uint2)fsecs % 60;
			break;

		case MINUTES:
			scalar = (uint2)(fsecs / 60.0f) % 60;
			break;

		case HOURS:
			scalar = (uint2)(fsecs / 3600.0f) % 24;
			break;

		default: break;
	}
	return scalar;
}

float LinearTween(char *strpath, float start, float end, float duration, bool relative)
{
	Countdown *cd = RunCountdown(strpath, duration, relative);
	float value = Lerp(start, end, (duration - cd->remaining) / duration);
	return (start < end) ? ((value >= end) ? end : value) : ((value <= end) ? end : value);
	// What the heck the above code doin lmao
}

void CleanTimeStorage(void)
{
	FreeTrie(timerStorage);
	timerStorage = CreateTrie();
}
/* --- ------------ --- */
