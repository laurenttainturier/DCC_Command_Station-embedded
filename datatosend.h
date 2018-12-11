/***********************************************************************
                         DataToSend  -  description
                           -------------------
    début              : 15/08/2018
    copyright          : (C) 2018 par Laurent Tainturier
***********************************************************************/

//-------------- <DataToSend> Classe Interface (DataToSend.h file) ---------------
#if !defined ( DataToSend_H )
#define DataToSend_H

//------------------------------------------------------ Used Interfaces
#include <queue>
#include <map>
#include "packet.h"

using namespace std;

//------------------------------------------------------------ Constants

//----------------------------------------------------------------------
// <DataToSend> class role
// This class is used to hold data to be send by the output stream
//----------------------------------------------------------------------

class DataToSend
{
//--------------------------------------------------------------- PUBLIC
public:

//------------------------------------------------------ Public Methodes
    void stack(Packet packet);

    bool unstack();
    // get the first bit of the first packet string if it is not empty
    // Otherwise, replace the packet string at the end of the queue
    // <packets> if needed

    void resendPacket(Packet packet);

//------------------------------------------- Constructors - destructors
    DataToSend(const DataToSend &aDataToSend);
    // Mode d'emploi (constructeur de copie) :
    // Cette méthode est juste déclarée

    DataToSend();
    //Constructeur de la classe DataToSend

    virtual ~DataToSend();
    // Destructeur de la classe DataToSend

//-------------------------------------------------------------- PRIVATE
protected:
//------------------------------------------------- Protected attributes
    queue<Packet> packets;
    map<int, int> remainingSending;
    Packet IDLE;
};

#endif // DataToSend_H
