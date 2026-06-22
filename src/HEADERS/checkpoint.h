#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <stdio.h>

#include "raylib.h"
#include "box2d/box2d.h"

#include "physics.h"
#include "utils.h"

typedef enum
{
	CIRCLE,
	BOX,
	CP_COUNT
} CpDimension;

typedef struct
{
	b2BodyId bodyId;
	b2ShapeId shapeId;
	Rectangle rect;
	int id;
} Checkpoint;

void InitCheckpoint(void);
void CreateCheckpoint(Rectangle destRect, float rotation, CpDimension dimension, int index);
void DestroyCheckpoint(void);
b2ShapeId *GetCpShapeFromId(int cpId);

#endif
