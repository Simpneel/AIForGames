#pragma once
#include <raylib.h>
#include "PathAgent.h"
//#include "Pathfinding.h"

class Agent
{
public:
	Agent() {}
	Agent(NodeMap* nodeMap, Behaviour* behaviour) : m_current(behaviour), m_nodeMap(nodeMap), m_color({ 255,255,0,255 }) {}
	~Agent() { delete m_current; }

	void Update(float deltaTime);
	void Draw();
	void GoTo(glm::vec2 point);

private:
	PathAgent m_pathAgent;
	Behaviour* m_current;
	NodeMap* m_nodeMap;
	Color m_color;
};