#pragma once
#include "Behaviour.h"
#include <vector>

class State;

class FiniteStateMachine : public Behaviour
{
private:
	std::vector<State*> m_states;

	State* m_currentState;
	State* m_newState;

public:
	FiniteStateMachine(State* s) : m_currentState(s), m_newState(nullptr) {}
	virtual ~FiniteStateMachine();

	void Update(Agent* agent, float deltaTime);

	void AddState(State* newState);

	virtual void Enter(Agent* agent);
};