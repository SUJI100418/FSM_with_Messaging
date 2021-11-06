#ifndef KAKAROT_H
#define KAKAROT_H

#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "fsm/StateMachine.h"

#include "fsm/State.h"
#include "misc/Utils.h"

#include "KakarotOwnedStates.h"
//#include "Miner.h"

template <class entity_type> class State; 

struct Telegram;

const int Kaka_HungerLevel = 3;
const int Kaka_MaxHelth = 10;


class Kakarot : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Kakarot>*  m_pStateMachine;

	location_type         m_Location;

	int m_iHunger;
	int m_iHelth;
	bool m_isBattlerFreezer;

public:

	Kakarot(int id) :m_Location(KingKaiPlanet),  //위에 변수 처음 셋업하기
		BaseGameEntity(id),
		m_iHunger(0),
		m_iHelth(Kaka_MaxHelth),
		m_isBattlerFreezer(false)

	{
		//set up state machine
		m_pStateMachine = new StateMachine<Kakarot>(this);

		m_pStateMachine->SetCurrentState(RestAndRice::Instance());

		m_pStateMachine->SetGlobalState(KakarotGlobalState::Instance());

	}

	~Kakarot() { delete m_pStateMachine; }

	//this must be implemented
	void Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);


	StateMachine<Kakarot>* GetFSM()const { return m_pStateMachine; }


	//-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	bool		  Faint() const;
	void          TakeDamage(int damage);
	int           GetHelth();
	void		  Healing();
	bool		  FullHeath();

	bool          Hunger()const;
	void          EatLotsOfFood() { m_iHunger = 0; }

	void		  BattleWithFreezer(bool opponent) { m_isBattlerFreezer = opponent;}
	bool		  GetBattleOpponent() { return m_isBattlerFreezer; }

};



#endif
