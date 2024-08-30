#pragma once

#include <raylib.h>
#include <string>
#include <glm/glm.hpp>
#include <vector>

namespace AIForGames
{
    struct Node;

    struct Edge {
        Node* target;
        float cost;
        Edge() { target = nullptr; cost = 0; }
        Edge(Node* _target, float _cost) : target(_target), cost(_cost) {}
    };

    struct Node {

        glm::vec2 position;
        std::vector<Edge> connections;
        float gScore;
        Node* previous;

        Node() {}
        Node(float x, float y) { position.x = x; position.y = y; }

        void SetPosition(float x, float y) { position.x = x; position.y = y; }

        void ConnectTo(Node* other, float cost) { connections.push_back(Edge(other, cost)); }
    };
}

class NodeMap
{
public:
    int m_width, m_height;
    float m_cellSize;

    AIForGames::Node** m_nodes;
    void Initialise(std::vector<std::string> asciiMap, int cellSize);

    AIForGames::Node* GetNode(int x, int y) const { return m_nodes[x + m_width * y]; }
    AIForGames::Node* GetClosestNode(glm::vec2 worldPos);

    void Draw();
    void DrawPath(std::vector<AIForGames::Node*> nodeMapPath, Color lineColor);

    static std::vector<AIForGames::Node*> DijkstrasSearch(AIForGames::Node* startNode, AIForGames::Node* endNode);
};