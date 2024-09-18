#pragma once
#include <raylib.h>
#include "Pathfinding.h"
#include "PathAgent.h"

class Behaviour;

class Agent
{
public:
	Agent() {}
	Agent(NodeMap* nodeMap, Behaviour* behaviour);
	~Agent() { delete m_current; }

	void Update(float deltaTime);
	void Draw();
	void GoTo(glm::vec2 point);

private:
	PathAgent m_pathAgent;
	Behaviour *m_current;
	NodeMap* m_nodeMap;
	Color m_color;
};