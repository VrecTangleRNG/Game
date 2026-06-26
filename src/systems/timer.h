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


void TimerInit(const float targetFPS, const float scale);			// Set FPS and virtual time scale, runs once at program interface
void UpdateGameTime(void);
float GetConstantFPS(void);
Time *GetVirtualTime(void);
uint2 ExtractTime(float fsecs, TimeMeasurement measure);
void CleanTimeStorage(void);
Stopwatch *InitStopwatch(char *strpath);											// Initialize Stopwatch, if strpath already exist, return that address
Stopwatch *RunStopwatch(char *strpath, bool relative);
Countdown *InitCountdown(char *strpath);
Countdown *RunCountdown(char *strpath, float duration, bool relative);
float LinearTween(char *strpath, float start, float end, float duration, bool relative);

#endif
