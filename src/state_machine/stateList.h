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

// X(enum, function tag)
#define GAME_STATES \
	X(STATE_COUNTDOWN, Countdown, cndn)\
	X(STATE_EXIT, Exit, exit)\
	X(STATE_HIGHLIGHT, Highlight, hglt)\
	X(STATE_RACE, Race, race)\
	X(STATE_RESULT, Result, resl)

#define INIT_STATE(function) void Init_##function##State(void)
#define UPDATE_STATE(function) StateIndex Update_##function##State(float deltaTime)
#define DRAW_STATE(function) void Draw_##function##State(void)
#define ESCAPE_STATE(function) int Escape_##function##State(StateIndex toState)

#define STATE_DECLARATION(function) \
	INIT_STATE(function);\
	UPDATE_STATE(function);\
	DRAW_STATE(function);\
	ESCAPE_STATE(function);

#define STATE_LIST_DECLARATION(function, string) \
	{ Init_##function##State, \
	Update_##function##State, \
	Draw_##function##State, \
	Escape_##function##State, \
	#string }

typedef enum
{
	STATE_CONTINUE = 255,
	STATE_BREAK = 254,
	STATE_BASE = 0,
	#define X(enum, function, string) enum,
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
	char code[4];
} States;

STATE_DECLARATION(Base)
#define X(enum, function, string) STATE_DECLARATION(function)
GAME_STATES
#undef X

extern const States stateList[STATE_COUNT];

#endif
