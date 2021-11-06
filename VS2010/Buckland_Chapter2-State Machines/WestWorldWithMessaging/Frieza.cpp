#include "Frieza.h"

bool Frieza::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}

void Frieza::Update()
{
	//set text color to green
	SetTextColor(0x0005);

	m_pStateMachine->Update();
}


bool Frieza::Faint()const
{
	if (m_iHelth == 0) { return true; }

	return false;
}

void Frieza::TakeDamage(int damage)
{
	m_iHelth -= damage;
}

int Frieza::GetHelth()
{
	if (m_iHelth < 0)
	{
		m_iHelth = 0;
	}

	return m_iHelth;
}

void Frieza::Healing()
{
	m_iHelth += 5;

	if (m_iHelth > Frieza_MaxHelth)
	{
		m_iHelth = Frieza_MaxHelth;
	}
}

bool Frieza::FullHeath()
{
	if (m_iHelth == Frieza_MaxHelth)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Frieza::isArriveEarth()
{
	if (m_iDistance <= 0)
	{
		return true;
	}

	else
	{
		return false;
	}
}

int Frieza::GetDistance()
{
	if (m_iDistance < 0)
	{
		m_iDistance = 0;
	}

	return m_iDistance;
}

void Frieza::UpdateDistance(int dis)
{
	m_iDistance -= dis;
}

void Frieza::SetResetDistance()
{
	m_iDistance = DistanceFromeEarth;
}


