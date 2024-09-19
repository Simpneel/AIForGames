#pragma once
#include <glm/glm.hpp>

class Agent;

class Behaviour
{
public: 
	virtual void Update(Agent* agent, float deltaTime) = 0;

	virtual void Enter(Agent* agent) {}
	virtual void Exit(Agent* agent) {}
};

//__________________________________________________________________________________________________________________________

class GoToPointBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime);
};

//__________________________________________________________________________________________________________________________

class WanderBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime);

	virtual void Enter(Agent* agent);
	virtual void Exit(Agent* agent) {}
};

//__________________________________________________________________________________________________________________________

class FollowBehaviour : public Behaviour
{
private:
	glm::vec2 lastTargetPostion;
public:
	virtual void Update(Agent* agent, float deltaTime);

	virtual void Enter(Agent* agent);
	virtual void Exit(Agent* agent) {}
};

//__________________________________________________________________________________________________________________________

class SelectorBehaviour : public Behaviour
{
private:
	Behaviour* m_b1;
	Behaviour* m_b2;
	Behaviour* m_selected;
public:
	SelectorBehaviour(Behaviour* b1, Behaviour* b2) : m_b1(b1), m_b2(b2), m_selected(nullptr) {}
	virtual void Update(Agent* agent, float deltaTime);

	void SetBehaviour(Behaviour* b, Agent* agent);
};

//__________________________________________________________________________________________________________________________
		//Condition classes
//__________________________________________________________________________________________________________________________

class Condition
{
public:
	virtual bool IsTrue(Agent* agent) = 0;
};

//__________________________________________________________________________________________________________________________

class DistanceCondition : public Condition
{
private:
	float m_distance;
	bool m_lessThan;
public:
	DistanceCondition(float d, bool lt) : m_distance(d), m_lessThan(lt) {}
	virtual bool IsTrue(Agent* agent);
};