#pragma once
#include <raylib.h>
#include <string>
#include <glm/glm.hpp>
#include "TileMap.h"
#include "Pathfinding.h"

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
    ~PathAgent() { UnloadTexture(agentTexture); }

    void SetAgentTexture(Texture2D newTexture) { agentTexture = newTexture; }

    void Update(/*float deltaTime*/);
    void GoToNode(AIForGames::Node* node);
    void SetNode(AIForGames::Node* node);
    void SetSpeed(float speed);
    void Draw();
};