/***********************************************************************
                         Clock  -  description
                           -------------------
    début              : 15/08/2018
    copyright          : (C) 2018 par Laurent Tainturier
***********************************************************************/

//-------------- <Clock> Classe Interface (Clock.h file) ---------------
#if !defined ( Clock_H )
#define Clock_H

//------------------------------------------------------ Used Interfaces
#include <queue>
#include "mbed.h"
#include "datatosend.h"

using namespace std;

//------------------------------------------------------------ Constants

//----------------------------------------------------------------------
// <Clock> class role
// This class is used to make transitions according to the content of 
// the class <DataToSend> queue that contains the bits needed to be send
//----------------------------------------------------------------------

class Clock
{
//--------------------------------------------------------------- PUBLIC
public:

//------------------------------------------------------ Public Methodes
    void oscillate();
    // called every 57us or 100us depending on 'state' value
    // this method change the state of the output either 1 or 0
    // calls changeState every two transitions to make sure if the 
    // frequency needs to be changed or not
    
    void start();
    // launch the chronometer that will change the state of the output
    // at regular intervals
    
    void changeState();
    // change the value of 'state' if needed
    
    void getNextStateValue();
    // get the next value of 'state' variable by looking to the queue of
    // the class 'DataToSend'
    
//------------------------------------------- Constructors - destructors
    Clock(const Clock &aClock);
    // Mode d'emploi (constructeur de copie) :
    // Cette méthode est juste déclarée

    Clock(DataToSend &aDataToSend);
    //Constructeur de la classe Clock

    virtual ~Clock();
    // Destructeur de la classe Clock

//-------------------------------------------------------------- PRIVATE
protected:

//--------------------------------------------------- Protected methodes

//------------------------------------------------- Protected attributes
    bool output;
    bool state;
    int bitDuration;
    int transitionNb;
    DataToSend dataToSend;
    Ticker flipper;
    DigitalOut dccOut(LED1);
};

#endif // Clock_H
