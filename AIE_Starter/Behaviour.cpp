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

void GoToPointBehaviour::Enter(Agent* agent)
{
}

void GoToPointBehaviour::Exit(Agent* agent)
{
}

//__________________________________________________________________________________________________________________________
//	Wander Behaviour

void WanderBehaviour::Update(Agent* agent, float deltaTime)
{
	if (agent->PathComplete())
	{
		Node* newNode = agent->GetNodeMap()->GetRandomNode();
		agent->GoTo({ newNode->position.x, newNode->position.y });
	}
}

void WanderBehaviour::Enter(Agent* agent)
{
	agent->SetTint(LIME);
	agent->Reset();
}

void WanderBehaviour::Exit(Agent* agent)
{
	agent->SetTint(WHITE);
}

float WanderBehaviour::Evaluate(Agent* agent)
{
	Agent* target = agent->GetTarget();
	float dist = glm::distance(target->GetPosition(), agent->GetPosition());

	float eval = dist;
	if (eval < 0) 
		eval = 0;
	return eval;
}

//__________________________________________________________________________________________________________________________
//	Follow Behaviour

void FollowBehaviour::Update(Agent* agent, float deltaTime)
{
	Agent* target = agent->GetTarget();

	float dist = glm::distance(target->GetPosition(), lastTargetPostion);
	if (dist > agent->GetNodeMap()->m_cellSize * 10)
	{
		glm::vec2 stoppingPoint;
		if (agent->GetPosition().x < target->GetPosition().x) {
			if (agent->GetPosition().y < target->GetPosition().y) stoppingPoint = { -25,-25 };
			else stoppingPoint = { -25,25 };
		}
		else {
			if (agent->GetPosition().y < target->GetPosition().y) stoppingPoint = { 25,-25 };
			else stoppingPoint = { 25,25 };
		}
		lastTargetPostion = target->GetPosition() + stoppingPoint;
		agent->GoTo(lastTargetPostion);
	}
}

void FollowBehaviour::Enter(Agent* agent)
{
	agent->SetTint(ORANGE);
	agent->Reset();
}

void FollowBehaviour::Exit(Agent* agent)
{
	agent->SetTint(WHITE);
}

float FollowBehaviour::Evaluate(Agent* agent)
{
	Agent* target = agent->GetTarget();
	float dist = glm::distance(target->GetPosition(), agent->GetPosition());

	float eval = 10 * agent->GetNodeMap()->m_cellSize - dist;
	if (eval < 0)
		eval = 0;
	return eval;
}

//__________________________________________________________________________________________________________________________

void AttackBehaviour::Update(Agent* agent, float deltaTime)
{
	Agent* target = agent->GetTarget();
	
	float dist = glm::distance(agent->GetPosition(), target->GetPosition());

	if (dist > agent->GetNodeMap()->m_cellSize * 5) {
		lastTargetPosition = target->GetPosition();
		agent->GoTo(lastTargetPosition);
	}
	else {
		attackTimer -= deltaTime;
		if (attackTimer <= 0 && dist <= agent->GetNodeMap()->m_cellSize) {
			attackTimer = 1.0f;
			target->SetHealth(target->GetHealth() - 5);
		}
	}
}

void AttackBehaviour::Enter(Agent* agent)
{
	agent->SetTint(RED);
	agent->Reset();
}

void AttackBehaviour::Exit(Agent* agent)
{
	agent->SetTint(WHITE);
}

float AttackBehaviour::Evaluate(Agent* agent)
{
	Agent* target = agent->GetTarget();

	float dist = glm::distance(target->GetPosition(), agent->GetPosition());

	float eval = 0;

	float hpDiff = agent->GetHealth() - target->GetHealth();
	eval = dist + hpDiff;
	
	if (eval < 0)
		eval = 0;

	return eval;
}

//__________________________________________________________________________________________________________________________

void SelectorBehaviour::Update(Agent* agent, float deltaTime)
{
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

//__________________________________________________________________________________________________________________________

UtilityAI::~UtilityAI()
{
	for (Behaviour* b : m_behaviour)
	{
		delete b;
	}
}

void UtilityAI::AddBehaviour(Behaviour* b)
{
	m_behaviour.push_back(b);
}

void UtilityAI::Enter(Agent* agent)
{
}

void UtilityAI::Exit(Agent* agent)
{
}

void UtilityAI::Update(Agent* agent, float deltaTime)
{
	float bestEval = 0.0f;
	Behaviour* newBehaviour = nullptr;
	for (Behaviour* b : m_behaviour)
	{
		float eval = b->Evaluate(agent);
		if (eval > bestEval)
		{
			bestEval = eval;
			newBehaviour = b;
		}
	}

	if (newBehaviour != nullptr && newBehaviour != m_currentBehaviour)
	{
		if (m_currentBehaviour)
			m_currentBehaviour->Exit(agent);
		m_currentBehaviour = newBehaviour;
		m_currentBehaviour->Enter(agent);
	}
	m_currentBehaviour->Update(agent, deltaTime);
}

//__________________________________________________________________________________________________________________________

bool DistanceCondition::IsTrue(Agent* agent)
{
	return (glm::distance(agent->GetPosition(), agent->GetTarget()->GetPosition()) < m_distance) == m_lessThan;
}

bool HealthCondition::IsTrue(Agent* agent)
{
	return (agent->GetHealth() > agent->GetTarget()->GetHealth()) == lessThan;
}
