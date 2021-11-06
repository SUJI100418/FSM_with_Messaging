#ifndef KAKAROT_OWNED_STATES_H
#define KAKAROT_OWNED_STATES_H

#include "fsm/State.h"


class Kakarot;
struct Telegram;


//====================================================================================

class KakarotGlobalState : public State<Kakarot>  //글로벌 for 메신저
{
private:

	KakarotGlobalState() {}

	//copy ctor and assignment should be private
	KakarotGlobalState(const KakarotGlobalState&);
	KakarotGlobalState& operator=(const KakarotGlobalState&);

public:

	//this is a singleton
	static KakarotGlobalState* Instance();

	virtual void Enter(Kakarot* kaka) {}

	virtual void Execute(Kakarot* kaka);

	virtual void Exit(Kakarot* kaka) {}

	virtual bool OnMessage(Kakarot* kaka, const Telegram& msg);  // 글로벌 메세지 받기 함수
};

//====================================================================================

class DoTrainingAlone : public State<Kakarot>
{
private:

	DoTrainingAlone() {}

	//copy ctor and assignment should be private
	DoTrainingAlone(const DoTrainingAlone&);
	DoTrainingAlone& operator=(const DoTrainingAlone&);

public:

	//this is a singleton
	static DoTrainingAlone* Instance();

	virtual void Enter(Kakarot* kaka);

	virtual void Execute(Kakarot* kaka);

	virtual void Exit(Kakarot* kaka);

	virtual bool OnMessage(Kakarot* kaka, const Telegram& msg);

};

//====================================================================================

class RestAndRice : public State<Kakarot>
{
private:

	RestAndRice() {}

	//copy ctor and assignment should be private
	RestAndRice(const RestAndRice&);
	RestAndRice& operator=(const RestAndRice&);

public:

	//this is a singleton
	static RestAndRice* Instance();

	virtual void Enter(Kakarot* kaka);

	virtual void Execute(Kakarot* kaka);

	virtual void Exit(Kakarot* kaka);

	virtual bool OnMessage(Kakarot* kaka, const Telegram& msg);
};

//====================================================================================

class FindSomeoneForBattle : public State<Kakarot>
{
private:

	FindSomeoneForBattle() {}

	//copy ctor and assignment should be private
	FindSomeoneForBattle(const FindSomeoneForBattle&);
	FindSomeoneForBattle& operator=(const FindSomeoneForBattle&);

public:

	//this is a singleton
	static FindSomeoneForBattle* Instance();

	virtual void Enter(Kakarot* kaka);

	virtual void Execute(Kakarot* kaka);

	virtual void Exit(Kakarot* kaka);

	virtual bool OnMessage(Kakarot* kaka, const Telegram& msg);
};

//=====================================================================================

class Kaka_Battle : public State<Kakarot>
{
private:

	Kaka_Battle() {}

	//copy ctor and assignment should be private
	Kaka_Battle(const Kaka_Battle&);
	Kaka_Battle& operator=(const Kaka_Battle&);

public:

	//this is a singleton
	static Kaka_Battle* Instance();

	virtual void Enter(Kakarot* kaka);

	virtual void Execute(Kakarot* kaka);

	virtual void Exit(Kakarot* kaka);

	virtual bool OnMessage(Kakarot* kaka, const Telegram& msg);
};


#endif