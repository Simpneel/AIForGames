#include "State.h"
#include "Agent.h"
#include "Behaviour.h"


State::State(Behaviour* behaviour)
{
	m_behaviours.push_back(behaviour);
}

State::~State()
{
	for (Behaviour* b : m_behaviours)
		delete b;
	for (Transition t : m_transitions)
		delete t.condition;
}

void State::Update(Agent* agent, float deltaTime)
{
	for (Behaviour* b : m_behaviours)
		b->Update(agent, deltaTime);
}

void State::Enter(Agent* agent)
{
	for (Behaviour* b : m_behaviours)
		b->Enter(agent);
}

void State::Exit(Agent* agent)
{
	for (Behaviour* b : m_behaviours)
		b->Exit(agent);
}

