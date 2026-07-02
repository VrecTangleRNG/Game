/* --- Header files --- */

#include "level.h"
/* --- ------------ --- */


/* --- Static global variables --- */

static Level *runningLevel = NULL;
static Level *levels = NULL;
static uint2 levelCount = 0;
/* --- ----------------------- --- */


/* --- Main function definition --- */

void LoadCurrentLevel(char *tilemapFile, char *levelFile)
{
    // Load level data from file
    char *levelString = GetStringFromFile(TextFormat("metadata/levels/%s", levelFile));
    cJSON *json = cJSON_Parse(levelString);

    // Extract data inside json
    int levelIndex = 0;
    cJSON *type = cJSON_GetObjectItem(json, "type");
    cJSON *worlds = cJSON_GetObjectItem(json, "worlds");
    cJSON *world = NULL;
    cJSON_ArrayForEach(world, worlds)
    {
        cJSON *source = cJSON_GetObjectItem(world, "source");

        // Check for loading level in a matching world
        if (strcmp(source->valuestring, TextFormat("metadata/maps/%s", tilemapFile)) == 0)
        {
            cJSON *levelsJSON = cJSON_GetObjectItem(world, "levels");
            cJSON *level = NULL;
            levelCount = cJSON_GetArraySize(levelsJSON);

            // Allocate memory for levels container
            if (!levels) levels = malloc(sizeof(Level));
            else
            {
                Level *temp = realloc(levels, levelCount * sizeof(Level));
                if (!temp) {printf("Memory error (level)"); return;}
                else levels = temp;
            }
            if (!levels) {printf("Memory error (level)"); return;}

            // Extract level datas
            cJSON_ArrayForEach(level, levelsJSON)
            {
                cJSON *name = cJSON_GetObjectItem(level, "name");
                cJSON *spawnpoint = cJSON_GetObjectItem(level, "spawnpoint");
                cJSON *angle = cJSON_GetObjectItem(level, "angle");
                cJSON *checkpoints = cJSON_GetObjectItem(level, "checkpoints");
                int checkpointCount = cJSON_GetArraySize(checkpoints);

                // Allocate memory to holds all checkpoint ids
                levels[levelIndex].checkpointIds = malloc(checkpointCount * sizeof(uint2));
                if (!levels[levelIndex].checkpointIds)
                {
                    printf("Memory error (level)");
                    return;
                }

                // Save the values from json to level container
                levels[levelIndex].cpIdCount = 0;
                for (int i = 0; i < checkpointCount; i++)
                {
                    int cpId = cJSON_GetArrayItem(checkpoints, i)->valueint;
                    levels[levelIndex].checkpointIds[i] = cpId;
                    levels[levelIndex].cpIdCount++;
                    // DEBUG: printf("cpId: %d, i: %d\n", levels[levelIndex].checkpointIds[i], i);
                }
                levels[levelIndex].mode = type->valueint;
                levels[levelIndex].angle = angle->valuedouble;
                levels[levelIndex].spawnpointId = spawnpoint->valueint;
                strcpy(levels[levelIndex].name, name->valuestring);
                levelIndex++;
            }
        }
    }

    // Free memory
    free(levelString);
    cJSON_Delete(json);
}
/* --- ------------------------ --- */


/* --- Main Methods --- */

void SetRunningLevelIndex(int levelIndex)
{
    runningLevel = levels + levelIndex;
}

Level *GetRunningLevel(void)
{
    return runningLevel;
}

void UnloadCurrentLevel(void)
{
    for (int i = 0; i < levelCount; i++)
    {
        free(levels[i].checkpointIds);
    }
    free(levels);
}
/* --- ------------ --- */


/* --- Game Mode exclusive functions --- */

void InitLapTracker(LapTracker *lap, Level *level)
{
    lap->currentLap = 1;
    lap->firstIteration = false;
    lap->currentCpIndex = 0;
    lap->currentCp = level->checkpointIds[0];
}

void RunLapTracker(LapTracker *lap, Level *level, b2ShapeId *targetShape)
{
    b2ShapeId *cpShape = CheckSensorCollision(targetShape, NULL, 1);
    b2ShapeId *targetCpShape = GetCpShapeFromId(lap->currentCp);
    if (cpShape != NULL && B2_ID_EQUALS(*cpShape, *targetCpShape))
    {
        // printf("Before: currentLap: %d, currentCp: %d, currentCpIndex: %d\n", lap->currentLap, lap->currentCp, lap->currentCpIndex);
        if (lap->currentCpIndex == 0 && lap->firstIteration)
        {
            lap->currentLap++;
        }
        lap->firstIteration = true;
        lap->currentCpIndex = (lap->currentCpIndex + 1) % (level->cpIdCount - 1);
        lap->currentCp = level->checkpointIds[lap->currentCpIndex];
        // printf("cpIdCount: %d\n", level->cpIdCount);
        // printf("After: currentLap: %d, currentCp: %d, currentCpIndex: %d\n\n", lap->currentLap, lap->currentCp, lap->currentCpIndex);
    }
}
/* --- ----------------------------- --- */
