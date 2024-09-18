#include "PathAgent.h"

using namespace AIForGames;

void PathAgent::Update(/*float deltaTime*/)
{
	if (m_path.empty()) return;

	/*Node* nextNode = m_path.at(m_currentIndex + 1);

	float distance = glm::distance(m_position, nextNode->position);
	float distTravelled = distance - (m_speed * deltaTime);

	glm::vec2 unitVec = (nextNode->position);

	if (distTravelled > 0)
	{
		m_position = { unitVec.x * m_speed * deltaTime, unitVec.y * m_speed * deltaTime };
	}
	else
	{
		m_currentIndex++;
		if (m_currentNode == m_path.back())
		{
			m_position = m_path.back()->position;
			m_path.clear();
			return;
		}

		if (nextNode)
		{
			distTravelled = -distTravelled;
			m_position.x += unitVec.x + distTravelled; m_position.y += unitVec.y + distTravelled;
		}
	}*/
	Node* nextNode = m_path.at(m_currentIndex + 1);

	if (m_position.x < nextNode->position.x) { m_position.x++; if (flipAgentTexture) flipAgentTexture = false; }

	if (m_position.x > nextNode->position.x) { m_position.x--; if (!flipAgentTexture) flipAgentTexture = true; }

	if (m_position.y < nextNode->position.y) { m_position.y++; }

	if (m_position.y > nextNode->position.y) { m_position.y--; }

	if (m_position == nextNode->position) {
		m_currentNode = nextNode;
		m_currentIndex++;
		if (m_currentNode == m_path.back())
		{
			m_position = m_path.back()->position;
			m_path.clear();
		}
	}
}

void PathAgent::GoToNode(AIForGames::Node* node)
{
	m_path = NodeMap::DijkstrasSearch(m_currentNode, node);
	m_currentIndex = 0;
}

void PathAgent::SetNode(AIForGames::Node* node)
{
	m_currentNode = node;
	m_position = node->position;
}

void PathAgent::SetSpeed(float speed)
{
	m_speed = speed;
}

void PathAgent::Draw()
{
	//DrawCircleV(Vector2(m_position.x, m_position.y), 8, ORANGE);
	//DrawCircleLines(m_position.x, m_position.y, 9, PURPLE);

	/*DrawCircleGradient(m_position.x, m_position.y, 8, SKYBLUE, DARKPURPLE);
	DrawCircleLines(m_position.x, m_position.y, 8, RED);*/

	if (!flipAgentTexture)
	{
		DrawTexturePro(agentTexture,
			Rectangle{ 0.0f, 0.0f, (float)agentTexture.width, (float)agentTexture.height },
			Rectangle{ m_position.x, m_position.y, (float)agentTexture.width, (float)agentTexture.height },
			Vector2{ (float)agentTexture.width * .5f, (float)agentTexture.height - 16.f },
			0.0f, m_tint);
	}
	else
	{
		DrawTexturePro(agentTexture,
			Rectangle{ 0.0f, 0.0f, -(float)agentTexture.width, (float)agentTexture.height },
			Rectangle{ m_position.x, m_position.y, (float)agentTexture.width, (float)agentTexture.height },
			Vector2{ (float)agentTexture.width * .5f, (float)agentTexture.height - 16.f },
			0.0f, m_tint);
	}
}
