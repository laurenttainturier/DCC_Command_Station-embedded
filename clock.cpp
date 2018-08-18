/***********************************************************************
                         Clock  -  description
                           -------------------
    début              : 07/02/2018
    copyright          : (C) 2018 par Laurent Tainturier
***********************************************************************/

//---------- <Clock> class implementation (fichier Clock.cpp) ----------

//-------------------------------------------------------------- INCLUDE

//------------------------------------------------------- System Include
using namespace std;

#include <iostream>

//----------------------------------------------------- Personal Include
#include "clock.h"

//------------------------------------------------------------ Constants
// duration in micro seconds
const signed int BIT0DURATION(57);
const signed int BIT1DURATION(100);

//--------------------------------------------------------------- PUBLIC

//------------------------------------------------------ Public methodes 
void Clock::oscillate()
{
    output = !output;
    if (!transitionNb % 2)
        getNextStateValue();
    transitionNb++;
}

void Clock::getNextStateValue()
{
    bool new_state = dataToSend.unstack();
    if (state != new_state)
    {
        state = new_state;
        if (state)
            bitDuration = BIT1DURATION;
        else
            bitDuration = BIT0DURATION;
        flipper.attach(&oscillate, bitDuration);
    }
}

//-------------------------------------------- Constructors - destructor
Clock::Clock(DataToSend &aDataToSend) :
        state(0), transitionNb(0), bitDuration(BIT0DURATION)
{
#ifdef MAP
    cout << "Call to <Clock> constructor" << endl;
#endif
    dataToSend = aDataToSend;
}

Clock::~Clock()
{
#ifdef MAP
    cout << "Call to <Clock> destructor" << endl;
#endif
}

void Clock::start()
{
    output = !output;
    flipper.attach(&oscillate, bitDuration);
}

//---------------------------------------------------------------- PRIVE

//---------------------------------------------------- Protected methods
