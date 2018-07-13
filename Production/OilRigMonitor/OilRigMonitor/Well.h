/*******************************************************************
 *   Well.h
 *   Timothy Finnegan
 *   Programming Assignment 1: Oil Rig Monitor
 *
 *   This program is entirely my own work
 *******************************************************************/
#ifndef WELL_H
#define WELL_H

#include <iostream>
#include <vector>
using namespace std;

class Sensor;
class Display;

class Well
{
	private:
		char m_id[32];		//well id number
		char m_opr[32];		//name of well operator
	public:
		vector<Sensor *>m_vSensors;	//vector of pointers to instances of Sensor contained within each well
		vector<Sensor *>m_vSSubscribers;	//list of displaying sensors

	public:
		Well();
		Well(char [32], char [32], int);
		~Well();
		void report();
		Sensor *selectSensor();
		void sSubscribe(Sensor *);
		bool sUnsubscribe(Sensor *);

		void setID(char *);
		void setOperator(char *);
		char *getID();
		char *getOperator();

};
#endif
