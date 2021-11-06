#include "VegetaOwnedStates.h"
#include "Vegeta.h"

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

VegetaGlobalState* VegetaGlobalState::Instance()
{
	static VegetaGlobalState instance;

	return &instance;
}


void VegetaGlobalState::Execute(Vegeta* vegy)
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

bool VegetaGlobalState::OnMessage(Vegeta* vegy, const Telegram& msg)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	switch (msg.Msg)
	{

	case Msg_FriezaCome:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(vegy->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(vegy->ID()) << ": I'm on my way, Kakarot";

		vegy->BattleWithFreezer(true);

		vegy->ChangeLocation(SomewhereOnEarth);
		vegy->GetFSM()->ChangeState(Vegy_Battle::Instance());


		return true;

	}
	
	case Msg_WannaBattle:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(vegy->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		if ((RandInt(0, 1) == 0))
		{
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
				vegy->ID(),        //ID of sender
				ent_Kakarot,            //ID of recipient
				Msg_Yes,   //the message
				NO_ADDITIONAL_INFO);

			SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

			cout << "\n" << GetNameOfEntity(vegy->ID()) << ": I'll take you down with all my power.";

			vegy->BattleWithFreezer(false);

			vegy->ChangeLocation(SomewhereOnEarth);
			vegy->GetFSM()->ChangeState(Vegy_Battle::Instance());

			return true;
		}

		else
		{
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
				vegy->ID(),        //ID of sender
				ent_Kakarot,            //ID of recipient
				Msg_No,   //the message
				NO_ADDITIONAL_INFO);

			SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

			cout << "\n" << GetNameOfEntity(vegy->ID()) << ": That's useless.";

			return true;
		}
	}

	}//end switch


	return false;
}

//-------------------------------------------------------------------------

UseGravityMachineForTraining* UseGravityMachineForTraining::Instance()
{
	static UseGravityMachineForTraining instance;

	return &instance;
}


void UseGravityMachineForTraining::Enter(Vegeta* vegy)
{
	cout << "\n" << GetNameOfEntity(vegy->ID()) << ": >> move to Gravity Room, I'll be stronger than now.";
	vegy->m_gravity = 1;
}


void UseGravityMachineForTraining::Execute(Vegeta* vegy)
{
	if ((RandInt(0, 2) == 0) &&
		!vegy->GetFSM()->isInState(*RestAndEatWithFamily::Instance()))
	{
		vegy->GetFSM()->ChangeState(RestAndEatWithFamily::Instance());
	}
	else
	{
		cout << "\n" << GetNameOfEntity(vegy->ID()) << ": (*Training) Go up to " << vegy->m_gravity * 100 << " times Earth's gravity.";
		vegy->m_gravity++;
	}

}

void UseGravityMachineForTraining::Exit(Vegeta* vegy)
{
	if (vegy->Location() == CapsuleCorp && vegy->FullHeath())
	{
		cout << "\n" << GetNameOfEntity(vegy->ID()) << ": Today is enough. I'm hungry.";
	}

}

bool UseGravityMachineForTraining::OnMessage(Vegeta* vegy, const Telegram& msg)
{
	return false;
}

//================================================================

RestAndEatWithFamily* RestAndEatWithFamily::Instance()
{
	static RestAndEatWithFamily instance;

	return &instance;
}

void RestAndEatWithFamily::Enter(Vegeta* pVegy)
{
	if (pVegy->Location() != Restaurant && pVegy->FullHeath())
	{
		pVegy->ChangeLocation(Restaurant);

		cout << "\n" << GetNameOfEntity(pVegy->ID()) << ": " << ">> move to Restaurant, Bulma. What is today's dinner?";
	}
	else if(!pVegy->FullHeath())
	{
		pVegy->ChangeLocation(CapsuleCorp);
		cout << "\n" << GetNameOfEntity(pVegy->ID()) << ": " << ">> move to Home, I need get some rest.. ";
	}
}

void RestAndEatWithFamily::Execute(Vegeta* pVegy)
{
	if (pVegy->FullHeath() && pVegy->Location() == CapsuleCorp)
	{
		cout << "\n" << GetNameOfEntity(pVegy->ID()) << ": Enough Rest!";
		pVegy->GetFSM()->ChangeState(UseGravityMachineForTraining::Instance());
	}

	if (pVegy->Location() == Restaurant)
	{
		if (pVegy->Hunger())
		{
			cout << "\n" << GetNameOfEntity(pVegy->ID()) << ": " << "(champ champ champ...) Pretty good";

			pVegy->EatLotsOfFood();
			pVegy->GetFSM()->ChangeState(UseGravityMachineForTraining::Instance());
		}
	}

	else if(!pVegy->FullHeath())
	{
		pVegy->Healing();
		cout << "\n" << GetNameOfEntity(pVegy->ID()) << ": " << "ZZZ... -> HP : " << pVegy->GetHelth();
	}

}


void RestAndEatWithFamily::Exit(Vegeta* pVegy)
{
	if (pVegy->Location() == Restaurant)
	{
		cout << "\n" << GetNameOfEntity(pVegy->ID()) << ": " << "Trunks, you getting Weaker. you should go to Gravity room with me.";
		SetTextColor(0x0007);

		cout << "\n" << "Trunks" << ": " << "No Thanks, Dad.";
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}

}


bool RestAndEatWithFamily::OnMessage(Vegeta* pVegy, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//====================================================================================================

Vegy_Battle* Vegy_Battle::Instance()
{
	static Vegy_Battle instance;

	return &instance;
}

void Vegy_Battle::Enter(Vegeta* pVegy)
{
	if (pVegy->Location() != SomewhereOnEarth)
	{
		pVegy->ChangeLocation(SomewhereOnEarth);
	}
	
	cout << "\n" << GetNameOfEntity(pVegy->ID()) << ": " << " >> Follow Kakarot";

}

void Vegy_Battle::Execute(Vegeta* pVegy)
{
	if (!pVegy->GetBattleOpponent()) //with vegy
	{
		if (pVegy->Faint())
		{
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
				pVegy->ID(),        //ID of sender
				ent_Kakarot,            //ID of recipient
				Msg_YouWin,   //the message
				NO_ADDITIONAL_INFO);

			pVegy->GetFSM()->ChangeState(RestAndEatWithFamily::Instance());
		}
		else
		{
			switch (RandInt(0, 2))
			{
			case 0:

				cout << "\n" << GetNameOfEntity(pVegy->ID()) << ": [Defense : MISS] -> HP : " << pVegy->GetHelth();

				break;

			case 1:

				pVegy->TakeDamage(1);
				cout << "\n" << GetNameOfEntity(pVegy->ID()) << ": [Demege Frome Kakarot : - 1] -> HP : " << pVegy->GetHelth();

				break;

			case 2:

				pVegy->TakeDamage(4);
				cout << "\n" << GetNameOfEntity(pVegy->ID()) << ": [Critical Demege Frome Kakarot : - 4] -> HP : " << pVegy->GetHelth();

				break;
			}
		}
	}

	else  //with Freezer
	{
		if (pVegy->Faint())
		{
			pVegy->Healing();
			cout << "\n" << GetNameOfEntity(pVegy->ID()) << ": [EAT SENZU BEAN] -> HP : " << pVegy->GetHelth();
		}

		switch (RandInt(0, 2))
		{
		case 0:

			cout << "\n" << GetNameOfEntity(pVegy->ID()) << ": [Defense : MISS] -> HP : " << pVegy->GetHelth();

			break;

		case 1:

			pVegy->TakeDamage(1);
			cout << "\n" << GetNameOfEntity(pVegy->ID()) << ": [Demege Frome Frieza : - 1] -> HP : " << pVegy->GetHelth();

			break;

		case 2:

			pVegy->TakeDamage(4);
			cout << "\n" << GetNameOfEntity(pVegy->ID()) << ": [Critical Demege Frome Frieza : - 4] -> HP : " << pVegy->GetHelth();

			break;
		}
	}


}


void Vegy_Battle::Exit(Vegeta* pVegy)
{
	if (pVegy->Faint())
	{
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pVegy->ID()) << ": >> Vegata fainted!";
	}

}


bool Vegy_Battle::OnMessage(Vegeta* pVegy, const Telegram& msg)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	switch (msg.Msg)
	{
	case Msg_YouWin:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(pVegy->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pVegy->ID()) << ": <Vegeta Win!>";


		pVegy->GetFSM()->ChangeState(RestAndEatWithFamily::Instance());

		return true;
	}

	case Msg_FriezaFaint:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(pVegy->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pVegy->ID()) << ": No biggie, Frieza";


		pVegy->GetFSM()->ChangeState(RestAndEatWithFamily::Instance());

		return true;
	}

	}
	//send msg to global message handler
	return false;
}