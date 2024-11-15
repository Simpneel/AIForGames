#include "Agent.h"
#include "Behaviour.h"

using namespace AIForGames;

Agent::Agent(NodeMap* nodeMap, Behaviour* behaviour)
{
	m_current = behaviour;
	m_nodeMap = nodeMap;
	m_color = { 255,255,255,255 };
	m_current->Enter(this);
	m_health = 100;
	target = nullptr;
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

void Agent::SetTint(Color color)
{
	m_pathAgent.m_tint = color;
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

void Agent::GoTo(Node* node)
{
	m_pathAgent.GoToNode(node);
}

void Agent::SetNode(Node* node)
{
	m_pathAgent.SetNode(node);
}

bool Agent::PathComplete()
{
	return m_pathAgent.GetPath().empty();
}

Agent* Agent::GetTarget()
{
	return target;
}

void Agent::SetTarget(Agent* agent)
{
	target = agent;
}

glm::vec2 Agent::GetPosition()
{
	return m_pathAgent.m_position;
}
