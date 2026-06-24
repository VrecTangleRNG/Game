/* ---HOW TO ADD A STATE V1--- */
/*	-> make 4 function declarations in this header file
 *	-> go to stateList.c, add those new header files into that list
 *	-> create new .c files containing function definitions in states/
 *	-> copy template.c to your new definition file
 */

/* ---HOW TO ADD A STATE V2--- */
/*
 * -> Looks definition for GAME_STATES
 * -> Adds your state there by providing X(enum, function, string)
 * -> Run this command in terminal: cp templates.txt src/state_machine/states/<nameState>.c
 */

#ifndef STATE_LIST_H
#define STATE_LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

// X(STATE_NAME, Function, idtf)
#define GAME_STATES\
	X(STATE_SPLASH, Splash, spls)\
	X(STATE_WELCOME, Welcome, wlcm)\
	X(STATE_MAIN_MENU, MainMenu, mnmn)

#define INIT_STATE(function) void Init_##function##_(void)
#define UPDATE_STATE(function) StateStatus *Update_##function##_(float deltaTime)
#define DRAW_STATE(function) void Draw_##function##_(void)
#define PAUSE_STATE(function) void Pause_##function##_(void)
#define EXIT_STATE(function) void Exit_##function##_(void)

#define STATE_DECLARATION(function) \
	INIT_STATE(function);\
	UPDATE_STATE(function);\
	DRAW_STATE(function);\
	PAUSE_STATE(function);\
	EXIT_STATE(function);

#define STATE_LIST_DECLARATION(function, string) \
	{ Init_##function##_, \
	Update_##function##_, \
	Draw_##function##_, \
	Pause_##function##_, \
	Exit_##function##_, \
	#string }

typedef enum
{
	STATE_CONTINUE = 255,
	STATE_BASE = 0,

	#define X(enum, function, string) enum,
	GAME_STATES
	#undef X

	STATE_COUNT
} StateIndex;

typedef struct
{
	StateIndex state;
	bool replace;
	bool pop;
} StateStatus;

typedef struct
{
	void (*init)(void);
	StateStatus *(*update)(float);
	void (*draw)(void);
	void (*pause)(void);
	void (*exit)(void);
	char code[4];
} States;

STATE_DECLARATION(Base)
#define X(enum, function, string) STATE_DECLARATION(function)
GAME_STATES
#undef X

extern const States stateList[STATE_COUNT];

#endif
