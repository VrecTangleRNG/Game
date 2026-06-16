/* ---HOW TO ADD A STATE V1--- */
/*	-> make 4 function declarations in this header file
 *	-> go to stateList.c, add those new header files into that list
 *	-> create new .c files containing function definitions in states/
 *	-> copy template.c to your new definition file
 */

/* ---HOW TO ADD A STATE V2--- */
/*
 * -> Looks definition for GAME_STATES
 * -> Adds your state there by providing X(enum, function)
 */

#ifndef STATE_LIST_H
#define STATE_LIST_H

#include <stdio.h>

#include "raylib.h"
#include "box2d/box2d.h"
#include "cJSON/cJSON.h"

#include "../gameplay/camera.h"
#include "../gameplay/checkpoint.h"
#include "../gameplay/level.h"
#include "../gameplay/mapBuilder.h"
#include "../gameplay/player.h"
#include "../gameplay/ui.h"
#include "../systems/physics.h"
#include "../systems/timer.h"
#include "../systems/utils.h"

#define GAME_STATES \
	X(STATE_COUNTDOWN, Countdown)\
	X(STATE_EXIT, Exit)\
	X(STATE_HIGHLIGHT, Highlight)\
	X(STATE_RACE, Race)

#define STATE_DECLARATION(function) \
	void Init_##function##State(void);\
	StateIndex Update_##function##State(float deltaTime);\
	void Draw_##function##State(void);\
	int Escape_##function##State(StateIndex toState);

#define STATE_LIST_DECLARATION(function) \
	{ Init_##function##State, \
	Update_##function##State, \
	Draw_##function##State, \
	Escape_##function##State }

typedef enum
{
	STATE_CONTINUE = 999,
	STATE_BASE = 0,
	#define X(enum, function) enum,
	GAME_STATES
	#undef X
	STATE_COUNT
} StateIndex;

typedef struct
{
	void (*init)(void);
	StateIndex (*update)(float);
	void (*draw)(void);
	int (*escape)(StateIndex);
} States;

STATE_DECLARATION(Base)
#define X(enum, function) STATE_DECLARATION(function)
GAME_STATES
#undef X

extern const States stateList[STATE_COUNT];

#endif
