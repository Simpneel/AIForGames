#include "Behaviour.h"
#include "Agent.h"

void GoToPointBehaviour::Update(Agent* agent, float deltaTime)
{
	if (IsMouseButtonPressed(0))
	{
		Vector2 mousePos = GetMousePosition();
		agent->GoTo(glm::vec2{ mousePos.x, mousePos.y });
	}
}

void WanderBehaviour::Update(Agent* agent, float deltaTime)
{
	if (agent->PathComplete())
	{
		Node* newNode = agent->GetNodeMap()->GetRandomNode();
		agent->GoTo({ newNode->position.x, newNode->position.y });
	}
}

void FollowBehaviour::Update(Agent* agent, float deltaTime)
{
	Agent* target = agent->GetTarget();

	float dist = glm::distance(target->GetPosition(), lastTargetPostion);
	if (dist > agent->GetNodeMap()->m_cellSize)
	{
		lastTargetPostion = target->GetPosition();
		agent->GoTo(lastTargetPostion);
	}
}

void SelectorBehaviour::Update(Agent* agent, float deltaTime)
{
	if (glm::distance(agent->GetPosition(), agent->GetTarget()->GetPosition()) < agent->GetNodeMap()->m_cellSize * 5)
	{
		SetBehaviour(m_b1, agent);
		agent->SetTint(RED);
	}
	else
	{
		SetBehaviour(m_b2, agent);
		agent->SetTint(BLUE);
	}
	m_selected->Update(agent, deltaTime);
}

void SelectorBehaviour::SetBehaviour(Behaviour* b, Agent* agent)
{
	if (m_selected != b)
	{
		m_selected = b;
		agent->Reset();
	}
}
