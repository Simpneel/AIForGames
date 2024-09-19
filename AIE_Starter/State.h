#pragma once
#include <vector>

class Agent;
class Behaviour;
class Condition;

class State
{
public:

	struct Transition
	{
		Condition* condition;
		State* targetState;
	};

	State() {}
	State(Behaviour* behaviour);
	~State();
	virtual void Update(Agent* agent, float deltaTime);

	virtual void Enter(Agent* agent) {}
	virtual void Exit(Agent* agent) {}

	std::vector<Transition> GetTransitions() { return m_transitions; }
	void AddTransition(Condition* cond, State* state) { m_transitions.push_back({ cond, state }); }

private:

	std::vector<Behaviour*> m_behaviours;
	std::vector<Transition> m_transitions;

};

