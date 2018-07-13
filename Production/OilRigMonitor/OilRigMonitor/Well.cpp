/*******************************************************************
 *   Well.cpp
 *   Timothy Finnegan
 *   Programming Assignment 1: Oil Rig Monitor
 *
 *   This program is entirely my own work
 *******************************************************************/

#include "Well.h"
#include "Sensor.h"

Well::Well()	//Default constructor
{
	strcpy(m_id, "");
	strcpy(m_opr, "");
}

Well::Well(char *id, char *optr, int sens)
{
	strcpy(m_id, id);
	strcpy(m_opr, optr);
	vector<Sensor *>m_vSensors(sens);
}

Well::~Well() {}

void Well::report()
{
	cout << "| " << getOperator() << " " << getID() << endl;
}

Sensor *Well::selectSensor()
{
	Sensor *selection;
	int select;
	for(int i = 0; i < 8; i++)
	{
		cout << i << ". " << m_vSensors.at(i)->getDisplayName() << endl;
	}
	cin >> select;
	selection = m_vSensors.at(select);
	return selection;
}

void Well::sSubscribe(Sensor *ssub)
{
	m_vSSubscribers.push_back(ssub);
}

bool Well::sUnsubscribe(Sensor *ssub)	//Removes sensor from display. Argument is the sensor to be removed.
{
	for(vector<Sensor *>::iterator it = m_vSSubscribers.begin(); it != m_vSSubscribers.end(); it++)
	{
		if (ssub == *it)
		{
			m_vSSubscribers.erase(it);
			return true;
		}
	}
	return false;
}

void Well::setID(char *id)
{
	strcpy(m_id, id);
}

void Well::setOperator(char *oper)
{
	strcpy(m_opr, oper);
}

char *Well::getID()
{
    char *id = new char[strlen(m_id) + 1];
    strcpy(id, m_id);
    return id;
}

char *Well::getOperator()
{
	char *oper = new char[strlen(m_opr) + 1];
	strcpy(oper, m_opr);
    return oper;
}
