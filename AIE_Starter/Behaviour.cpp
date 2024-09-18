#include "Behaviour.h"
#include "Agent.h"
#include <glm/glm.hpp>

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
	NodeMap* nodeMap = agent->GetNodeMap();
	Node* validNode = nodeMap->GetRandomNode();
	agent->GoTo({ validNode->position.x, validNode->position.y });
	if (agent->PathComplete()) validNode = nodeMap->GetRandomNode();
}
