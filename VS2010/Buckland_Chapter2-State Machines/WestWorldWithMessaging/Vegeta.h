#ifndef VEGETA_H
#define VEGETA_H

#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "fsm/StateMachine.h"

#include "fsm/State.h"
#include "misc/Utils.h"

#include "VegetaOwnedStates.h"
//#include "Miner.h"

template <class entity_type> class State;

struct Telegram;


const int Vegy_HungerLevel = 5;
const int Vegy_MaxHelth = 10;


class Vegeta : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Vegeta>*  m_pStateMachine;

	location_type         m_Location;

	int m_iHunger;
	bool m_isBattlerFreezer;

public:
	int m_gravity;
	int m_iHelth;

	Vegeta(int id) :m_Location(CapsuleCorp),  //위에 변수 처음 셋업하기
		BaseGameEntity(id),
		m_iHunger(0),
		m_iHelth(Vegy_MaxHelth),
		m_gravity(1),
		m_isBattlerFreezer(false)

	{
		//set up state machine
		m_pStateMachine = new StateMachine<Vegeta>(this);

		m_pStateMachine->SetCurrentState(UseGravityMachineForTraining::Instance());

		m_pStateMachine->SetGlobalState(VegetaGlobalState::Instance());

	}

	~Vegeta() { delete m_pStateMachine; }

	//this must be implemented
	void Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);


	StateMachine<Vegeta>* GetFSM()const { return m_pStateMachine; }



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

	void		  BattleWithFreezer(bool opponent) { m_isBattlerFreezer = opponent; }
	bool		  GetBattleOpponent() { return m_isBattlerFreezer; }
};



#endif
