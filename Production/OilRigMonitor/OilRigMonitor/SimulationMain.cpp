/*******************************************************************
 *   SimulationMain.cpp
 *   Timothy Finnegan
 *   Programming Assignment 1: Oil Rig Monitor
 *
 *   This program is entirely my own work
 *******************************************************************/

#include "Simulation.h"

void main()
{
	Simulation *sim = new Simulation();
	sim->initSim(sim);
	sim->run();
}