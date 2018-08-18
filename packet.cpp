/*************************************************************************
                           Packet  -  description
                             -------------------
    début                : 17/08/18
    copyright            : (C) 2018 par laurent TAINTURIER
    e-mail               : laurent.tainturier@insa-lyon.fr
*************************************************************************/
//---------- Réalisation de la classe <Packet> (fichier Packet.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include <bitset>
#include "packet.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
short int Packet::unstack()
{
    if (index != bits.size())
        return bits[index++] == '1';

    index = 0;
    return -1;
}

int Packet::getAddress()
{
    return (int)address.to_ulong();
}

//------------------------------------------------- Surcharge d'opérateurs
Packet &Packet::operator=(const Packet &unPacket)
// Algorithme :
//
{
} //----- Fin de operator =

//-------------------------------------------- Constructeurs - destructeur
Packet::Packet(const Packet &unPacket)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Packet>" << endl;
#endif
    this->index = unPacket.index;
    this->preamble = unPacket.preamble;
    this->address = unPacket.address;
    this->control = unPacket.control,
    this->bits = unPacket.bits;
} //----- Fin de Packet (constructeur de copie)


Packet::Packet(short signed int anAddress, vector<short signed int> aCommand): index(0)
{
    preamble = bitset<PREAMBLE_LENGTH>(32767);
    address = bitset<BYTE_LENGTH>(anAddress);
    control = address;
    bits = preamble.to_string() + "0" + address.to_string() + "0";

    for (int i = 0; i < aCommand.size(); i++)
    {
        command.push_back(bitset<BYTE_LENGTH>(aCommand[i]));
        bits += command[i].to_string() + "0";
        control ^= aCommand[i];
    }

    bits += control.to_string() + "1";
}

Packet::~Packet()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Packet>" << endl;
#endif
}

string Packet::getBits()
{
    return bits;
}

void Packet::toString()
{
    cout << "address " << address << endl;
    for (int i=0; i<command.size(); i++)
        cout << "command " << command[i] << endl;
    cout << "control " << control << endl;
    cout << "packet  " << bits << endl;
}
//----- Fin de ~Packet

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées