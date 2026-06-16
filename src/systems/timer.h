#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>

#include "raylib.h"

typedef struct
{
	float elapsed;
	float delta;
	float scale;
} Time;

typedef struct
{
	float startTime;
	float elapsed;
	bool running;
} Stopwatch;

typedef struct
{
	float duration;
	float remaining;
	bool started;
	bool finished;
} Countdown;

// main functions
void SetupGameTime(const float targetFPS, const float scale);
void UpdateGameTime(void);
void StopwatchStart(Stopwatch *sw);
void StopwatchUpdate(Stopwatch *sw);
void CountdownStart(Countdown *cd, float duration);
void CountdownUpdate(Countdown *cd);

// Utility functions
float GetConstantFPS(void);
Time *GetVirtualTime(void);

#endif