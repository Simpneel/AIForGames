

#include "raylib.h"

//#define RAYGUI_IMPLEMENTATION
//#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "Pathfinding.h"

using namespace AIForGames;

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1200;
    int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "AI For Games: Pathfinding");

    SetTargetFPS(60);

    float time = GetTime();
    float deltaTime;
    //--------------------------------------------------------------------------------------
    /*std::vector<std::string> asciiMap1;
    asciiMap1.push_back("000000000000");
    asciiMap1.push_back("010111011100");
    asciiMap1.push_back("010101110110");
    asciiMap1.push_back("010100000000");
    asciiMap1.push_back("010111111110");
    asciiMap1.push_back("010000001000");
    asciiMap1.push_back("011111111110");
    asciiMap1.push_back("000000000000");

    NodeMap newMap;
	newMap.Initialise(asciiMap1, 50);*/

    NodeMap nodeMap;
    std::vector<std::string> asciiMap;
   /* asciiMap.push_back("000000000000");
    asciiMap.push_back("010111011100");
    asciiMap.push_back("010101110110");
    asciiMap.push_back("010100000000");
    asciiMap.push_back("010111111110");
    asciiMap.push_back("010000001000");
    asciiMap.push_back("011111111110");
    asciiMap.push_back("000000000000");*/

    asciiMap.push_back("00000000000000000000");
    asciiMap.push_back("01111111111111111110");
    asciiMap.push_back("00000111110000001110");
    asciiMap.push_back("01101010101010101010");
    asciiMap.push_back("01111111111111111110");
    asciiMap.push_back("01000000011100001100");
    asciiMap.push_back("00000000000110000000");
    asciiMap.push_back("00011111100111110010");
    asciiMap.push_back("01111000000000011110");
    asciiMap.push_back("00010111111111110000");
    asciiMap.push_back("01110001111000000000");
    asciiMap.push_back("01000000010000000000");
    asciiMap.push_back("01111000111100011100");
    asciiMap.push_back("01110000001000111000");
    asciiMap.push_back("01110000001111100000");
    asciiMap.push_back("01000000000000100000");
    asciiMap.push_back("01000000000001111000");
    asciiMap.push_back("01111111111111100000");
    asciiMap.push_back("00000000011111100000");
    asciiMap.push_back("00000000000000000000");

    nodeMap.Initialise(asciiMap, 32);

    Node* start = nodeMap.GetNode(1, 1);
    Node* end = nodeMap.GetNode(10, 1);
    std::vector<Node*> nodeMapPath = NodeMap::DijkstrasSearch(start, end);
    
    PathAgent newAgent;
    newAgent.SetNode(start);
    newAgent.SetSpeed(64);
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
            start = nodeMap.GetClosestNode(glm::vec2(GetMousePosition().x, GetMousePosition().y));
            nodeMapPath = NodeMap::DijkstrasSearch(start, end); //resetting the search to now consider the mouse location as the starting node when user left clicks
            newAgent.GoToNode(end);
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(DARKGRAY);

        nodeMap.Draw();
        nodeMap.DrawPath(nodeMapPath, DARKPURPLE, 4);
        nodeMap.DrawPath(newAgent.m_path, ORANGE, 3);

        newAgent.Update(deltaTime);
        newAgent.Draw();

        EndDrawing();
        
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}