/* --- User-defined header files --- */

#include "texture.h"
/* --- ------------------------- --- */


/* --- Global static variables --- */

static Trie *textureDatas = NULL;
static Texture2D *textures = NULL;
static char **textureNames = NULL;
static int loadedTextureCount = 0;
static int loadedTileCount = 0;
/* --- ----------------------- --- */


/* --- Main methods --- */

void LoadTextureSheet(const char *filename)
{
	// Allocate memory for textures variable
	loadedTextureCount++;
	if (textures == NULL)
	{
		textures = calloc(1, sizeof(Texture2D));
		textureNames = malloc(sizeof(char *));
		if (textures == NULL || textureNames == NULL) printf("Failed to load texture");
	}
	else
	{
		Texture2D *tempT = realloc(textures, loadedTextureCount * sizeof(Texture2D));
		char **tempN = realloc(textureNames, loadedTextureCount * sizeof(char *));
		if (tempT == NULL || tempN == NULL) printf("Failed to load texture\n");
		textures = tempT;
		textureNames = tempN;
	}
	textures[loadedTextureCount - 1] = LoadTexture(TextFormat("assets/%s.png", filename));
	textureNames[loadedTextureCount - 1] = malloc(strlen(filename) * sizeof(char) + 1);
	if (!textureNames[loadedTextureCount - 1]) printf("Failed to load texture name\n");
	strcpy(textureNames[loadedTextureCount - 1], filename);

	// Allocate memory for textureDatas trie
	if (!textureDatas) textureDatas = CreateTrie();

	// Process JSON from filename
	char *jsonString = GetStringFromFile(TextFormat("assets/metadata/%s.json", filename));
	cJSON *json = cJSON_Parse(jsonString);
	cJSON *frames = cJSON_GetObjectItem(json, "frames");
	cJSON *textureName = NULL;
	int frameCount = cJSON_GetArraySize(frames);
	loadedTileCount += frameCount;

	// Assign data to each entry of textureDatas array
	cJSON_ArrayForEach(textureName, frames)
	{
		cJSON *frame = cJSON_GetObjectItem(textureName, "frame");
		cJSON *x = cJSON_GetObjectItem(frame, "x");
		cJSON *y = cJSON_GetObjectItem(frame, "y");
		cJSON *w = cJSON_GetObjectItem(frame, "w");
		cJSON *h = cJSON_GetObjectItem(frame, "h");
		TextureData *texDatEach = malloc(sizeof(TextureData));
		if (!texDatEach) {printf("Failed to load tile\n"); return;}
		*texDatEach = (TextureData)
		{
			{x->valueint, y->valueint, w->valueint, h->valueint},
			loadedTextureCount - 1
		};
		char tempstr[32];
		strcpy(tempstr, textureName->string);
		TruncateString(tempstr, -4);
		InsertTrie(textureDatas, tempstr, (void *)texDatEach);
	}

	// Free memories
	free(jsonString);
	cJSON_Delete(json);
}

void DrawSheetSection(char *file, Vector2 pos, Vector2 origin, float rot, Color tint)
{
	char tempstr[32];
	strcpy(tempstr, file);
	TruncateString(tempstr, -4);
	TextureData *data = (TextureData *)SearchTrie(textureDatas, tempstr);
	Rectangle destRec = { pos.x, pos.y, data->rect.width, data->rect.height };
	DrawTexturePro(textures[data->textureIndex], data->rect, destRec, origin, rot, tint);
	return;
}

void FreeAllTextures(void)
{
	for (int i = 0; i < loadedTextureCount; i++)
	{
		if (textures + i)
		{
			UnloadTexture(textures[i]);
			free(textureNames[i]);
		}
	}
	free(textureNames);
	free(textures);
	FreeTrie(textureDatas);
	loadedTextureCount = 0;
	loadedTileCount = 0;
}
/* --- ------------ --- */


/* --- Methods --- */

TextureData *GetSheetData(char *file)
{
	char tempstr[32];
	strcpy(tempstr, file);
	TruncateString(tempstr, -4);
	TextureData *val = (TextureData *)SearchTrie(textureDatas, tempstr);
	if (val) return val;
	return NULL;
}
/* --- ------- --- */
