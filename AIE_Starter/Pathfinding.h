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

    struct Node {

        glm::vec2 position;
        std::vector<Edge> connections;
        float gScore;
        Node* previous;
        int nodeID;

        Node() { gScore = 0; previous = nullptr; position = { 0,0 }; nodeID = 0; }
        Node(float x, float y) { position.x = x; position.y = y; gScore = 0; nodeID = 0; previous = nullptr; }
        ~Node() { connections.clear(); }

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
    NodeMap() { m_width = 0; m_height = 0; m_cellSize = 0; m_nodes = nullptr; }
    ~NodeMap();
    void Initialise(std::vector<std::string> asciiMap, int cellSize);

    void Initialise(TileMap* tileMap, int cellSize);

    AIForGames::Node* GetNode(int x, int y) const { return m_nodes[x + m_width * y]; }
    AIForGames::Node* GetClosestNode(glm::vec2 worldPos);

    void Draw();
    static void DrawPath(std::vector<AIForGames::Node*> nodeMapPath, Color lineColor, float lineThickness);

    static std::vector<AIForGames::Node*> DijkstrasSearch(AIForGames::Node* startNode, AIForGames::Node* endNode);
    static std::vector<AIForGames::Node*> AStarSearch(AIForGames::Node* startNode, AIForGames::Node* endNode);

    static float EuclideanDistance(glm::vec2 pos1, glm::vec2 pos2);
};

class PathAgent
{
public:
    glm::vec2 m_position;

    std::vector<AIForGames::Node*> m_path;
    int m_currentIndex;
    AIForGames::Node* m_currentNode;
    float m_speed;

    Texture2D agentTexture;
    bool flipAgentTexture;

    PathAgent() { m_position = { 0,0 }; m_currentIndex = m_speed = 0; m_currentNode = nullptr; m_path.clear(); agentTexture = LoadTexture("ref/m8ra.png"); flipAgentTexture = false; }
    ~PathAgent();

    void SetAgentTexture(Texture2D newTexture) { agentTexture = newTexture; }

    void Update(/*float deltaTime*/);
    void GoToNode(AIForGames::Node* node);
    void SetNode(AIForGames::Node* node);
    void SetSpeed(float speed);
	void Draw();
};