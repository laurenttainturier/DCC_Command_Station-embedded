/***********************************************************************
                         DataToSend  -  description
                           -------------------
    début              : 07/02/2018
    copyright          : (C) 2018 par Laurent Tainturier
***********************************************************************/

//---------- <DataToSend> class implementation (fichier DataToSend.cpp) ----------

//-------------------------------------------------------------- INCLUDE

//------------------------------------------------------- System Include
using namespace std;

#include <iostream>
#include <algorithm>

//----------------------------------------------------- Personal Include
#include "datatosend.h"

//------------------------------------------------------------ Constants
const signed int RESEND_NB(2);

//--------------------------------------------------------------- PUBLIC

//------------------------------------------------------ Public methodes
void DataToSend::stack(Packet packet)
{
    if (!packets.empty() && packets.back().getAddress() == packet.getAddress())
        packets.push(IDLE);
    packets.push(packet);
    remainingSending[packet.getAddress()] = RESEND_NB;
}

bool DataToSend::unstack()
{
    if (packets.empty())
       packets.push(IDLE);

    int bitToSend = packets.front().unstack();

    if (bitToSend == -1)
    {
        cout << "\r" << endl;
        Packet currentPacket = packets.front();
        packets.pop();

        if (packets.empty())
            packets.push(IDLE);

        resendPacket(currentPacket);

        return (bool)packets.front().unstack();
    }

    return (bool)bitToSend;
}

void DataToSend::resendPacket(Packet packet)
{
    // if the packet needs to be resend
    if (remainingSending[packet.getAddress()])
    {
        if (packets.back().getAddress() == packet.getAddress())
            packets.push(IDLE);
        packets.push(packet);
        remainingSending[packet.getAddress()]--;
    }
}

//-------------------------------------------- Constructors - destructor
DataToSend::DataToSend(const DataToSend &aDataToSend)
{
#ifdef MAP
    cout << "Call to <DataToSend> copy constructor" << endl;
#endif
    this->packets = aDataToSend.packets;
    this->remainingSending = aDataToSend.remainingSending;
}

DataToSend::DataToSend()
{
#ifdef MAP
    cout << "Call to <DataToSend> constructor" << endl;
#endif
    packets.push(IDLE);
}

DataToSend::~DataToSend()
{
#ifdef MAP
    cout << "Call to <DataToSend> destructor" << endl;
#endif
}

//-------------------------------------------------------------- PRIVATE

//---------------------------------------------------- Protected methods
