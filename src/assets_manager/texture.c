/* --- User-defined header files --- */

#include "texture.h"
/* --- ------------------------- --- */


/* --- Global static variables --- */

static Trie *sheetDatas = NULL;
static Trie *textureDatas = NULL;
static Texture2D *sheets = NULL;
static int loadedTextureCount = 0;
static int loadedTileCount = 0;
/* --- ----------------------- --- */


/* --- Main methods --- */

void LoadTextureSheet(char *filename)
{
	loadedTextureCount++;

	// Allocate memory for (sheetDatas), (textureDatas) trie, and (sheets) array
	if (!sheetDatas) sheetDatas = CreateTrie();
	if (!textureDatas) textureDatas = CreateTrie();
	if (!sheets) sheets = malloc(sizeof(Texture2D));
	else sheets = realloc(sheets, loadedTextureCount * sizeof(Texture2D));
	if (!sheets) return;

	// Process JSON from (filename)
	char *jsonString = GetStringFromFile(TextFormat("assets/metadata/%s.json", filename));
	cJSON *json = cJSON_Parse(jsonString);
	cJSON *frames = cJSON_GetObjectItem(json, "frames");
	cJSON *textureName = NULL;
	int frameCount = cJSON_GetArraySize(frames);
	loadedTileCount += frameCount;

	// Get and carry texture sheet information
	SheetData *currentSheet = malloc(sizeof(SheetData));
	if (!currentSheet) return;
	sheets[loadedTextureCount - 1] = LoadTexture(TextFormat("assets/%s.png", filename));
	currentSheet->sheet = sheets[loadedTextureCount - 1];
	currentSheet->tileCount = frameCount;

	// Insert texture sheet information into trie
	char *tempstr = malloc(strlen(filename) + 1);
	if (!tempstr) return;
	TruncateString(strcpy(tempstr, filename), -6);
	InsertTrie(sheetDatas, tempstr, currentSheet);
	free(tempstr);

	// Assign data to each entry of textureDatas array
	cJSON_ArrayForEach(textureName, frames)
	{
		cJSON *frame = cJSON_GetObjectItem(textureName, "frame");
		cJSON *x = cJSON_GetObjectItem(frame, "x");
		cJSON *y = cJSON_GetObjectItem(frame, "y");
		cJSON *w = cJSON_GetObjectItem(frame, "w");
		cJSON *h = cJSON_GetObjectItem(frame, "h");

		// Make space for  temporary texture tile data extraction
		TextureData *texDatEach = malloc(sizeof(TextureData));
		if (!texDatEach) return;
		texDatEach->rect = (Rectangle){ x->valueint, y->valueint, w->valueint, h->valueint };
		texDatEach->textureIndex = loadedTextureCount - 1;

		// Insert tile informations to trie
		char *tempstr = malloc(strlen(textureName->string) + 1);
		if (!tempstr) return;
		TruncateString(strcpy(tempstr, textureName->string), -4);
		InsertTrie(textureDatas, tempstr, texDatEach);
		free(tempstr);
	}

	// Free memories
	free(jsonString);
	cJSON_Delete(json);
}

uint1 SimpleDrawSheet(char *file, Vector2 pos, float rotation, float scale, Color tint)
{
	char tempstr[32];
	strcpy(tempstr, file);
	TruncateString(tempstr, -4);
	TextureData *data = (TextureData *)SearchTrie(textureDatas, tempstr);
	if (!data) return 0;
	Vector2 destExtent = { data->rect.width * .5f * scale, data->rect.height * .5f * scale };
	Rectangle destRec =
	{
		pos.x,
		pos.y,
		(float)data->rect.width * scale,
		(float)data->rect.height * scale
	};
	DrawTexturePro(sheets[data->textureIndex], data->rect, destRec, destExtent, rotation, tint);
}

uint1 DrawSheetSection(char *file, Vector2 pos, Vector2 origin, float rot, float scale, Color tint)
{
	char tempstr[32];
	strcpy(tempstr, file);
	TruncateString(tempstr, -4);
	TextureData *data = (TextureData *)SearchTrie(textureDatas, tempstr);
	if (!data) return 0;
	Rectangle destRec = { pos.x, pos.y, (float)data->rect.width * scale, (float)data->rect.height * scale };
	DrawTexturePro(sheets[data->textureIndex], data->rect, destRec, origin, rot, tint);
	return 1;
}

void FreeTexture(char *filename)
{
	SheetData *buffer = (SheetData *)SearchTrie(sheetDatas, filename);
	if (buffer) UnloadTexture(buffer->sheet);
}

void ClearTextures(void)
{
	FreeTrie(sheetDatas);
	FreeTrie(textureDatas);
	loadedTextureCount = 0;
	loadedTileCount = 0;
}

TextureData *GetTileData(char *file)
{
	char *tempstr = malloc(strlen(file) + 1);
	if (!tempstr) {printf("Failed to load tile texture\n"); return NULL;}
	strcpy(tempstr, file);
	TruncateString(tempstr, -4);
	TextureData *val = (TextureData *)SearchTrie(textureDatas, tempstr);
	if (val) return val;
	free(tempstr);
	return NULL;
}

SheetData *GetSheetData(char *cutFilename)
{
	SheetData *buffer = (SheetData *)SearchTrie(sheetDatas, cutFilename);
	if (!buffer) return NULL;
}
/* --- ------------ --- */
