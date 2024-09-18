#pragma once
#include <raylib.h>
#include "Pathfinding.h"
#include "PathAgent.h"

class Behaviour;

using namespace AIForGames;

class Agent
{
public:
	Agent() {}
	Agent(NodeMap* nodeMap, Behaviour* behaviour);
	~Agent() { delete m_current;}

	void Update(float deltaTime);
	void Draw();
	void SetTint(Color color);
	void SetAgentTexture(Texture2D texture);

	void GoTo(glm::vec2 point);
	void GoTo(Node* node);

	void SetNode(Node* node);
	bool PathComplete();
	NodeMap* GetNodeMap() { return m_nodeMap; }

	Agent* GetTarget();
	void SetTarget(Agent* agent);

	glm::vec2 GetPosition();

	void Reset() { m_pathAgent.m_path.clear(); }

private:
	Agent* target;

	PathAgent m_pathAgent;
	Behaviour *m_current;
	NodeMap* m_nodeMap;
	Color m_color;
};