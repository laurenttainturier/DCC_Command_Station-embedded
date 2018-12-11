/*************************************************************************
                           Packet  -  description
                             -------------------
    début                : 17/08/18
    copyright            : (C) 2018 par laurent TAINTURIER
    e-mail               : laurent.tainturier@insa-lyon.fr
*************************************************************************/
//------- Réalisation de la classe <Packet> (fichier Packet.cpp) ---------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include <bitset>
#include "packet.h"

using namespace std;
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

void Packet::createPacket()
{
    bits = preamble.to_string<char, string::traits_type, string::allocator_type>();
    bits.append("0");
    bits.append(address.to_string<char, string::traits_type, string::allocator_type>());
    bits.append("0");
    bits.append(command.to_string<char, string::traits_type, string::allocator_type>());
    bits.append("0");
    bits.append(control.to_string<char, string::traits_type, string::allocator_type>());
    bits.append("1");
}

string Packet::getBits()
{
    return bits;
}

void Packet::toString()
{
    cout << "address " << address << endl;
    cout << "command " << command << endl;
    cout << "control " << control << endl;
    cout << "packet  " << bits << endl;
}

//------------------------------------------------- Surcharge d'opérateurs
Packet &Packet::operator=(const Packet &unPacket)
// Algorithme :
//
{
    this->index = unPacket.index;
    this->preamble = unPacket.preamble;
    this->address = unPacket.address;
    this->control = unPacket.control,
    this->bits = unPacket.bits;
    
    return *this;
}

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

Packet::Packet() : index(0)
{
    preamble = 32767;
    address = bitset<BYTE_LENGTH>(255);
    command = bitset<BYTE_LENGTH>(0);
    control = bitset<BYTE_LENGTH>(address ^ command);
    
    createPacket();
}

Packet::Packet(short signed int anAddress, short signed int aCommand):
    index(0)
{
    preamble = 32767;
    address = bitset<BYTE_LENGTH>(anAddress);
    command = bitset<BYTE_LENGTH>(aCommand);
    control = bitset<BYTE_LENGTH>(address ^ command);
    
    createPacket();
}

Packet::~Packet()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Packet>" << endl;
#endif
}

//----- Fin de ~Packet

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées