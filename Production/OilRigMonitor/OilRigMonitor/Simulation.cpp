/*******************************************************************
 *   Simulation.cpp
 *   Timothy Finnegan
 *   Programming Assignment 1: Oil Rig Monitor
 *
 *   This program is entirely my own work
 *******************************************************************/

#include "Simulation.h"
#include "OilFieldDataParser.h"
#include "Well.h"
#include "Sensor.h"


Simulation::Simulation() {}

Simulation::~Simulation() {}

void Simulation::initSim(Simulation *sim)
{
	cout << "Please enter the name of the data file:";
	cin >> filename;
	cout << endl;
	dp = new OilFieldDataParser(filename);
	numWells = dp->getWellCount();

	char wellID[32];
	char wellOptr[32];
	int sensorCount;
	bool moreWells = true;

	char sentype[32];
	char cname[32];
	char dname[32];
	double sen_min;
	double sen_max;
	double *min_ptr = &sen_min;
	double *max_ptr = &sen_max;
	char senunits[32];
	char abbrev[32];
	bool moreSensors = true;

	while (moreWells)
	{
		moreWells = dp->getWellData(wellID, wellOptr, &sensorCount);
		if (moreWells)
		{
			Well *wx = new Well(wellID, wellOptr, sensorCount);
			m_vWells.push_back(wx);
			//m_vWSubscribers.push_back(wx);
			while (moreSensors)
			{
				moreSensors = dp->getSensorData(wellID, sentype, cname, dname, min_ptr, max_ptr, senunits, abbrev);
				if (moreSensors)
				{
					Sensor *sx = new Sensor(wellID, sentype, cname, dname, sen_min, sen_max, senunits, abbrev);
					wx->m_vSensors.push_back(sx);
					//wx->m_vSSubscribers.push_back(sx);
				}
			}
			moreSensors = true;
		}
	}
}


void Simulation::run()
{
	struct _timeb   tStruct;
    double          thisTime;
    double          outputTime;
    bool            done = false;  // while loop flag
	int hit;     // key hit flag
    char ch;     // character key which was hit
	char ch2;	//second level menu entry
	int w_selection;
	Sensor *s_selection = NULL;
	Well *temp = NULL;

	struct _timeb
    {
    int   dstflag;   // holds a non-zero value if daylight saving time is in effect
    long  millitm;   // time in milliseconds since the last one-second hack
    long  time;      // time in seconds since 00:00:00 1/1/1970
    long  timezone;  // difference in minutes moving west from UTC
    };

    _ftime(&tStruct);	// Get start time
    thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0); // Convert to double
    outputTime = thisTime + 5.0; // Set next 5 second interval time

	cout << "|-----------------------------------------|\n";
	cout << "| Oil Rig Monitor\n";
	cout << "|-----------------------------------------|\n";

    while(!done)     // Start an eternal loop
    {
        _ftime(&tStruct);    // Get the current time
        thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0); // Convert to double
        // Check for 5 second interval to print status to screen
        if(thisTime >= outputTime)
        {
			cout << "|-----------------------------------------|\n";
			cout << "| Well Report:\n";
			cout << "|-----------------------------------------|\n";
			cout << "| To edit wells, press 'w'.\n";
			cout << "| To edit sensors for a well, press 's'.\n";
			cout << "| To exit the application, press 'q'.\n";
			cout << "|-----------------------------------------|\n\n";

			for(vector<Well *>::iterator it = m_vWSubscribers.begin(); it != m_vWSubscribers.end(); it++)
			{
				//print out the well informatio using call to the current iteration of the subscribed wells
				cout << "|-----------------------------------------|\n";
				(*it)->report();
				for(vector<Sensor *>::iterator sens_it = (*it)->m_vSSubscribers.begin(); sens_it != (*it)->m_vSSubscribers.end(); sens_it++)
				{
					//print out the sensor information using calls to current iteration of the subscribed sensors
					cout << "|\t" << (*sens_it)->getDisplayName() << ": " << (*sens_it)->report() << " " << (*sens_it)->getAbbreviation() << endl;
				}
				cout << "|-----------------------------------------|\n";
			}

			/*This is the implementation of the report method using an index rather than an iterator. Will be reworked before completion.
			for(int i = 0; i < numWells; i++)
			{
				cout << "|-----------------------------------------|\n";
				m_vWSubscribers.at(i)->report();	//print out the well ID and operator
				for (int j = 0; j < 8; j++)
				{
					Sensor *s_temp = m_vWSubscribers.at(i)->m_vSSubscribers.at(j);					//temp pointer for attempted neatness
					cout << "|\t" << s_temp->getDisplayName() << ": " << s_temp->report() << " " << s_temp->getAbbreviation() << endl;;	//print out the sensor information using calls to current iteration of the subscribed sensors
				}
				cout << "|-----------------------------------------|\n";
			}
			*/

            outputTime += 5.0; // Set time for next 5 second interval
        }
		hit = _kbhit(); //See if a key has been pressed
		if (hit)
			{
				ch = _getch();	// Get the key pressed
				ch = tolower(ch);
				switch (ch)
				{
				case 'w':
					{
						cout << "Would you like to add ('a') or remove ('r') a well?\n";
						cin >> ch2;
						ch2 = tolower(ch2);
						if (ch2 == 'a')
						{
							cout << "Please select a well from the list: \n";
							for(int i = 0; i < numWells; i++)	//iterate through the elements in the well storage vector using the *.at() function
							{
								cout << i << ". " << m_vWells.at(i)->getID() << " - " << m_vWells.at(i)->getOperator() << endl;
							}
							cin >> w_selection;	//use int to select the element
							temp = m_vWells.at(w_selection);	//assign that element to a temp pointer
							wSubscribe(temp);					//add the selected well to the list of "subscribers"
						}
						else if (ch2 == 'r')
						{
							cout << "Please select a well from the list: \n";
							for(int i = 0; i < numWells; i++)
							{
								cout << i << ". " << m_vWells.at(i)->getID() << " - " << m_vWells.at(i)->getOperator() << endl;
							}
							cin >> w_selection;
							temp = m_vWells.at(w_selection);
							wUnsubscribe(temp);
						}
					}
					break;

				case 's':
					{
						cout << "Would you like to add ('a') or remove ('r') a sensor?\n";
						cin >> ch2;
						ch2 = tolower(ch2);
						if (ch2 == 'a')
						{
							cout << "Please select a well from the list: \n";
							for(int i = 0; i < numWells; i++)
							{
								cout << i << ". " << m_vWells.at(i)->getID() << " - " << m_vWells.at(i)->getOperator() << endl;
							}
							cin >> w_selection;
							temp = m_vWells.at(w_selection);

							cout << "Please select a sensor from the list: \n";
							s_selection = temp->selectSensor();
							temp->sSubscribe(s_selection);
						}
						else if (ch2 == 'r')
						{
							cout << "Please select a well from the list: \n";
							for(int i = 0; i < numWells; i++)
							{
								cout << i << ". " << m_vWells.at(i)->getID() << " - " << m_vWells.at(i)->getOperator() << endl;
							}
							cin >> w_selection;
							temp = m_vWells.at(w_selection);
							cout << "Please select a sensor from the list: \n";
							s_selection = temp->selectSensor();
							temp->sUnsubscribe(s_selection);
						}
					}
					break;

				case 'q':
				{
					done = true;
				}
				break;

				default:
					break;
				}
			}
   }
}

void Simulation::report()	//for each well in the subscribers list, call the report function for the name and ID
{
	for(int i = 0; i < numWells; i++)
	{
		m_vWSubscribers.at(i)->report();
	}
}

void Simulation::wSubscribe(Well *wsub)	//for each
{
	m_vWSubscribers.push_back(wsub);
}

bool Simulation::wUnsubscribe(Well *wsub)
{
	for(vector<Well *>::iterator it = m_vWSubscribers.begin(); it != m_vWSubscribers.end(); it++)
	{
		if (wsub == *it)
		{
			m_vWSubscribers.erase(it);
			return true;
		}
	}
	return false;
}
