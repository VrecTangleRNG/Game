/* --- User-defined header files --- */

#include "player.h"
/* --- ------------------------- --- */


/* --- Global static variables --- */

// Global constants
static float
	LINEAR_DAMPING 	= 2.5f,										// Between 2.0 ~ 8.0
	ANGULAR_DAMPING	= 14.0f,
	DENSITY 		= 50.0f / (PX_PER_METER * PX_PER_METER),	// kg / m^2
	F_ENGINE 		= 25000.0f * PX_PER_METER,					// kg * m / sec^2
	TIRE_GRIP		= 0.85f,
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
	carAngle = RAD2DEG * b2Rot_GetAngle(b2Body_GetRotation(car.bodyId));

	// Set initial car state
	playerControl = 1;
}

void UpdatePlayer(float deltaTime)
{
	// Control movement and rotation based on player input
	float gasPad = (BrakeInput() - AccelerateInput()) * playerControl;
	float steerPad = SteeringInput();

	// Change the steering angle based on player input
	static float steeringAngle = 0.0f;
	steeringAngle += steerPad * STEERING_SPEED * deltaTime;

	// If no input from steer. then return steer to center
	float maxAngle = 60.0f;
	static int lastSteer = 0;
	if (steerPad != 0)
	{
		lastSteer = steerPad;
		steeringAngle = Clamp(steeringAngle, -maxAngle, maxAngle);
	}
	else
	{
		steeringAngle -= lastSteer * STEERING_SPEED * deltaTime;
		if (lastSteer >= .0f)
		{
			steeringAngle = Clamp(steeringAngle, 0.0f, maxAngle);
		}
		else
		{
			steeringAngle = Clamp(steeringAngle, -maxAngle, 0.0f);
		}
	}

	// Control tire angle direction in facing
	carRad = b2Rot_GetAngle(b2Body_GetRotation(car.bodyId));
	carAngle = RAD2DEG * carRad;
	tireAngle = carAngle + steeringAngle;
	if (tireAngle < 0.0f)
	{
		tireAngle += 360.0f;
	}

	// Set where the rear forces is acting
	Vector2 forceMagnitude = { F_ENGINE * gasPad * .5f, 0.0f };
	Vector2 rearForceMagnitude = Vector2Rotate(forceMagnitude, carRad);
	Vector2 rearForcePoint = { carExtent.x, 0.0f };
	rearForcePoint = Vector2Rotate(rearForcePoint, carRad);
	rearForcePoint = Vector2Add(B2vecToRlvec(carPosCenter), rearForcePoint);

	// Set where the front force is acting
	Vector2 frontForceMagnitude = Vector2Rotate
	(
		Vector2Rotate(forceMagnitude, carRad),
		steeringAngle * DEG2RAD
	);
	Vector2 frontForcePoint = { -carExtent.x, 0.0f };
	frontForcePoint = Vector2Rotate(frontForcePoint, carRad);
	frontForcePoint = Vector2Add(B2vecToRlvec(carPosCenter), frontForcePoint);

	// Apply forces
	b2Body_ApplyForce
	(
		car.bodyId,
		RlvecToB2vec(rearForceMagnitude),
		RlvecToB2vec(rearForcePoint),
		true
	);
	b2Body_ApplyForce
	(
		car.bodyId,
		RlvecToB2vec(frontForceMagnitude),
		RlvecToB2vec(frontForcePoint),
		true
	);

	// Fix right velocity to control sliding
	Vector2 currentVelocity = B2vecToRlvec(b2Body_GetLinearVelocity(car.bodyId));
	Vector2 right =
	{
		cosf((carAngle + 90.0f) * DEG2RAD),
		sinf((carAngle + 90.0f) * DEG2RAD)
	};
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
	carAngle = RAD2DEG * b2Rot_GetAngle(b2Body_GetRotation(car.bodyId));
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
