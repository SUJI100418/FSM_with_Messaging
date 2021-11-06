#ifndef FREEZER_OWNED_STATES_H
#define FREEZER_OWNED_STATES_H

#include "fsm/State.h"


class Frieza;
struct Telegram;


//====================================================================================

class FriezaGlobalState : public State<Frieza>  //�۷ι� for �޽���
{
private:

	FriezaGlobalState() {}

	//copy ctor and assignment should be private
	FriezaGlobalState(const FriezaGlobalState&);
	FriezaGlobalState& operator=(const FriezaGlobalState&);

public:

	//this is a singleton
	static FriezaGlobalState* Instance();

	virtual void Enter(Frieza* free) {}

	virtual void Execute(Frieza* free);

	virtual void Exit(Frieza* free) {}

	virtual bool OnMessage(Frieza* free, const Telegram& msg);  // �۷ι� �޼��� �ޱ� �Լ�
};

//====================================================================================

class CommandFriezaForce : public State<Frieza>
{
private:

	CommandFriezaForce() {}

	//copy ctor and assignment should be private
	CommandFriezaForce(const CommandFriezaForce&);
	CommandFriezaForce& operator=(const CommandFriezaForce&);

public:

	//this is a singleton
	static CommandFriezaForce* Instance();

	virtual void Enter(Frieza* free);

	virtual void Execute(Frieza* free);

	virtual void Exit(Frieza* free);

	virtual bool OnMessage(Frieza* free, const Telegram& msg);

};

class GoToEarth : public State<Frieza>
{
private:

	GoToEarth() {}

	//copy ctor and assignment should be private
	GoToEarth(const GoToEarth&);
	GoToEarth& operator=(const GoToEarth&);

public:

	//this is a singleton
	static GoToEarth* Instance();

	virtual void Enter(Frieza* free);

	virtual void Execute(Frieza* free);

	virtual void Exit(Frieza* free);

	virtual bool OnMessage(Frieza* free, const Telegram& msg);

};

class Battle : public State<Frieza>
{
private:

	Battle() {}

	//copy ctor and assignment should be private
	Battle(const Battle&);
	Battle& operator=(const Battle&);

public:

	//this is a singleton
	static Battle* Instance();

	virtual void Enter(Frieza* free);

	virtual void Execute(Frieza* free);

	virtual void Exit(Frieza* free);

	virtual bool OnMessage(Frieza* free, const Telegram& msg);

};


#endif