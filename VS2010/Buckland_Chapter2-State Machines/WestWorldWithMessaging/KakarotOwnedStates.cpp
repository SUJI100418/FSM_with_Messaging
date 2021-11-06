#include "KakarotOwnedStates.h"
#include "Kakarot.h"

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

KakarotGlobalState* KakarotGlobalState::Instance()
{
	static KakarotGlobalState instance;

	return &instance;
}


void KakarotGlobalState::Execute(Kakarot* kaka)
{
	/*
	//1 in 10 chance of needing the bathroom (provided she is not already
	//in the bathroom)
	if ((RandFloat() < 0.1) &&
		!wife->GetFSM()->isInState(*VisitBathroom::Instance()))
	{
		wife->GetFSM()->ChangeState(VisitBathroom::Instance());
	}
	*/
}

bool KakarotGlobalState::OnMessage(Kakarot* kaka, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_TimeToRevenge:
	{
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << "\nMessage handled by " << GetNameOfEntity(kaka->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(kaka->ID()) << ": That's Freezer! He's coming to earth!";

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			kaka->ID(),        //ID of sender
			ent_Vegeta,            //ID of recipient
			Msg_FriezaCome,   //the message
			NO_ADDITIONAL_INFO);

		kaka->BattleWithFreezer(true);

		kaka->GetFSM()->ChangeState(Kaka_Battle::Instance());
	}

	return true;

	}//end switch



	return false;
}

//-------------------------------------------------------------------------DoHouseWork

DoTrainingAlone* DoTrainingAlone::Instance()
{
	static DoTrainingAlone instance;

	return &instance;
}


void DoTrainingAlone::Enter(Kakarot* kaka)
{
	cout << "\n" << GetNameOfEntity(kaka->ID()) << ": Go to KingKai's Planet, Time to Technique Practice!";
}


void DoTrainingAlone::Execute(Kakarot* kaka)
{
	if ((RandInt(0, 1) == 0) &&
		!kaka->GetFSM()->isInState(*FindSomeoneForBattle::Instance()))
	{
		kaka->GetFSM()->ChangeState(FindSomeoneForBattle::Instance());
	}
	else
	{
		switch (RandInt(0, 2))
		{
		case 0:

			cout << "\n" << GetNameOfEntity(kaka->ID()) << ": Technique Practice -> Kamehameha!!";

			break;

		case 1:

			cout << "\n" << GetNameOfEntity(kaka->ID()) << ": Technique Practice -> Meteor Smash!!";

			break;

		case 2:

			cout << "\n" << GetNameOfEntity(kaka->ID()) << ": Technique Practice -> Solar Flare !";

			break;
		}

		if (kaka->Hunger())
		{
			kaka->GetFSM()->ChangeState(RestAndRice::Instance());
		}
	}
}

void DoTrainingAlone::Exit(Kakarot* kaka)
{
}

bool DoTrainingAlone::OnMessage(Kakarot* kaka, const Telegram& msg)
{
	return false;
}

//================================================================

RestAndRice* RestAndRice::Instance()
{
	static RestAndRice instance;

	return &instance;
}

void RestAndRice::Enter(Kakarot* pKaka)
{
	if (pKaka->Location() != Restaurant && !pKaka->Faint())
	{
		pKaka->ChangeLocation(Restaurant);

		cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": " << "I'm starving. Let's have some food";
	}

	if (pKaka->Location() != KingKaiPlanet && pKaka->Faint())
	{
		pKaka->ChangeLocation(KingKaiPlanet);

		cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": >> move to King Kai's Planet, Need rest..";
	}
}

void RestAndRice::Execute(Kakarot* pKaka)
{
	if (pKaka->FullHeath())
	{
		if (pKaka->Hunger())
		{
			cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": " << "Go to Restaurant, (champ champ champ...)";
			pKaka->EatLotsOfFood();
			pKaka->GetFSM()->ChangeState(DoTrainingAlone::Instance());
		}
	}

	else if(!pKaka->FullHeath())
	{
		if (pKaka->FullHeath())
		{
			pKaka->GetFSM()->ChangeState(DoTrainingAlone::Instance());
		}
		pKaka->Healing();
		cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": " << "ZZZ... -> HP : " << pKaka->GetHelth();
	}
}


void RestAndRice::Exit(Kakarot* pKaka)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": " << "Enough ate and rested!";
}


bool RestAndRice::OnMessage(Kakarot* pKaka, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//====================================================================================================

FindSomeoneForBattle* FindSomeoneForBattle::Instance()
{
	static FindSomeoneForBattle instance;

	return &instance;
}

void FindSomeoneForBattle::Enter(Kakarot* pKaka)
{
	cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": " << "I'm bored to training alone...";
}

void FindSomeoneForBattle::Execute(Kakarot* pKaka)
{
	//let the wife know I'm home
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		pKaka->ID(),        //ID of sender
		ent_Vegeta,            //ID of recipient
		Msg_WannaBattle,   //the message
		NO_ADDITIONAL_INFO);

	//pKaka->GetFSM()->ChangeState(WaitForBattle::Instance());
}

void FindSomeoneForBattle::Exit(Kakarot* pKaka)
{
	//cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": " << "Enough ate and rested!";
}

bool FindSomeoneForBattle::OnMessage(Kakarot* pKaka, const Telegram& msg)
{
	//send msg to global message handler
	//SetTextColor(BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_RED);  //파란배경 빨간글자

	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	switch (msg.Msg)
	{
	case Msg_No:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(pKaka->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": Maybe Next time..";


		pKaka->GetFSM()->ChangeState(DoTrainingAlone::Instance());

		return true;
	}

	case Msg_Yes:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(pKaka->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": I know a good place. Follow me.";

		pKaka->GetFSM()->ChangeState(Kaka_Battle::Instance());

		return true;
	}
	}


	return false;
}

//======================================================

Kaka_Battle* Kaka_Battle::Instance()
{
	static Kaka_Battle instance;
	return &instance;
}

void Kaka_Battle::Enter(Kakarot* pKaka)
{
	if (!pKaka->GetBattleOpponent()) //with vegy
	{
		if (pKaka->Location() != SomewhereOnEarth)
		{
			pKaka->ChangeLocation(SomewhereOnEarth);

			cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": " << ">> go to some where on Earth, Come here!";
		}
	}
	else  //with freezer
	{
		if (pKaka->Location() != SomewhereOnEarth)
		{
			pKaka->ChangeLocation(SomewhereOnEarth);
		}
	}



}

void Kaka_Battle::Execute(Kakarot* pKaka)
{
	if (!pKaka->GetBattleOpponent()) //with vegy
	{
		if (pKaka->Faint())
		{
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
				pKaka->ID(),        //ID of sender
				ent_Vegeta,            //ID of recipient
				Msg_YouWin,   //the message
				NO_ADDITIONAL_INFO);

			pKaka->GetFSM()->ChangeState(RestAndRice::Instance());
		}
		else
		{
			switch (RandInt(0, 2))
			{
			case 0:

				cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": [Defense : MISS] -> HP : " << pKaka->GetHelth();

				break;

			case 1:

				pKaka->TakeDamage(1);
				cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": [Demege Frome Kakarot : - 1] -> HP : " << pKaka->GetHelth();

				break;

			case 2:

				pKaka->TakeDamage(4);
				cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": [Critical Demege Frome Kakarot : - 4] -> HP : " << pKaka->GetHelth();

				break;
			}
		}
	}
	else  // with Freezer
	{
		if (pKaka->Faint())
		{
			pKaka->Healing();
			cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": [EAT SENZU BEAN] -> HP : " << pKaka->GetHelth();
		}

		switch (RandInt(0, 2))
		{
		case 0:

			cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": [Defense : MISS] -> HP : " << pKaka->GetHelth();

			break;

		case 1:

			pKaka->TakeDamage(1);
			cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": [Demege Frome Frieza : - 1] -> HP : " << pKaka->GetHelth();

			break;

		case 2:

			pKaka->TakeDamage(4);
			cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": [Critical Demege Frome Frieza : - 4] -> HP : " << pKaka->GetHelth();

			break;
		}
	}
	
}


void Kaka_Battle::Exit(Kakarot* pKaka)
{
	if (pKaka->Faint())
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": >> Goku fainted!";
	}
	//let the wife know I'm home

}


bool Kaka_Battle::OnMessage(Kakarot* pKaka, const Telegram& msg)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	switch (msg.Msg)
	{
	case Msg_YouWin:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(pKaka->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": <Kakarot Win!>";


		pKaka->GetFSM()->ChangeState(RestAndRice::Instance());

		return true;
	}

	case Msg_FriezaFaint:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(pKaka->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pKaka->ID()) << ": Let's fight again next time!, Frieza!";


		pKaka->GetFSM()->ChangeState(RestAndRice::Instance());

		return true;
	}
	}
	//send msg to global message handler
	return false;
}