/*******************************************************************
 *   Sensor.cpp
 *   Timothy Finnegan
 *   Programming Assignment 1: Oil Rig Monitor
 *
 *   This program is entirely my own work
 *******************************************************************/

#include "Sensor.h"


Sensor::Sensor()
{
	strcpy(m_wellID, "");
	strcpy(m_type, "");
	strcpy(m_className, "");
	strcpy(m_displayName, "");
	m_minVal = 0.0;
	m_maxVal = 0.0;
	strcpy(m_units, "");
	strcpy(m_unitAbbrev, "");

	srand((unsigned int)(time(NULL))); // Seed the random number generator
}

Sensor::Sensor(char *ID, char *type, char *cname, char *dname, double min, double max, char *unit, char *abbr)
{
	strcpy(m_wellID, ID);
	strcpy(m_type, type);
	strcpy(m_className, cname);
	strcpy(m_displayName, dname);
	m_minVal = min;
	m_maxVal = max;
	strcpy(m_units, unit);
	strcpy(m_unitAbbrev, abbr);
}

Sensor::~Sensor() {}

double Sensor::report()
{
	int inc = 1;
	int temp_max = 100;

	if(m_maxVal != 0.0)
	{
		double randVal = m_minVal + (rand() % (int)(m_maxVal - m_minVal));
		return randVal;
	}
	else
	{
		double m_maxVal = rand() % (int)(inc + 10);
		double randVal = (m_minVal + (rand() % (int)(temp_max - m_minVal)));
		return randVal;
	}
	//return testVal;
}

void Sensor::setWellID(char *ID)
{
	strcpy(m_wellID, ID);
}

void Sensor::setType(char *type)
{
	strcpy(m_type, type);
}

void Sensor::setClassName(char *cname)
{
	strcpy(m_className, cname);
}

void Sensor::setDisplayName(char *dname)
{
	strcpy(m_displayName, dname);
}

void Sensor::setMin(double min)
{
	m_minVal = min;
}

void Sensor::setMax(double max)
{
	m_minVal = max;
}

void Sensor::setUnits(char *unit)
{
	strcpy(m_units, unit);
}

void Sensor::setAbbreviation(char *abbr)
{
	strcpy(m_unitAbbrev, abbr);
}

char *Sensor::getWellID()
{
    char *ID = new char[strlen(m_wellID) + 1];
    strcpy(ID, m_wellID);
    return ID;
}

char *Sensor::getType()
{
    char *type = new char[strlen(m_type) + 1];
	strcpy(type, m_type);
    return type;
}

char *Sensor::getClassName()
{
	char *cname = new char[strlen(m_className) + 1];
	strcpy(cname, m_className);
    return cname;
}

char *Sensor::getDisplayName()
{
	char *dname = new char[strlen(m_displayName) + 1];
	strcpy(dname, m_displayName);
    return dname;
}

double Sensor::getMin()
{
	return m_minVal;
}

double Sensor::getMax()
{
	return m_maxVal;
}

char *Sensor::getUnits()
{
	char *unit = new char[strlen(m_units) + 1];
	strcpy(unit, m_units);
    return unit;
}

char *Sensor::getAbbreviation()
{
	char *abbr = new char[strlen(m_unitAbbrev) + 1];
	strcpy(abbr, m_unitAbbrev);
    return abbr;
}
