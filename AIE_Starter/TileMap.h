#pragma once

#include "raylib.h"

#define TM_ROWS 20

#define TM_COLS 20

class TileMap
{
public:

	TileMap();
	~TileMap();


	void LoadMap(int arr[TM_ROWS][TM_COLS]);
	//void LoadMapFromFile(const char* fileName);
	void ChangeTextureAtMouseLoc(Vector2 mousePos, bool isEditorOpen);

	void SaveMapToFile(char saveName[15]);
	void LoadMapFromFile(const char* fileName);
	
	void DrawMap();
	
	float tileSize;
	int map[TM_ROWS][TM_COLS];
private:

	Rectangle src, dest;
	Texture2D grassTexture;
	Texture2D waterTexture;
	Texture2D brickTexture;
	Texture2D dirtTexture;
};