/* --- Header files --- */

#include "level.h"
/* --- ------------ --- */


/* --- Static global variables --- */

static Level *runningLevel = NULL;
static Level *levels = NULL;    // TODO: not yet freed
static int levelCount = 0;
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
        if (strcmp(source->valuestring, tilemapFile) == 0)
        {
            cJSON *levelsJSON = cJSON_GetObjectItem(world, "levels");
            cJSON *level = NULL;
            int levelCount = cJSON_GetArraySize(levelsJSON);

            // Allocate memory for levels container
            if (!levels) levels = malloc(sizeof(Level));
            else
            {
                Level *temp = realloc(levels, levelCount * sizeof(Level));
                if (!temp) {printf("Memory error (level)"); return;}
                levels = temp;
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
                levels[levelIndex].checkpointIds = malloc(checkpointCount * sizeof(int));
                if (!levels[levelIndex].checkpointIds)
                {
                    printf("Memory error (level)");
                    return;
                }

                // Save the values from json to level container
                for (int i = 0; i < checkpointCount; i++)
                {
                    int cpId = cJSON_GetArrayItem(checkpoints, i)->valueint;
                    levels[levelIndex].checkpointIds[i] = cpId;
                }
                levels[levelIndex].mode = type->valueint;
                levels[levelIndex].angle = angle->valuedouble;
                levels[levelIndex].spawnpointId = spawnpoint->valueint;
                strcpy(levels[levelIndex].name, name->valuestring);
                levelIndex++;
            }
        }
    }
    levelCount = levelIndex;

    // Free memory
    free(levelString);
    cJSON_Delete(json);
}
/* --- ------------------------ --- */


/* --- Main Methods --- */

void SetRunningLevelIndex(int levelIndex)
{
    runningLevel = &(levels[levelIndex]);
}

Level *GetRunningLevel(void)
{
    return runningLevel;
}
/* --- ------------ --- */
