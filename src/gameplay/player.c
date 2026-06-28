/* --- User-defined header files --- */

#include "player.h"
/* --- ------------------------- --- */


/* --- Global static variables --- */

// Global constants
static float
	LINEAR_DAMPING 	= 1.6f,										// Between 2.0 ~ 8.0
	ANGULAR_DAMPING	= 14.0f,
	DENSITY 		= 50.0f / (PX_PER_METER * PX_PER_METER),	// kg / m^2
	TIRE_GRIP		= .85f,
	STEERING_SPEED	= 600.0f;

// Global variables
static Rectangle 	tireTextureData;
static Rectangle	tireSource, tireDest;
static Vector2		tireOrigin;

static Car car = { 0 };
static b2Vec2 carExtent;
static b2Vec2 carPosCenter, carPosEdge;
static TextureData *carTextureData;
static float carAngle = .0f, tireAngle = .0f;
static float carRad;
static uint1 playerControl = 1;
/* --- ----------------------- --- */


/* --- Main methods --- */

void InitPlayer(b2Vec2 initPos, float initAngle)
{
	// Set up initial car "body"
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.linearDamping = LINEAR_DAMPING;
	bodyDef.angularDamping = ANGULAR_DAMPING;
	bodyDef.position = initPos;
	bodyDef.rotation = b2MakeRot(DEG2RAD * initAngle);
	bodyDef.type = b2_dynamicBody;
	car.bodyId = b2CreateBody(GetWorldId(), &bodyDef);

	// Loading car texture and its information
	strcpy(car.textureFile, "car1.png");
	car.textureData = GetSheetData(car.textureFile);
	carExtent.x = car.textureData->rect.width * 0.5f;
	carExtent.y = car.textureData->rect.height * 0.5f;

	// Loading tire texture and its information
	//tireTextureData =;
	//tireSource = (Rectangle){ 0.0f, 0.0f,tireTextureData.width, tireTextureData.height };
	//tireDest = (Rectangle){ 0.0f, 0.0f, tireTextureData.width, tireTextureData.height };
	//tireOrigin = (Vector2){ tireTextureData.width * 0.5f, tireTextureData.height * 0.5f };

	// Define physical hitbox and set up shape definition
	b2Polygon carHitbox = b2MakeBox( carExtent.x, carExtent.y );
	b2ShapeDef shapeDef = b2DefaultShapeDef();

	// Create shapes on the body and attach user data on it
	shapeDef.density = DENSITY;
	shapeDef.enableSensorEvents = true;
	car.shapeId = b2CreatePolygonShape(car.bodyId, &shapeDef, &carHitbox);

	// Get player position before loop
	carPosCenter = b2Body_GetWorldPoint(car.bodyId, (b2Vec2){ 0.0f, 0.0f });
	carPosEdge = b2Body_GetWorldPoint
	(
		car.bodyId,
		(b2Vec2){ -carExtent.x , -carExtent.y }
	);
	carRad = b2Rot_GetAngle(bodyDef.rotation);
	carAngle = RAD2DEG * carRad;

	// Set initial car state
	playerControl = 1;
}

void UpdatePlayer(float deltaTime)
{
	// Control movement and rotation based on player input
	float gasPad = (AccelerateInput() - BrakeInput()) * playerControl;
	float steerPad = SteeringInput();

	// Calculate engine force
	float mass = b2Body_GetMass(car.bodyId);
	float acceleration = 50.0f * PX_PER_METER * gasPad;
	float engineF = mass * acceleration;

	// Set engine force appplication
	b2Vec2 forcePoint = b2Add
	(
		carPosCenter,
		b2RotateVector(b2Body_GetRotation(car.bodyId), (b2Vec2){ carExtent.x, .0f })
	);

	// Apply engine force
	b2Vec2 force = { -(engineF), .0f };
	b2Body_ApplyForce
	(
		car.bodyId,
		b2RotateVector(b2Body_GetRotation(car.bodyId), force),
		forcePoint,
		true
	);

	// Calculate steering force
	float steerF = .0f;
	if (b2Length(b2Body_GetLinearVelocity(car.bodyId)) > PX_PER_METER * .3f)
	{
		steerF = mass * 40.0f * PX_PER_METER * steerPad;
	}

	// Set Steering force point
	forcePoint = b2Add
	(
		carPosCenter,
		b2RotateVector(b2Body_GetRotation(car.bodyId), (b2Vec2){ -carExtent.x, .0f })
	);

	// Apply steering force
	force = (b2Vec2){ .0f, -(steerF) };
	b2Body_ApplyForce
	(
		car.bodyId,
		b2RotateVector(b2Body_GetRotation(car.bodyId), force),
		forcePoint,
		true
	);

	// Fix car's slowing down behaviour
	b2Vec2 vel = b2Body_GetLinearVelocity(car.bodyId);
	if (b2Length(vel) <= PX_PER_METER * .3f && FloatEquals(gasPad, .0f))
	{
		b2Body_SetLinearVelocity(car.bodyId, (b2Vec2){ .0f, .0f });
	}

	// Fix right velocity to control sliding
	Vector2 currentVelocity = B2vecToRlvec(b2Body_GetLinearVelocity(car.bodyId));
	Vector2 right = { cosf(carRad + B2_PI * .5f), sinf(carRad + B2_PI * .5f) };
	float lateralSpeed = Vector2DotProduct(currentVelocity, right);
	Vector2 killLateral = Vector2Scale(right, -lateralSpeed * TIRE_GRIP);
	b2Body_SetLinearVelocity
	(
		car.bodyId,
		RlvecToB2vec(Vector2Add(currentVelocity, killLateral))
	);

	// Get linear and angular tranformations
	carPosCenter = b2Body_GetWorldPoint(car.bodyId, (b2Vec2){ 0.0f, 0.0f });
	carPosEdge = b2Body_GetWorldPoint
	(
		car.bodyId,
		(b2Vec2){ -carExtent.x , -carExtent.y }
	);
	tireDest.x = carPosEdge.x;
	tireDest.y = carPosEdge.y;
	carRad = b2Rot_GetAngle(b2Body_GetRotation(car.bodyId));
	carAngle = RAD2DEG * carRad;
}

void DrawPlayer(void)
{
	// Draw the main car body
	DrawSheetSection
	(
		car.textureFile, B2vecToRlvec(carPosEdge),
		Vector2Zero(), carAngle, WHITE
	);

	// Draw car's tire
	//DrawTexturePro
	//(
	//	tireTextureData, tireSource, tireDest,
	//	tireOrigin, tireAngle, WHITE
	//);
}
/* --- ------------ --- */


/* --- Methods --- */
void SetPlayerControl(uint2 control)
{
	switch (control) {
		case AUTO:		break;
		case RELEASE:	playerControl = 0; break;
		case HELD:		playerControl = 1; break;
		default: break;
	}
}

Vector2 GetCenterPlayerPos(void)
{
	return B2vecToRlvec(carPosCenter);
}

Vector2 GetEdgePlayerPos(void)
{
	return B2vecToRlvec(carPosEdge);
}

b2ShapeId *GetPlayerShape(void)
{
	return &(car.shapeId);
}
/* --- ------- --- */
