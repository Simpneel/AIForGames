#pragma once

#include "raylib.h"

class TileMap
{
public:

	TileMap();
	~TileMap();

	void LoadMap(int arr[20][20]);
	void DrawMap();

private:

	Rectangle src, dest;
	Texture2D grassTexture;
	Texture2D waterTexture;
	Texture2D brickTexture;

	int map[20][20];

};
