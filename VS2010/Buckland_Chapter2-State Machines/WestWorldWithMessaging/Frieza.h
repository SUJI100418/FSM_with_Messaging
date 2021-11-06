#ifndef FREEZER_H
#define FREEZER_H

#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "fsm/StateMachine.h"

#include "fsm/State.h"
#include "misc/Utils.h"

#include "FriezaOwnedStates.h"
//#include "Miner.h"

template <class entity_type> class State;

struct Telegram;


const int Frieza_MaxHelth = 20;
const int DistanceFromeEarth = 20;


class Frieza : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Frieza>*  m_pStateMachine;

	location_type         m_Location;

	int m_iHelth;
	int m_iDistance;

public:

	Frieza(int id) :m_Location(FriezaSpaceship),  //위에 변수 처음 셋업하기
		BaseGameEntity(id),
		m_iHelth(Frieza_MaxHelth),
		m_iDistance(DistanceFromeEarth)

	{
		//set up state machine
		m_pStateMachine = new StateMachine<Frieza>(this);

		m_pStateMachine->SetCurrentState(CommandFriezaForce::Instance());

		m_pStateMachine->SetGlobalState(FriezaGlobalState::Instance());

	}

	~Frieza() { delete m_pStateMachine; }

	//this must be implemented
	void Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);


	StateMachine<Frieza>* GetFSM()const { return m_pStateMachine; }


	//-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	bool		  Faint() const;
	void          TakeDamage(int damage);
	int           GetHelth();
	void		  Healing();
	bool		  FullHeath();

	int GetDistance();
	bool isArriveEarth();
	void UpdateDistance(int dis);
	void SetResetDistance();

};



#endif
