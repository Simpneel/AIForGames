#include "raylib.h"

//#define RAYGUI_IMPLEMENTATION
//#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "Pathfinding.h"
#include "PathAgent.h"
#include "Agent.h"
#include "Behaviour.h"
#include "TileMap.h"
#include <fstream>
#include <iostream>

using namespace AIForGames;

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = TM_ROWS * 32 + 200;
    int screenHeight = TM_COLS * 32 + 25;

    InitWindow(screenWidth, screenHeight, "AI For Games: Pathfinding");

    SetTargetFPS(60);

    float time = GetTime();
    float deltaTime;
    //--------------------------------------------------------------------------------------
   
    /*NodeMap nodeMap;
    std::vector<std::string> asciiMap;
    asciiMap.push_back("00000000000000000000");
    asciiMap.push_back("01111111111111111110");
    asciiMap.push_back("00000111110000001110");
    asciiMap.push_back("01101010101010101010");
    asciiMap.push_back("01111111111111111110");
    asciiMap.push_back("01001000011100001100");
    asciiMap.push_back("00001000000110000000");
    asciiMap.push_back("00011111100111110010");
    asciiMap.push_back("01111100000000011110");
    asciiMap.push_back("00010111111111110010");
    asciiMap.push_back("01110001111000000010");
    asciiMap.push_back("01000000010000000010");
    asciiMap.push_back("01111000111100011110");
    asciiMap.push_back("01110000001000111010");
    asciiMap.push_back("01110000001111100010");
    asciiMap.push_back("01000000000000100010");
    asciiMap.push_back("01000000000001111110");
    asciiMap.push_back("01111111111111100000");
    asciiMap.push_back("00000000011111100000");
    asciiMap.push_back("00000000000000000000");
    nodeMap.Initialise(asciiMap, 32);
    std::vector<Node*> nodeMapPath = NodeMap::DijkstrasSearch(start, end);*/

    //TileMap initialization
    TileMap *newMap = new TileMap();
    bool isEditorOpen = false;
    bool isNodeViewOpen = false;

    NodeMap tileNodeMap;
    tileNodeMap.Initialise(newMap, 32);

    Node* start = tileNodeMap.GetClosestNode({2,2});
    if (start == nullptr) start = tileNodeMap.GetClosestNode({10,10});
    Node* end = tileNodeMap.GetClosestNode({ 100,100 });
    if (end == nullptr) end = tileNodeMap.GetClosestNode({ 500,500 });
    
    std::vector<Node*> nodeMapPath = NodeMap::DijkstrasSearch(start, end);
    
    PathAgent newAgent;
    newAgent.SetNode(start);
    newAgent.SetSpeed(124);

    /*PathAgent pacman;
    pacman.SetAgentTexture(LoadTexture("ref/pacman.png"));
    pacman.SetNode(tileNodeMap.GetClosestNode({500,500}));
    pacman.SetSpeed(124);*/

    Agent agent(&tileNodeMap, new GoToPointBehaviour());

    Rectangle inputBox = { screenWidth / 2, screenHeight / 2, 100, 45 };
    bool mouseOnInputBox = false;
    int letterCount = 0;
    char saveFileName[17];

    newAgent.GoToNode(end);
    //pacman.GoToNode(end);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here

        /*float fTime = (float)GetTime();
        deltaTime = fTime - time;
        time = fTime;*/
        
        //----------------------------------------------------------------------------------
        if (IsMouseButtonPressed(0))
        {
            start = tileNodeMap.GetClosestNode(glm::vec2(GetMousePosition().x, GetMousePosition().y));
            if (end != nullptr) nodeMapPath = NodeMap::DijkstrasSearch(start, end);
            newAgent.SetNode(start); //resetting the search to now consider the mouse location as the starting node when user left clicks
            newAgent.GoToNode(end);
            
        }
        if (IsMouseButtonPressed(1))
        {
            end = tileNodeMap.GetClosestNode(glm::vec2(GetMousePosition().x, GetMousePosition().y));
            if (end == nullptr) exit;
            if (start != nullptr) nodeMapPath = NodeMap::DijkstrasSearch(start, end); //resetting the search to now consider the mouse location as the ending node when user right clicks
            newAgent.GoToNode(end);
            
        }
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(DARKGRAY);
        DrawFPS(screenWidth - 50, screenHeight - 25);

        DrawText("N - NodeMap View", 650, 580, 5, {15, 225, 255, 255});

        if (IsKeyPressed(KEY_E))   //editor mode, can be turned on and off by pressing 'E'
        {
            if (isEditorOpen)
            {
                isEditorOpen = false;
                tileNodeMap.Initialise(newMap, 32);
                nodeMapPath = NodeMap::DijkstrasSearch(start, end);
            }
            else isEditorOpen = true;
        }
        newMap->ChangeTextureAtMouseLoc(GetMousePosition(), isEditorOpen);

        newMap->DrawMap();
        if (IsKeyPressed(KEY_N))
        {
            if (isNodeViewOpen) isNodeViewOpen = false;
            else isNodeViewOpen = true;
        }

        if (isNodeViewOpen)
        {
            tileNodeMap.Draw();
            tileNodeMap.DrawPath(nodeMapPath, ORANGE, 4);
            NodeMap::DrawPath(newAgent.m_path, RED, 5);
        }

        if (start != nullptr && end != nullptr) {
            DrawCircle(start->position.x, start->position.y, 4, PINK);
            DrawCircle(end->position.x, end->position.y, 4, PINK);
        }

        newAgent.Update(/*deltaTime*/);
        newAgent.Draw();

        /*pacman.Update(deltaTime);
        pacman.Draw();*/
        
        if (IsKeyPressed(KEY_S))     
        {
            newMap->SaveMapToFile(saveFileName);
        }
        if (IsKeyPressed(KEY_L))
        {
            ClearBackground(DARKGRAY);
            newMap->LoadMapFromFile("tileMapSaved.txt");
            tileNodeMap.Initialise(newMap, 32);
        }

        EndDrawing();
        
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}