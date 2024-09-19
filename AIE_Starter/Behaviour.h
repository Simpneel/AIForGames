#pragma once
#include <glm/glm.hpp>
#include <vector>

class Agent;

class Behaviour
{
public: 
	virtual void Update(Agent* agent, float deltaTime) = 0;

	virtual void Enter(Agent* agent) = 0;
	virtual void Exit(Agent* agent) = 0;

	virtual float Evaluate(Agent* agent) { return 0.0f; }
};

//__________________________________________________________________________________________________________________________

class GoToPointBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime);

	virtual void Enter(Agent* agent) override;
	virtual void Exit(Agent* agent) override;
};

//__________________________________________________________________________________________________________________________

class WanderBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime);

	virtual void Enter(Agent* agent) override;
	virtual void Exit(Agent* agent) override;

	virtual float Evaluate(Agent* agent) override;
};

//__________________________________________________________________________________________________________________________

class FollowBehaviour : public Behaviour
{
private:
	glm::vec2 lastTargetPostion;
public:
	virtual void Update(Agent* agent, float deltaTime);

	virtual void Enter(Agent* agent) override;
	virtual void Exit(Agent* agent) override;

	virtual float Evaluate(Agent* agent) override;
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

class UtilityAI : public Behaviour
{
private:

	Behaviour* m_currentBehaviour;

	std::vector<Behaviour*> m_behaviour;

public:
	UtilityAI() { m_currentBehaviour = nullptr; }
	~UtilityAI();

	void AddBehaviour(Behaviour* b);

	virtual void Enter(Agent* agent) override;
	virtual void Exit(Agent* agent) override;

	virtual void Update(Agent* agent, float deltaTime);
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

//__________________________________________________________________________________________________________________________