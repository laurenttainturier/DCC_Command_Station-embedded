/*************************************************************************
                           Packet  -  description
                             -------------------
    début                : 17/08/18
    copyright            : (C) 2018 par laurent TAINTURIER
    e-mail               : laurent.tainturier@insa-lyon.fr
*************************************************************************/
//------- Interface de la classe <Packet> (fichier Packet.h) -------------
#ifndef DCC_COMMAND_STATION_PACKET_H
#define DCC_COMMAND_STATION_PACKET_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

//------------------------------------------------------------- Constantes
const signed int PREAMBLE_VALUE(32767);
const signed int BYTE_LENGTH(8);
const signed int PREAMBLE_LENGTH(14);
const signed int PACKET_LENGTH(38);
const signed int PREAMBLE_BIT_NB(34);
const signed int ADDRESS_BIT_NB(17);
const signed int COMMAND_BIT_NB(8);
const signed int CONTROL_BIT_NB(0);

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe Packet
//
//
//------------------------------------------------------------------------

class Packet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // friend ostream &operator << (ostream &out, const Packet &packet);

    short int unstack();

    int getAddress();

    string getBits();
    
    void createPacket();

    void toString();

//------------------------------------------------- Surcharge d'opérateurs
    Packet &operator=(const Packet &unPacket);

//-------------------------------------------- Constructeurs - destructeur
    Packet(const Packet &unPacket);

    Packet(short signed int address, short signed int command);
    
    Packet();

    virtual ~Packet();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    signed int index;
    bitset<PREAMBLE_LENGTH> preamble;
    bitset<BYTE_LENGTH> address;
    bitset<BYTE_LENGTH> command;
    bitset<BYTE_LENGTH> control;
    string bits;
};

//-------------------------------- Autres définitions dépendantes de <Xxx>
#endif //DCC_COMMAND_STATION_PACKET_H

/*ostream &operator << (ostream &out, const Packet &packet)
{
    out << "address " << packet.address << endl;
    for (int i=0; i<packet.command.size(); i++)
        out << "command " << packet.command[i] << endl;
    out << "control " << packet.control << endl;
    out << "packet  " << packet.bits << endl;
    return out;
}*/
