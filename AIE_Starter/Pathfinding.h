#pragma once

#include <raylib.h>
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "TileMap.h"

namespace AIForGames
{
    struct Node;

    struct Edge {
        Node* target;
        float cost;
        Edge() { target = nullptr; cost = 0; }
        Edge(Node* _target, float _cost) : target(_target), cost(_cost) {}
    };
    //______________________________________________________________________
    struct Node {

        glm::vec2 position;
        std::vector<Edge> connections;
        float gScore;
        Node* previous;
        int nodeID;

        Node() { gScore = 0; previous = nullptr; }
        Node(float x, float y) { position.x = x; position.y = y; gScore = 0; previous = nullptr; }

        void SetPosition(float x, float y) { position.x = x; position.y = y; }

        void ConnectTo(Node* other, float cost) { connections.push_back(Edge(other, cost)); }
    };
}

//__________________________________________________________________________________________________________________________

class NodeMap
{
public:
    int m_width, m_height;
    float m_cellSize;

    AIForGames::Node** m_nodes;
    void Initialise(std::vector<std::string> asciiMap, int cellSize);

    void Initialise(TileMap* tileMap, int cellSize);

    AIForGames::Node* GetNode(int x, int y) const { return m_nodes[x + m_width * y]; }
    AIForGames::Node* GetClosestNode(glm::vec2 worldPos);
    AIForGames::Node* GetRandomNode();

    void Draw();
    static void DrawPath(std::vector<AIForGames::Node*> nodeMapPath, Color lineColor, float lineThickness);

    static std::vector<AIForGames::Node*> DijkstrasSearch(AIForGames::Node* startNode, AIForGames::Node* endNode);
    static std::vector<AIForGames::Node*> AStarSearch(AIForGames::Node* startNode, AIForGames::Node* endNode);

    static float EuclideanDistance(glm::vec2 pos1, glm::vec2 pos2);
};

//__________________________________________________________________________________________________________________________