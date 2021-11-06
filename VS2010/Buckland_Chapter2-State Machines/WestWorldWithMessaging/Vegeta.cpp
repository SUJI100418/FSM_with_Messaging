#include "Vegeta.h"

bool Vegeta::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}

void Vegeta::Update()
{
	//set text color to green
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	m_iHunger += 1;

	m_pStateMachine->Update();
}

bool Vegeta::Hunger()const
{
	if (m_iHunger >= Vegy_HungerLevel) { return true; }

	return false;
}

bool Vegeta::Faint()const
{
	if(m_iHelth == 0) { return true; }

	return false;
}

void Vegeta::TakeDamage(int damage)
{
	m_iHelth -= damage;
}

int Vegeta::GetHelth()
{
	if (m_iHelth < 0)
	{
		m_iHelth = 0;
	}

	return m_iHelth; 
}

void Vegeta::Healing()
{
	m_iHelth += 5;

	if (m_iHelth > Vegy_MaxHelth)
	{
		m_iHelth = Vegy_MaxHelth;
	}
}

bool Vegeta::FullHeath()
{
	if (m_iHelth == Vegy_MaxHelth)
	{
		return true;
	}
	else
	{
		return false;
	}
}

