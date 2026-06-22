/* --- User-defined header files --- */

#include "../HEADERS/checkpoint.h"
/* --- ------------------------- --- */


/* --- Static global variables --- */

static b2BodyDef cpBodyDef;
static b2ShapeDef cpShapeDef;
static b2Polygon cpPolygon;
static b2Circle cpCircle;

static Checkpoint *cps;
static int cpCount;
/* --- ----------------------- --- */


/* --- Main methods --- */

void InitCheckpoint(void)
{
	// Initiolize cp body definitions
	cpBodyDef = b2DefaultBodyDef();

	// Initiolize cp shape definitions
	cpShapeDef = b2DefaultShapeDef();
	cpShapeDef.isSensor = true;
	cpShapeDef.enableSensorEvents = true;
}

void CreateCheckpoint(Rectangle destRect, float rotation, CpDimension dimension, int id)
{
	// Allocate memory to hold checkpoint information and expands afterwards
	cpCount++;
	if (!cps) cps = calloc(1, sizeof(Checkpoint));
	else cps = realloc(cps, cpCount * sizeof(Checkpoint));
	if (!cps) {printf("Unable to make Checkpoint\n"); return;}

	// Set its properties
	cpBodyDef.position = (b2Vec2)
	{
		destRect.x + destRect.width * 0.5f,
		destRect.y + destRect.height * 0.5f
	};
	cpBodyDef.rotation = b2MakeRot(DEG2RAD * rotation);
	cps[cpCount - 1].id = id;	// NOTE: Id assignement

	// Make cp bodyId and attach its shape
	cps[cpCount - 1].bodyId = b2CreateBody(GetWorldId(), &cpBodyDef);
	switch (dimension)
	{
		case BOX:
			cpPolygon = b2MakeBox(destRect.width * 0.5f, destRect.height * 0.5f);
			cps[cpCount - 1].shapeId = b2CreatePolygonShape
			(
				cps[cpCount - 1].bodyId,
				&cpShapeDef, &cpPolygon
			);
			break;

		case CIRCLE:
			cpCircle.center = (b2Vec2){ 0.0f, 0.0f };
			cpCircle.radius = destRect.width * 0.5f;
			cps[cpCount - 1].shapeId = b2CreateCircleShape
			(
				cps[cpCount - 1].bodyId,
				&cpShapeDef, &cpCircle
			);
			break;

		default: break;
	}

	// Store rendering information
	cps[cpCount - 1].rect = destRect;
}

void DestroyCheckpoint(void)
{
	for (int i = 0; i < cpCount; i++)
	{
		b2DestroyBody(cps[i].bodyId);
	}
	free(cps);
}
/* --- ------------ --- */


/* --- Methods --- */

b2ShapeId *GetCpShapeFromId(int cpId)
{
	for (int i = 0; i < cpCount; i++)
	{
		if (cps[i].id == cpId) return &(cps[i].shapeId);
	}
	return NULL;
}
/* --- ------- --- */
