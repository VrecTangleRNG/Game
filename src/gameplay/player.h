#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <string.h>

#include "box2d/box2d.h"
#include "raylib.h"
#include "raymath.h"

#include "../assets_manager/texture.h"
#include "../systems/physics.h"
#include "../systems/utils.h"

typedef struct
{
	char textureFile[32];
	TextureData *textureData;
	b2BodyId bodyId;
	b2ShapeId shapeId;
} Car;

void InitPlayer(b2Vec2 initPos, float initAngle);	// Initialize player
void UpdatePlayer(float deltaTime);								// Do something to player
void DrawPlayer(void);														// Draw player to screen

Vector2 GetCenterPlayerPos(void);					// Get center position of player
Vector2 GetEdgePlayerPos(void);						// Get raylib-based position of player

#endif
