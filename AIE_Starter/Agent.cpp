#include "Agent.h"
#include "Pathfinding.h"
#include "Behaviour.h"

using namespace AIForGames;

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
