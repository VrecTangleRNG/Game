#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"
#include "box2d/box2d.h"

#include "../assets_manager/texture.h"
#include "../systems/input.h"
#include "../systems/physics.h"
#include "../systems/utils.h"

typedef struct
{
	char textureFile[32];
	TextureData *textureData;
	b2BodyId bodyId;
	b2ShapeId shapeId;
} Car;

typedef enum
{
	AUTO = 0,
	RELEASE,
	HELD,
	CONTROL_COUNT
} ControlOveride;

// Main function declarations
void InitPlayer(b2Vec2 initPos, float initAngle);	// Initialize player
void UpdatePlayer(float deltaTime);					// Update player
void DrawPlayer(void);								// Draw player to screen
// TODO: AUTO wasn't yet defined
void SetPlayerControl(uint2 control);				// Set  player control so car can't be controlled by player ((isHeld) = false)
Vector2 GetCenterPlayerPos(void);					// Get center position of player
Vector2 GetEdgePlayerPos(void);						// Get raylib-based position of player
b2ShapeId *GetPlayerShape(void);					// Get hitbox shape of player

#endif
