/* --- User-defined header files --- */

#include "physics.h"
/* --- ------------------------- --- */


/* --- Preprocessors --- */

#define SENSOR_RETURN_SHAPE \
	if (!targetShape)\
	{\
		if (B2_ID_EQUALS(*sensorShape, currentSensor)) return currentVisitor;\
	}\
	else if (B2_ID_EQUALS(*targetShape, currentVisitor)) return currentSensor
/* --- ------------- --- */


/* --- Global static variables --- */

static b2WorldId worldId;
/* --- ----------------------- --- */


/* --- Main methods --- */

void InitPhysics(void)
{
	b2SetLengthUnitsPerMeter(PX_PER_METER);
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = (b2Vec2){ 0.0f, 0.0f };
	worldId = b2CreateWorld(&worldDef);
}

void UpdatePhysics(float timeStep, float deltaTime)
{
	static float accumulator = 0.0f;
	accumulator += deltaTime;
	while (accumulator >= timeStep)
	{
		b2World_Step(worldId, timeStep, 4);
		accumulator -= timeStep;
	}
}

b2ShapeId CheckSensorCollision(b2ShapeId *targetShape, b2ShapeId *sensorShape, int check)
{
	b2SensorEvents worldEvents = b2World_GetSensorEvents(GetWorldId());
	b2ShapeId currentSensor;
	b2ShapeId currentVisitor;

	switch (check)
	{
		// Check for shapes that is involved in sensor collision
		case 1:
			for (int i = 0; i < worldEvents.beginCount; i++)
			{
				b2SensorBeginTouchEvent *beginTouch = worldEvents.beginEvents + i;
				currentSensor = beginTouch->sensorShapeId;
				currentVisitor = beginTouch->visitorShapeId;
				SENSOR_RETURN_SHAPE;
			}
			break;

		// Check for shapes that is leaving the sensor area
		case -1:
			for (int i = 0; i < worldEvents.endCount; i++)
			{
				// Check if the shape is valid
				b2SensorEndTouchEvent *endTouch = worldEvents.endEvents + i;
				if((b2Shape_IsValid(endTouch->visitorShapeId)))
				{
					currentSensor = endTouch->sensorShapeId;
					currentVisitor = endTouch->visitorShapeId;
				}
				SENSOR_RETURN_SHAPE;
			}
			break;

		default: break;
	}
	return (b2ShapeId){ 0 };
}
/* --- ------------ --- */


/* --- Methods --- */

b2WorldId GetWorldId(void)
{
	return worldId;
}
/* --- ------- --- */
