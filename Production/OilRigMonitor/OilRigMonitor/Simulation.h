/*******************************************************************
 *   Simulation.h
 *   Timothy Finnegan
 *   Programming Assignment 1: Oil Rig Monitor
 *
 *   This program is entirely my own work
 *******************************************************************/
#ifndef SIMULATION_H
#define SIMULATION_H

#include "OilFieldDataParser.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <sys/types.h>     // needed for the _ftime() function
#include <sys/timeb.h>     // contains definition of _timeb struct
#include <time.h>          // needed for other time functions and structures
#include <conio.h>
#include <stdio.h>

class Well;
class Display;
class Sensor;

class Simulation
{
	private:
		OilFieldDataParser *dp;
		char filename[32];
		int numWells;
		vector<Well *>m_vWells;	//storage for well instances
		vector<Well *>m_vWSubscribers;	//list of displaying wells
		
	public:
		Simulation();
		~Simulation();
		void initSim(Simulation *);
		void run();
		void report();
		void wSubscribe(Well *);
		bool wUnsubscribe(Well *);
};
#endif
