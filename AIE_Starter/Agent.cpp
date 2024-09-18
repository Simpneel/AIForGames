#include "Agent.h"
#include "Behaviour.h"

using namespace AIForGames;

Agent::Agent(NodeMap* nodeMap, Behaviour* behaviour)
{
	m_current = behaviour;
	m_nodeMap = nodeMap;
	m_color = { 255,255,0,255 };
}

void Agent::Update(float deltaTime)
{
	if (m_current)
		m_current->Update(this, deltaTime);
	m_pathAgent.Update();
}

void Agent::GoTo(glm::vec2 point)
{
	Node* end = m_nodeMap->GetClosestNode(point);
	m_pathAgent.GoToNode(end);
}
