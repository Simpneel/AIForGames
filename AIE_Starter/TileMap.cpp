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
	Image grassImg = LoadImage("ref/grass.png");
	Image dirtImg = LoadImage("ref/dirt.png");
	Image brickImg = LoadImage("ref/brick.png");
	Image waterImg = LoadImage("ref/water.png");
	tileSize = 32;

	grassTexture = LoadTextureFromImage(grassImg);
	dirtTexture = LoadTextureFromImage(dirtImg);
	brickTexture = LoadTextureFromImage(brickImg);
	waterTexture = LoadTextureFromImage(waterImg);

	UnloadImage(grassImg);
	UnloadImage(dirtImg);
	UnloadImage(brickImg);
	UnloadImage(waterImg);

	int brickwaterCounter = 0;

	int tempMap[TM_ROWS][TM_COLS];
	for (int i = 0; i < TM_ROWS; i++) {
		for (int j = 0; j < TM_COLS; j++) {
			tempMap[i][j] = GetRandomValue(0, 3);
			if (tempMap[i][j] == 2 || tempMap[i][j] == 3) brickwaterCounter++;
			if (brickwaterCounter > 2) tempMap[i][j] = brickwaterCounter = 0;
		}
	}

	LoadMap(tempMap);

	src.x = src.y = 0;
	src.width = dest.width = tileSize;	//setting default height & width to tileSize; based on size of textures
	src.height = dest.height = tileSize;
	dest.x = dest.y = 0;
}

TileMap::~TileMap()
{
	UnloadTexture(grassTexture);
	UnloadTexture(waterTexture);
	UnloadTexture(brickTexture);
	UnloadTexture(dirtTexture);
}

void TileMap::LoadMap(int arr[TM_ROWS][TM_COLS])
{
	for (int i = 0; i < TM_ROWS; ++i)
	{
		for (int j = 0; j < TM_COLS; ++j)
		{
			map[i][j] = arr[i][j];	//copy over given map into my object
		}
	}
}

void TileMap::ChangeTextureAtMouseLoc(Vector2 mousePos, bool isEditorOpen)
{
	if (isEditorOpen)
	{
		int mapWidth = TM_COLS * tileSize;
		int mapHeight = TM_ROWS * tileSize;

		DrawText("Texture Atlas:", (mapWidth + 20), 20, 3, ORANGE);

		DrawTexture(grassTexture, (mapWidth + 20), 40, WHITE); DrawText("Grass: 1", (mapWidth + 55), 45, 2, RAYWHITE);

		DrawTextureTiled(dirtTexture, Rectangle{},
			Rectangle{}, Vector2{},
			0.0f, 0.5f, WHITE);

		DrawTexture(dirtTexture, (mapWidth + 20), 80, WHITE); DrawText("Dirt: 2", (mapWidth + 55), 85, 2, RAYWHITE);

		DrawTexture(brickTexture, (mapWidth + 20), 120, WHITE); DrawText("Brick: 3", (mapWidth + 55), 125, 2, RAYWHITE);

		DrawTexture(waterTexture, (mapWidth + 20), 160, WHITE); DrawText("Water: 4", (mapWidth + 55), 165, 2, RAYWHITE);
		
		DrawText("S- Save edited map to file", (mapWidth + 20), 200, 3, ORANGE);
		DrawText("L- Load map from file", (mapWidth + 20), 240, 3, ORANGE);

		if (IsKeyDown(KEY_ONE))
		{
			map[(int)(mousePos.y / tileSize)][(int)(mousePos.x / tileSize)] = 0;
		}
		else if (IsKeyDown(KEY_TWO))
		{
			map[(int)(mousePos.y / tileSize)][(int)(mousePos.x / tileSize)] = 1;
		}
		else if (IsKeyDown(KEY_THREE))
		{
			map[(int)(mousePos.y / tileSize)][(int)(mousePos.x / tileSize)] = 2;
		}
		else if (IsKeyDown(KEY_FOUR))
		{
			map[(int)(mousePos.y / tileSize)][(int)(mousePos.x / tileSize)] = 3;
		}
	}
	LoadMap(map);
}

void TileMap::SaveMapToFile(char savename[15])
{
	std::fstream mapSaveFile;
	mapSaveFile.open("tileMapSaved.txt", std::ios::out);
	if (mapSaveFile.is_open()) {
		for (int i = 0; i < TM_ROWS; ++i)
		{
			for (int j = 0; j < TM_COLS; ++j)
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
	char temp[TM_ROWS][TM_COLS*2 + 1];  // Allocate memory for 20 strings of up to 20 characters each 
	
	file.open("tileMapSaved.txt", std::ios::in);
	if (file.is_open())
	{
		for (int i = 0; i < TM_ROWS; ++i)
		{
			file.getline(temp[i], 41);  // 41 to account for the commas & null pointer at the end
		}
	}
	else std::cout << "Error accessing save file\n";
	file.close();
	
	for (int i = 0; i < TM_ROWS; ++i)	
	{ 
		int x = 0;
		for (int j = 0; j < (TM_COLS * 2 + 1); j++) {
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
	for (int i = 0; i < TM_ROWS; ++i)
	{
		for (int j = 0; j < TM_COLS; ++j)
		{
			type = map[i][j];

			dest.x = j * tileSize;	//set texture destination rect to the pos of the grid tile, multiplied by 32 for the texture pixel size
			dest.y = i * tileSize;

			switch (type)
			{
			case 0:
				DrawTexturePro(grassTexture, src, dest, { 0,0 }, 0.0f, WHITE);
				break;
			case 1:
				DrawTexturePro(dirtTexture, src, dest, { 0,0}, 0.0f, WHITE);
				break;
			case 2:
				DrawTexturePro(brickTexture, src, dest, { 0,0 }, 0.0f, BEIGE);
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