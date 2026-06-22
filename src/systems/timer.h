#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "utils.h"

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

typedef enum
{
	MSECONDS = 0,
	SECONDS,
	MINUTES,
	HOURS
} TimeMeasurement;


// Core time functions
void SetupGameTime(const float targetFPS, const float scale);			// Set FPS and virtual time scale, runs once at program interface
void UpdateGameTime(void);
float GetConstantFPS(void);
Time *GetVirtualTime(void);
meduint ExtractTime(float fsecs, TimeMeasurement measure);
void CleanTimeStorage(void);

// Stopwatch
void StopwatchStart(Stopwatch *sw);
void StopwatchUpdate(Stopwatch *sw);

// Countdown
void CountdownStart(Countdown *cd, float duration);
void CountdownUpdate(Countdown *cd);

// Tweens
float LinearTween(char *name, float start, float end, float duration);

#endif
