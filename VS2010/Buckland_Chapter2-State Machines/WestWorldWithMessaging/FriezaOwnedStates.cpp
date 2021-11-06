#include "FriezaOwnedStates.h"
#include "Frieza.h"

//#include "MinerOwnedStates.h"

#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//-----------------------------------------------------------------------Global state

FriezaGlobalState* FriezaGlobalState::Instance()
{
	static FriezaGlobalState instance;

	return &instance;
}


void FriezaGlobalState::Execute(Frieza* free)
{

}

bool FriezaGlobalState::OnMessage(Frieza* free, const Telegram& msg)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);


	return false;
}

//-------------------------------------------------------------------------

CommandFriezaForce* CommandFriezaForce::Instance()
{
	static CommandFriezaForce instance;

	return &instance;
}


void CommandFriezaForce::Enter(Frieza* free)
{
	if (free->Location() != FriezaSpaceship && !free->Faint())
	{
		free->ChangeLocation(FriezaSpaceship);

		cout << "\n" << GetNameOfEntity(free->ID()) << ": " << "Everyone, sorry for the wait. The emperor of the universe has returned!";
	}

	if (free->Faint())
	{
		free->ChangeLocation(FriezaSpaceship);

		cout << "\n" << GetNameOfEntity(free->ID()) << ": >> Run off the Spaceship, I am Lord Frieza. None surpass me... ";
	}

}


void CommandFriezaForce::Execute(Frieza* free)
{
	//
	if (free->FullHeath())
	{
		cout << "\n" << GetNameOfEntity(free->ID()) << ": " << "Everyone, sorry for the wait. The emperor of the universe has returned!";

		free->GetFSM()->ChangeState(GoToEarth::Instance());
	}

	else if (!free->FullHeath())
	{
		free->Healing();
		cout << "\n" << GetNameOfEntity(free->ID()) << ": " << "ZZZ... -> HP : " << free->GetHelth();
	}


}

void CommandFriezaForce::Exit(Frieza* free)
{

}

bool CommandFriezaForce::OnMessage(Frieza* free, const Telegram& msg)
{
	return false;
}

//======================================================

GoToEarth* GoToEarth::Instance()
{
	static GoToEarth instance;

	return &instance;
}


void GoToEarth::Enter(Frieza* free)
{
	cout << "\n" << GetNameOfEntity(free->ID()) << ": >> Let's go to Earth.";
}


void GoToEarth::Execute(Frieza* free)
{
	if (!free->isArriveEarth())
	{
		free->UpdateDistance(3);
		cout << "\n" << GetNameOfEntity(free->ID()) << ": >> Distance from Earth -> " << free->GetDistance() <<" [ly]";
	}
	else
	{
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			free->ID(),        //ID of sender
			ent_Kakarot,            //ID of recipient
			Msg_TimeToRevenge,   //the message
			NO_ADDITIONAL_INFO);

		SetTextColor(0x0005);

		free->GetFSM()->ChangeState(Battle::Instance());
	}



}

void GoToEarth::Exit(Frieza* free)
{

}

bool GoToEarth::OnMessage(Frieza* free, const Telegram& msg)
{
	return false;
}

//===============================


Battle* Battle::Instance()
{
	static Battle instance;

	return &instance;
}


void Battle::Enter(Frieza* free)
{
	cout << "\n" << GetNameOfEntity(free->ID()) << ": >> Don't tell me you're surprised! Of course, my vengeance must be satisfied!";
}


void Battle::Execute(Frieza* free)
{
	if (free->Faint())
	{
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			free->ID(),        //ID of sender
			ent_Kakarot,            //ID of recipient
			Msg_FriezaFaint,   //the message
			NO_ADDITIONAL_INFO);

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			free->ID(),        //ID of sender
			ent_Vegeta,            //ID of recipient
			Msg_FriezaFaint,   //the message
			NO_ADDITIONAL_INFO);

		SetTextColor(0x0005);

		free->SetResetDistance();

		free->GetFSM()->ChangeState(CommandFriezaForce::Instance());
	}
	else
	{
		switch (RandInt(0, 2))
		{
		case 0:

			cout << "\n" << GetNameOfEntity(free->ID()) << ": [Defense : MISS] -> HP : " << free->GetHelth();

			break;

		case 1:

			free->TakeDamage(2);
			cout << "\n" << GetNameOfEntity(free->ID()) << ": [Demege From Goku & Vegeta : - 2] -> HP : " << free->GetHelth();

			break;

		case 2:

			free->TakeDamage(7);
			cout << "\n" << GetNameOfEntity(free->ID()) << ": [Critical Demege From Goku & Vegeta : - 7] -> HP : " << free->GetHelth();

			break;
		}
	}



}

void Battle::Exit(Frieza* free)
{

}

bool Battle::OnMessage(Frieza* free, const Telegram& msg)
{
	return false;
}