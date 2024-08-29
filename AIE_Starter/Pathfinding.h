#pragma once

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
        Edge(Node* target, float cost) : target(target), cost(cost) {}
    };

    struct Node {

        glm::vec2 position;
        std::vector<Edge> connections;
    public:
        Node();
        Node(float x, float y) { position.x = x; position.y = y; }

        void ConnectTo(Node* other, float cost)
        {
            connections.push_back(Edge(other, cost));
        }
    };
}

using namespace AIForGames;
class NodeMap
{
    int m_width, m_height;
    float m_cellSize;

    Node** m_nodes;
public:
    void Initialise(std::vector<std::string> asciiMap, int cellSize);

    Node* GetNode(int x, int y) { return m_nodes[x + m_width * y]; }

    void Draw();
};