#include "Kakarot.h"

bool Kakarot::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Kakarot::Update()
{
	//set text color to green
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

	m_iHunger += 1;

	m_pStateMachine->Update();

}

bool Kakarot::Hunger()const
{
	if (m_iHunger >= Kaka_HungerLevel) { return true; }

	return false;
}

bool Kakarot::Faint()const
{
	if (m_iHelth == 0) { return true; }

	return false;
}

void Kakarot::TakeDamage(int damage)
{
	m_iHelth -= damage;
}

int Kakarot::GetHelth()
{
	if (m_iHelth < 0)
	{
		m_iHelth = 0;
	}

	return m_iHelth;
}

void Kakarot::Healing()
{
	m_iHelth += 5;

	if (m_iHelth > Kaka_MaxHelth)
	{
		m_iHelth = Kaka_MaxHelth;
	}

}

bool Kakarot::FullHeath()
{
	if (m_iHelth == Kaka_MaxHelth)
	{
		return true;
	}
	else
	{
		return false;
	}

}