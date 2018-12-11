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
const timestamp_t BIT0DURATION(5700);
const timestamp_t BIT1DURATION(1000);

//--------------------------------------------------------------- PUBLIC

//------------------------------------------------------ Public methodes 
void Clock::oscillate()
{
    dccOut = !dccOut; 
    if (transitionNb % 2 == 0)
    { 
        getNextStateValue();
    }
    transitionNb++;
}

void Clock::getNextStateValue()
{
    bool new_state = dataToSend->unstack();
    if (state != new_state)
    {
        state = new_state;
        if (state)
            bitDuration = BIT1DURATION;
        else
            bitDuration = BIT0DURATION;
        flipper.attach_us(callback(this, &Clock::oscillate), bitDuration);
    }    
    cout << state << flush;
}

void Clock::start()
{
    dccOut = !dccOut;
    cout << "start\r" << endl;
    cout << bitDuration << "\r" << endl;
    flipper.attach_us(callback(this, &Clock::oscillate), bitDuration);
}

Ticker& Clock::getFlipper()
{
    return flipper;
}

timestamp_t Clock::getBitDuration()
{
    return bitDuration;
}

void Clock::setBitDuration(timestamp_t time)
{
    bitDuration  = time;
}

//-------------------------------------------- Constructors - destructor
Clock::Clock(DataToSend *aDataToSend) :
        state(0), bitDuration(BIT1DURATION), transitionNb(0), dccOut(LED1)
{

    cout << "Call to <Clock> constructor" << endl;

    dataToSend = aDataToSend;
}

Clock::~Clock()
{
#ifdef MAP
    cout << "Call to <Clock> destructor" << endl;
#endif
}

//---------------------------------------------------------------- PRIVE

//---------------------------------------------------- Protected methods
