/* --- header files --- */

// TODO: i don't think mapBuilder should be in gameplay/ (or is it?)
#include "mapBuilder.h"
/* --- ------------ --- */


/* --- Static global variables --- */

static int tileCount = 0;
static int bodyCount = 0;
static int spawnCount = 0;
static Tile *ts = NULL;
static Tilemap tm;

static b2BodyId *bodyIds = NULL;
static Spawnpoint *sps = NULL;
/* --- ----------------------- --- */


/* --- Main methods --- */

void LoadMap(char *tilemapFile)
{
	// Parse string from filename and then parse from json
	char *jsonString = GetStringFromFile(TextFormat("metadata/maps/%s", tilemapFile));
	cJSON *json = cJSON_Parse(jsonString);

	// Get tileset count ang firstgids in a single tm file
	cJSON *tilesets = cJSON_GetObjectItem(json, "tilesets");
	cJSON *tileset = NULL;
	tm.tsCount = cJSON_GetArraySize(tilesets);
	tm.firstgids = malloc(tm.tsCount * sizeof(int));
	if (tm.firstgids == NULL) {printf("Memory error (firstgid)\n"); return;}

	// Load tileset from each tileset mentioned in tm file
	int tsIndex = 0;
	int tIndex = 0;
	cJSON_ArrayForEach(tileset, tilesets)
	{
		cJSON *firstgid = cJSON_GetObjectItem(tileset, "firstgid");
		tm.firstgids[tsIndex] = firstgid->valueint;

		// Laod each tileset json
		cJSON *source = cJSON_GetObjectItem(tileset, "source");
		char *tsJSONString = GetStringFromFile(source->valuestring);
		cJSON *tsJSON = cJSON_Parse(tsJSONString);

		// Get all tiles from a tileset
		cJSON *tiles = cJSON_GetObjectItem(tsJSON, "tiles");
		cJSON *tile = NULL;
		tileCount += cJSON_GetArraySize(tiles);

		// Allocate memory to holds all tiles data
		if (ts == NULL)
		{
			ts = malloc(tileCount * sizeof(Tile));
			if (ts == NULL) {printf("Memory error (tileset)\n"); return;}
		}
		else
		{
			Tile *temp = realloc(ts, tileCount * sizeof(Tile));
			if (temp == NULL) {printf("Memory error (re:tileset)\n"); return;}
			ts = temp;
		}

		// Iterate on each tile in tiles object and get all of its information
		cJSON_ArrayForEach(tile, tiles)
		{
			ts[tIndex].lid = atoi(tile->string);
			ts[tIndex].gid = ts[tIndex].lid + tm.firstgids[tsIndex];

			// Get each tile type
			cJSON *type = cJSON_GetObjectItem(tile, "type");
			char *typeString = type->valuestring;
			ts[tIndex].tileType = malloc(strlen(typeString) + 1);
			if (ts[tIndex].tileType == NULL) {printf("Memory error (tileType)\n"); return;}
			strcpy(ts[tIndex].tileType, typeString);

			// Get each tile defined hitboxes
			cJSON *objectGroup = cJSON_GetObjectItem(tile, "objectgroup");
			if (objectGroup != NULL)
			{
				cJSON *objects = cJSON_GetObjectItem(objectGroup, "objects");
				cJSON *object = NULL;
				int objectCount = cJSON_GetArraySize(objects);

				// Allocate memory to holds each tile's hitboxes
				ts[tIndex].hitboxes = malloc(objectCount * sizeof(Hitbox));
				if (ts[tIndex].hitboxes == NULL) {printf("Memory error (hitboxes)\n"); return;}

				// Get all the tile's hitboxes
				ts[tIndex].hitboxCount = 0;
				int oIndex = 0;
				cJSON_ArrayForEach(object, objects)
				{
					cJSON *x = cJSON_GetObjectItem(object, "x");
					cJSON *y = cJSON_GetObjectItem(object, "y");
					cJSON *width = cJSON_GetObjectItem(object, "width");
					cJSON *height = cJSON_GetObjectItem(object, "height");
					cJSON *isCircle = cJSON_GetObjectItem(object, "ellipse");

					// Assign values to tile's hitboxes
					ts[tIndex].hitboxes[oIndex].rect.x = x->valueint;
					ts[tIndex].hitboxes[oIndex].rect.y = y->valueint;
					ts[tIndex].hitboxes[oIndex].rect.width = width->valueint;
					ts[tIndex].hitboxes[oIndex].rect.height = height->valueint;
					ts[tIndex].hitboxCount++;
					if (isCircle == NULL)
					{
						ts[tIndex].hitboxes[oIndex].isCircle = false;
					}
					else
					{
						ts[tIndex].hitboxes[oIndex].isCircle = (bool)isCircle->valueint;
					}
					oIndex++;
				}
			}

			// Make sure to initialize tiles that has no hitbox
			else
			{
				ts[tIndex].hitboxCount = 0;
				ts[tIndex].hitboxes = NULL;
			}
			tIndex++;
		}

		// Free memory for each json file loaded and increase index
		free(tsJSONString);
		cJSON_Delete(tsJSON);
		tsIndex++;
	}

	// Get layers and layer count of tilemap
	cJSON *layers = cJSON_GetObjectItem(json, "layers");
	cJSON *layer = NULL;
	tm.layerCount = cJSON_GetArraySize(layers);
	tm.layers = malloc(tm.layerCount * sizeof(TilemapLayer));
	if (tm.layers == NULL) {printf("Memory error (layers)\n"); return;}
	int layerIndex = 0;
	cJSON_ArrayForEach(layer, layers)
	{
		cJSON *name = cJSON_GetObjectItem(layer, "name");
		tm.layers[layerIndex].layerName = malloc(strlen(name->valuestring) + 1);
		if (!tm.layers[layerIndex].layerName) {printf("Memory error (tileType)\n"); return;}
		strcpy(tm.layers[layerIndex].layerName, name->valuestring);

		// Get all objects each layer has
		cJSON *objects = cJSON_GetObjectItem(layer, "objects");
		cJSON *object = NULL;
		tm.layers[layerIndex].objectCount = cJSON_GetArraySize(objects);
		tm.layers[layerIndex].objects = calloc(tm.layers[layerIndex].objectCount, sizeof(Object));
		if (!tm.layers[layerIndex].objects) {printf("Memory error (objects)\n"); return;}
		int oIndex = 0;
		cJSON_ArrayForEach(object, objects)
		{
			// Get gid and rectangle each object has
			cJSON *gid = cJSON_GetObjectItem(object, "gid");
			cJSON *x = cJSON_GetObjectItem(object, "x");
			cJSON *y = cJSON_GetObjectItem(object, "y");
			cJSON *width = cJSON_GetObjectItem(object, "width");
			cJSON *height = cJSON_GetObjectItem(object, "height");
			tm.layers[layerIndex].objects[oIndex].rect.x = x->valueint;
			tm.layers[layerIndex].objects[oIndex].rect.y = y->valueint;
			tm.layers[layerIndex].objects[oIndex].rect.width = width->valueint;
			tm.layers[layerIndex].objects[oIndex].rect.height = height->valueint;
			if (gid != NULL)
			{
				tm.layers[layerIndex].objects[oIndex].hasgid = true;
				tm.layers[layerIndex].objects[oIndex].gid = gid->valueint;
			}
			else
			{
				tm.layers[layerIndex].objects[oIndex].hasgid = false;
			}

			// Get each object properties
			cJSON *properties = cJSON_GetObjectItem(object, "properties");
			ObjectProperty props = { -1, -1 };
			if (properties != NULL)
			{
				cJSON *checkpoint = cJSON_GetObjectItem(properties, "checkpoint");
				cJSON *spawnpoint = cJSON_GetObjectItem(properties, "spawnpoint");
				if (checkpoint) props.checkpoint = checkpoint->valueint;
				if (spawnpoint) props.spawnpoint = spawnpoint->valueint;
			}
			tm.layers[layerIndex].objects[oIndex].properties = props;
			oIndex++;
		}
		layerIndex++;
	}

	// Delete JSON
	cJSON_Delete(json);
	free(jsonString);
}

void PlaceObjects(void)
{
	// Initialize physical properties template before entering creation loop
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.isAwake = false;
	bodyDef.type = b2_staticBody;
	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.material.friction = 0.3;
	shapeDef.material.restitution = 0.4;
	b2Polygon polygonShape;
	b2Circle circleShape;
	InitCheckpoint();

	// Place building and all graphics along with their hitboxes, else...
	for (int lIndex = 0; lIndex < tm.layerCount; lIndex++)
	{
		if (strcmp(tm.layers[lIndex].layerName, "graphics") == 0)
		{
			// Alocate memory to store body ids
			if (bodyIds == NULL)
			{
				bodyIds = malloc(tm.layers[lIndex].objectCount * sizeof(b2BodyId));
				if (bodyIds == NULL) printf("Can't allocate memory (bodyIds)\n");
			}
			else
			{
				b2BodyId *temp = realloc
				(
					bodyIds, tm.layers[lIndex].objectCount * sizeof(b2BodyId)
				);
				if (temp == NULL) printf("Can't allocate memory (bodyIds)\n");
				bodyIds = temp;
				temp = NULL;
			}

			// Create every object inside this loop
			for (int oIndex = 0; oIndex < tm.layers[lIndex].objectCount; oIndex++)
			{
				// Create body for that object
				Object currentObject = tm.layers[lIndex].objects[oIndex];
				bodyDef.position = (b2Vec2)
				{
					(float)currentObject.rect.x + (float)currentObject.rect.width * 0.5f,
					(float)currentObject.rect.y + (float)currentObject.rect.height * 0.5f
				};
				bodyIds[oIndex] = b2CreateBody(GetWorldId(), &bodyDef);
				bodyCount++;

				// Process lid index of tileset to place hitboxes
				int tilesetIndex = GetTilesetIndex(tm.layers[lIndex].objects[oIndex].gid);
				for (int hbIndex = 0; hbIndex < ts[tilesetIndex].hitboxCount; hbIndex++)
				{
					Hitbox currentHitbox = ts[tilesetIndex].hitboxes[hbIndex];
					if (currentHitbox.isCircle)
					{
						circleShape = (b2Circle)
						{
							{ 0.0f, 0.0f},
							(float)currentHitbox.rect.width * 0.5f
						};
						b2CreateCircleShape(bodyIds[oIndex], &shapeDef, &circleShape);
					}
					else
					{
						polygonShape = b2MakeBox
						(
							(float)currentHitbox.rect.width * 0.5f,
							(float)currentHitbox.rect.height * 0.5f
						);
						b2CreatePolygonShape(bodyIds[oIndex], &shapeDef, &polygonShape);
					}
				}
			}
		}

		// Place checkpoints and spawnpoint on map
		else if (strcmp(tm.layers[lIndex].layerName, "invisible") == 0)
		{
			for (int oIndex = 0; oIndex < tm.layers[lIndex].objectCount; oIndex++)
			{
				Object *currentObject = tm.layers[lIndex].objects + oIndex;

				// Make shape for checkpoints
				if (currentObject->properties.checkpoint > -1)
				{
					CreateCheckpoint
					(
						currentObject->rect, 0.0f, BOX,
						currentObject->properties.checkpoint
					);
				}

				// Locate spawnpoints
				else if (currentObject->properties.spawnpoint > -1)
				{
					spawnCount++;

					// Allocate memory for spawnpoint to place it to map
					if (!sps) sps = malloc(sizeof(Spawnpoint));
					if (!sps) {printf("Memory error (spawnpoint)\n"); return;}
					else
					{
						Spawnpoint *temp = realloc(sps, spawnCount * sizeof(Spawnpoint));
						if (!temp) {printf("Memory error (re:spawnpoint)\n"); return;}
						sps = temp;
					}

					// Make initialization to "that" spawnpoint
					sps[spawnCount - 1].id = currentObject->properties.spawnpoint;
					sps[spawnCount - 1].pos.x = currentObject->rect.x;
					sps[spawnCount - 1].pos.y = currentObject->rect.y;
				}
			}
		}
	}
}

void DrawMap(void)
{
	for (int lIndex = 0; lIndex < tm.layerCount; lIndex++)
	{
		if (strcmp(tm.layers[lIndex].layerName, "graphics") == 0)
		{
			for (int oIndex = 0; oIndex < tm.layers[lIndex].objectCount; oIndex++)
			{
				Object currentObject = tm.layers[lIndex].objects[oIndex];
				int tilesetIndex = GetTilesetIndex(currentObject.gid);
				Vector2 pos = { currentObject.rect.x, currentObject.rect.y };
				DrawSheetSection(ts[tilesetIndex].tileType, pos, Vector2Zero(), 0.0f, 1.0f, WHITE);
			}
		}
	}
}

void FreeMapDatas(void)
{
	// Free tilesets loaded along with the loaded tilemap
	for (int i = 0; i < tileCount; i++)
	{
		free(ts[i].tileType);
		free(ts[i].hitboxes);
	}
	free(ts);

	// Free tilemap which loaded to memory
	free(tm.firstgids);
	for (int i = 0; i < tm.layerCount; i++)
	{
		free(tm.layers[i].layerName);
		free(tm.layers[i].objects);
	}
	free(tm.layers);
}

void DestroyMapBodies(void)
{
	// Destroy all bodyIds that was made
	for (int i = 0; i < bodyCount; i++)
	{
		b2DestroyBody(bodyIds[i]);
	}

	// Free checkpoint
	DestroyCheckpoint();

	// Free all spawnpoints
	free(sps);
}
/* --- ------------ --- */


/* --- Methods --- */

int GetTilesetIndex(int gid)
{
	for (int i = 0; i < tileCount; i++)
	{
		if (gid == ts[i].gid)
		{
			return i;
		}
	}
	return -1;
}

Spawnpoint GetSpawnpoint(int spawnId)
{
	for (int i = 0; i < spawnCount; i++)
	{
		int currentSpawnId = sps[i].id;
		if (currentSpawnId == spawnId) return sps[i];
	}
	return (Spawnpoint){ 0 };
}
/* --- ------- --- */
