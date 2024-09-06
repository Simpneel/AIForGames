#include "TileMap.h"
#include <fstream>
#include <iostream>
#include <charconv>

int defaultMap[20][20] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0},
	{0,0,3,3,2,2,2,2,2,3,3,0,0,0,0,0,0,0,0,0},
	{0,0,3,2,1,1,1,1,1,2,3,0,0,0,0,0,0,0,0,0},
	{0,0,3,3,2,1,1,1,1,2,3,3,0,0,0,0,0,0,0,0},
	{0,0,3,3,3,2,1,1,1,2,3,3,3,0,0,0,0,0,0,0},
	{0,0,3,3,3,3,2,1,1,1,2,3,3,0,0,0,0,0,0,0},
	{0,0,3,3,3,3,3,2,1,1,1,2,3,0,0,0,0,0,0,0},
	{0,0,0,3,3,3,3,3,2,2,2,3,3,0,0,0,0,0,0,0},
	{0,0,0,0,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0},
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
	brickTexture = LoadTexture("ref/brick.png");
	dirtTexture = LoadTexture("ref/dirt.png");

	int brickwaterCounter = 0;

	int tempMap[20][20];
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			tempMap[i][j] = GetRandomValue(0, 3);
			if (tempMap[i][j] == 2 || tempMap[i][j] == 3) brickwaterCounter++;
			if (brickwaterCounter > 3) tempMap[i][j] = brickwaterCounter = 0;
		}
	}

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
	UnloadTexture(brickTexture);
	UnloadTexture(dirtTexture);
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

void TileMap::ChangeTextureAtMouseLoc(Vector2 mousePos, bool isEditorOpen)
{
	if (isEditorOpen)
	{
		DrawText("Texture Atlas:", 650, 20, 3, ORANGE);
		DrawTexture(grassTexture, 650, 40, WHITE); DrawText("Grass: 1", 700, 40, 2, RAYWHITE);

		DrawTexture(dirtTexture, 650, 80, WHITE); DrawText("Dirt: 2", 700, 80, 2, RAYWHITE);

		DrawTexture(brickTexture, 650, 120, WHITE); DrawText("Brick: 3", 700, 120, 2, RAYWHITE);

		DrawTexture(waterTexture, 650, 160, WHITE); DrawText("Water: 4", 700, 160, 2, RAYWHITE);
		
		DrawText("S- Save edited map to file", 650, 200, 3, ORANGE);
		DrawText("L- Load map from file", 650, 240, 3, ORANGE);

		if (IsKeyDown(KEY_ONE))
		{
			map[(int)mousePos.y / 32][(int)mousePos.x / 32] = 0;
		}
		else if (IsKeyDown(KEY_TWO))
		{
			map[(int)mousePos.y / 32][(int)mousePos.x / 32] = 1;
		}
		else if (IsKeyDown(KEY_THREE))
		{
			map[(int)mousePos.y / 32][(int)mousePos.x / 32] = 2;
		}
		else if (IsKeyDown(KEY_FOUR))
		{
			map[(int)mousePos.y / 32][(int)mousePos.x / 32] = 3;
		}
	}
	LoadMap(map);
}

void TileMap::SaveMapToFile()
{
	std::fstream mapSaveFile;
	mapSaveFile.open("tileMapSaved.txt", std::ios::out);
	if (mapSaveFile.is_open()) {
		for (int i = 0; i < 20; ++i)
		{
			for (int j = 0; j < 20; ++j)
			{
				mapSaveFile << (map[i][j]) << ",";
			}
			mapSaveFile << std::endl;
		}
		std::cout << "Saved tile map to text document successfully!\n";
	}
	else
	{
		std::cout << "SAVE FILE OPEN ERROR\n";
	}
	mapSaveFile.close();
}

void TileMap::LoadMapFromFile(const char* fileName)
{
	std::fstream file;
	char temp[20][41];  // Allocate memory for 20 strings of up to 20 characters each 
	
	file.open("tileMapSaved.txt", std::ios::in);
	if (file.is_open())
	{
		for (int i = 0; i < 20; ++i)
		{
			file.getline(temp[i], 41);  // 41 to account for the commas & null pointer at the end
		}
	}
	else std::cout << "Error accessing save file\n";
	file.close();
	
	for (int i = 0; i < 20; ++i)	
	{ 
		int x = 0;
		for (int j = 0; j < 41; j++) {
			if (j % 2 != 0)
			{
				std::from_chars(temp[i] + j - 1, temp[i] + j, map[i][x]);	
				std::cout << map[i][x];
				++x;
			}
		}
		std::cout << std::endl;
	}
	std::cout << "Loaded map from text file successfully!\n";
}

void TileMap::DrawMap()
{
	int type = 0;
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			type = map[i][j];

			dest.x = j * 32;	//set texture destination rect to the pos of the grid tile, multiplied by 32 for the texture pixel size
			dest.y = i * 32;

			switch (type)
			{
			case 0:
				DrawTexturePro(grassTexture, src, dest, { 0,0 }, 0.0f, WHITE);
				break;
			case 1:
				DrawTexturePro(dirtTexture, src, dest, { 0,0}, 0.0f, WHITE);
				break;
			case 2:
				DrawTexturePro(brickTexture, src, dest, { 0,0 }, 0.0f, PINK);
				break;
			case 3:
				DrawTexturePro(waterTexture, src, dest, { 0,0 }, 0.0f, WHITE);
				break;
			default:
				break;
			}
		}
	}

}