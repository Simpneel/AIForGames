#pragma once

#include "raylib.h"

class TileMap
{
public:

	TileMap();
	~TileMap();

	void LoadMap(int arr[20][20]);
	//void LoadMapFromFile(const char* fileName);
	void ChangeTextureAtMouseLoc(Vector2 mousePos, bool isEditorOpen);

	void SaveMapToFile();
	void LoadMapFromFile(const char* fileName);

	void DrawMap();

private:

	Rectangle src, dest;
	Texture2D grassTexture;
	Texture2D waterTexture;
	Texture2D brickTexture;
	Texture2D dirtTexture;

	int map[20][20];

};
