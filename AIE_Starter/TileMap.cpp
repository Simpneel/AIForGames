#pragma once

#include "TileMap.h"

int defaultMap[20][20] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

TileMap::TileMap()
{
	grassTexture = LoadTexture("ref/grass.png");
	waterTexture = LoadTexture("ref/water.png");

	LoadMap(defaultMap);

	src.x = src.y = 0;
	src.width = dest.width = 32;	//setting default height & width to 32 based on size of textures
	src.height = dest.height = 32;
	dest.x = dest.y = 0;
}

TileMap::~TileMap()
{
	UnloadTexture(grassTexture);
	UnloadTexture(waterTexture);
}

void TileMap::LoadMap(int arr[20][20])
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			map[i][j] = arr[i][j];	//copy over given map into my object
		}
	}
}

void TileMap::DrawMap()
{
	int type = 0;
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			type = map[i][j];

			dest.x = i * 32;	//set position of texture to position of tile on the grid, multiplied by 32px for the size of the texture
			dest.y = j * 32;

			switch (type)
			{
			case 0:
				DrawTexturePro(grassTexture, src, dest, { 0,0 }, 0.0f, WHITE);
				break;
			case 1:
				DrawTexturePro(waterTexture, src, dest, { 0,0}, 0.0f, WHITE);
				break;
			/*case 2:

				break;
			case 3:

				break;*/
			default:
				break;
			}
		}
	}

}



