/*******************************************************************
 *   Sensor.h
 *   Timothy Finnegan
 *   Programming Assignment 1: Oil Rig Monitor
 *
 *   This program is entirely my own work
 *******************************************************************/
#ifndef SENSOR_H
#define SENSOR_H

#include <time.h>          // needed for other time functions and structures
#include <stdlib.h>
#include <iostream>
#include <vector>


using namespace std;

class Sensor
{
	private:
		char m_wellID[32];
		char m_type[32];
		char m_className[32];
		char m_displayName[32];
		double m_minVal;
		double m_maxVal;
		char m_units[32];
		char m_unitAbbrev[32];
		vector<Sensor *>m_vSensorSub;	//vector of pointers to instances of sensors that Display is subscribed to

	public:
		Sensor();
		Sensor(char *ID, char *type, char *cname, char *dname, double min, double max, char *unit, char *abbr);
		~Sensor();
		double report();

		void setWellID(char *);
		void setType(char *);
		void setClassName(char *);
		void setDisplayName(char *);
		void setMin(double);
		void setMax(double);
		void setUnits(char *);
		void setAbbreviation(char *);
		char *getWellID();
		char *getType();
		char *getClassName();
		char *getDisplayName();
		double getMin();
		double getMax();
		char *getUnits();
		char *getAbbreviation();

};
#endif
