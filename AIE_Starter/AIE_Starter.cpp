

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
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "AI For Games: Pathfinding");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------


    /*Node* a = new Node();
    a->position = glm::vec2(125.0f, 75.0f);
    Node* b = new Node();
    b->position = glm::vec2(250.0f, 75.0f);

    a->ConnectTo(b, 2);*/

    std::vector<std::string> asciiMap1;
    asciiMap1.push_back("000000000000");
    asciiMap1.push_back("010111011100");
    asciiMap1.push_back("010101110110");
    asciiMap1.push_back("010100000000");
    asciiMap1.push_back("010111111110");
    asciiMap1.push_back("010000001000");
    asciiMap1.push_back("011111111110");
    asciiMap1.push_back("000000000000");

    NodeMap newMap;
	newMap.Initialise(asciiMap1, 50);

    NodeMap nodeMap;
    std::vector<std::string> asciiMap;
    asciiMap.push_back("000000000000");
    asciiMap.push_back("010111011100");
    asciiMap.push_back("010101110110");
    asciiMap.push_back("010100000000");
    asciiMap.push_back("010111111110");
    asciiMap.push_back("010000001000");
    asciiMap.push_back("011111111110");
    asciiMap.push_back("000000000000");
    nodeMap.Initialise(asciiMap, 32);

    Node* start = nodeMap.GetNode(1, 1);
    Node* end = nodeMap.GetNode(10, 2);
    std::vector<Node*> nodeMapPath = NodeMap::DijkstrasSearch(start, end);
    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        if (IsMouseButtonPressed(0))
        {
            start = nodeMap.GetClosestNode(glm::vec2(GetMousePosition().x, GetMousePosition().y));
            nodeMapPath = NodeMap::DijkstrasSearch(start, end);
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        nodeMap.Draw();
        //nodeMap.DrawPath(nodeMapPath, PURPLE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}