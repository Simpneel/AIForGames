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

void Agent::Draw()
{
	m_pathAgent.Draw();
}

void Agent::SetAgentTexture(Texture2D texture)
{
	m_pathAgent.SetAgentTexture(texture);
}

void Agent::GoTo(glm::vec2 point)
{
	Node* end = m_nodeMap->GetClosestNode(point);
	m_pathAgent.GoToNode(end);
}

void Agent::SetNode(Node* node)
{
	m_pathAgent.SetNode(node);
}

bool Agent::PathComplete()
{
	return m_pathAgent.GetPath().empty();
}
