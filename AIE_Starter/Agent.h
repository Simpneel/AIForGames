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
	~Agent() { delete m_current; }

	void Update(float deltaTime);
	void Draw();
	void SetTint(Color color);
	void SetAgentTexture(Texture2D texture);

	void GoTo(glm::vec2 point);
	void GoTo(Node* node);

	void SetNode(Node* node);
	bool PathComplete();
	NodeMap* GetNodeMap() { return m_nodeMap; }
	std::vector<Node*> GetPath() { return m_pathAgent.m_path; }

	Agent* GetTarget();
	void SetTarget(Agent* agent);

	glm::vec2 GetPosition();

	void Reset() { m_pathAgent.m_path.clear(); }

	void SetHealth(int newHealth) { m_health = newHealth; if (newHealth < m_health) SetTint(RED); }
	int GetHealth() { return m_health; }

private:
	Agent* target;

	int m_health;
	PathAgent m_pathAgent;
	Behaviour *m_current;
	NodeMap* m_nodeMap;
	Color m_color;
};

