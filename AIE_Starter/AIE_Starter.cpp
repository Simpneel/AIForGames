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

    //TileMap initialization
    TileMap *newMap = new TileMap();
    bool isEditorOpen = false;
    bool isNodeViewOpen = false;

    NodeMap tileNodeMap;
    tileNodeMap.Initialise(newMap, 32);

    Node* start = tileNodeMap.GetClosestNode({2,2});
    if (!start) start = tileNodeMap.GetRandomNode();
    Node* end = tileNodeMap.GetClosestNode({ 100,100 });
    if (!end) end = tileNodeMap.GetRandomNode();
    
    std::vector<Node*> nodeMapPath = NodeMap::DijkstrasSearch(start, end);

    Agent agent(&tileNodeMap, new GoToPointBehaviour());
    agent.SetNode(start);

    Agent agent2(&tileNodeMap, new WanderBehaviour());
    agent2.SetNode(tileNodeMap.GetRandomNode());
    agent2.SetAgentTexture(LoadTexture("ref/m8raEvil.png"));

    Agent agent3(&tileNodeMap, new SelectorBehaviour( new FollowBehaviour(), new WanderBehaviour() ));
    agent3.SetNode(tileNodeMap.GetRandomNode());
    agent3.SetTarget(&agent);

    Rectangle inputBox = { screenWidth / 2, screenHeight / 2, 100, 45 };
    bool mouseOnInputBox = false;
    int letterCount = 0;
    char saveFileName[17];

    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here

        float fTime = (float)GetTime();
        deltaTime = fTime - time;
        time = fTime;
        
        //----------------------------------------------------------------------------------
        if (IsMouseButtonPressed(0))
        {
            start = tileNodeMap.GetClosestNode(glm::vec2(GetMousePosition().x, GetMousePosition().y));
            if (end != nullptr) nodeMapPath = NodeMap::DijkstrasSearch(start, end);
            agent.SetNode(start); //resetting the search to now consider the mouse location as the starting node when user left clicks
            agent.GoTo(end);
            
        }
        if (IsMouseButtonPressed(1))
        {
            end = tileNodeMap.GetClosestNode(glm::vec2(GetMousePosition().x, GetMousePosition().y));
            if (end == nullptr) exit;
            if (start != nullptr) nodeMapPath = NodeMap::DijkstrasSearch(start, end); //resetting the search to now consider the mouse location as the ending node when user right clicks
            agent.GoTo(end);
            
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
            tileNodeMap.DrawPath(agent.GetPath(), RED, 5);
        }

        if (start != nullptr && end != nullptr) {
            DrawCircle(start->position.x, start->position.y, 4, PINK);
            DrawCircle(end->position.x, end->position.y, 4, PINK);
        }

        //newAgent.Update(/*deltaTime*/);
        //newAgent.Draw();

        agent.Update(deltaTime);
        agent.Draw();
        agent2.Update(deltaTime);
        agent2.Draw();
        agent3.Update(deltaTime);
        agent3.Draw();

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