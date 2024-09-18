#pragma once

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