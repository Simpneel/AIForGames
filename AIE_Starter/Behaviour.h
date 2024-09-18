#pragma once
#include <glm/glm.hpp>

class Agent;

class Behaviour
{
public: 
	virtual void Update(Agent* agent, float deltaTime) = 0;
};

class GoToPointBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime);
};

class WanderBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime);
};

class FollowBehaviour : public Behaviour
{
private:
	glm::vec2 lastTargetPostion;
public:
	virtual void Update(Agent* agent, float deltaTime);
};

class SelectorBehaviour : public Behaviour
{
private:
	Behaviour* m_b1;
	Behaviour* m_b2;
	Behaviour* m_selected;
public:
	SelectorBehaviour(Behaviour* b1, Behaviour* b2) : m_b1(b1), m_b2(b2) {}
	virtual void Update(Agent* agent, float deltaTime);

	void SetBehaviour(Behaviour* b, Agent* agent);
};