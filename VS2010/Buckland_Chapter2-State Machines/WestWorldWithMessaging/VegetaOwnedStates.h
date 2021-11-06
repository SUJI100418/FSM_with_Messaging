#ifndef VEGETA_OWNED_STATES_H
#define VEGETA_OWNED_STATES_H

#include "fsm/State.h"


class Vegeta;
struct Telegram;


//====================================================================================

class VegetaGlobalState : public State<Vegeta>  //글로벌 for 메신저
{
private:

	VegetaGlobalState() {}

	//copy ctor and assignment should be private
	VegetaGlobalState(const VegetaGlobalState&);
	VegetaGlobalState& operator=(const VegetaGlobalState&);

public:

	//this is a singleton
	static VegetaGlobalState* Instance();

	virtual void Enter(Vegeta* vegy) {}

	virtual void Execute(Vegeta* vegy);

	virtual void Exit(Vegeta* vegy) {}

	virtual bool OnMessage(Vegeta* vegy, const Telegram& msg);  // 글로벌 메세지 받기 함수
};

//====================================================================================

class UseGravityMachineForTraining : public State<Vegeta>
{
private:

	UseGravityMachineForTraining() {}

	//copy ctor and assignment should be private
	UseGravityMachineForTraining(const UseGravityMachineForTraining&);
	UseGravityMachineForTraining& operator=(const UseGravityMachineForTraining&);

public:

	//this is a singleton
	static UseGravityMachineForTraining* Instance();

	virtual void Enter(Vegeta* vegy);

	virtual void Execute(Vegeta* vegy);

	virtual void Exit(Vegeta* vegy);

	virtual bool OnMessage(Vegeta* vegy, const Telegram& msg);

};

//====================================================================================

class RestAndEatWithFamily : public State<Vegeta>
{
private:

	RestAndEatWithFamily() {}

	//copy ctor and assignment should be private
	RestAndEatWithFamily(const RestAndEatWithFamily&);
	RestAndEatWithFamily& operator=(const RestAndEatWithFamily&);

public:

	//this is a singleton
	static RestAndEatWithFamily* Instance();

	virtual void Enter(Vegeta* vegy);

	virtual void Execute(Vegeta* vegy);

	virtual void Exit(Vegeta* vegy);

	virtual bool OnMessage(Vegeta* vegy, const Telegram& msg);
};

//====================================================================================

class Vegy_Battle : public State<Vegeta>
{
private:

	Vegy_Battle() {}

	//copy ctor and assignment should be private
	Vegy_Battle(const Vegy_Battle&);
	Vegy_Battle& operator=(const Vegy_Battle&);

public:

	//this is a singleton
	static Vegy_Battle* Instance();

	virtual void Enter(Vegeta* vegy);

	virtual void Execute(Vegeta* vegy);

	virtual void Exit(Vegeta* vegy);

	virtual bool OnMessage(Vegeta* vegy, const Telegram& msg);
};


#endif