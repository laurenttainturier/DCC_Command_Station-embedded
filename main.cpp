#include <iostream>
#include <bitset>
#include <vector>

#include "datatosend.h"
#include "packet.h"
#include "clock.h"

using namespace std;

DigitalOut dout(LED1);
DigitalIn userButton(USER_BUTTON);

int main()
{
    cout << "\n\n====================== start =====================\r" << endl;

    DataToSend data = DataToSend();
    Clock c(&data);
    
    cout << "\rPress <Enter> to start the station\r" << endl;
    while (userButton) {}
    c.start();
    
    bool power = true;
    string address, command;
    
    while(power)
    {
        getline(cin, address, ' ');
        getline(cin, command);
        
        // cout << "addr: " << address << " com: " << command << "\r" << endl;
        
        Packet p4(atoi(address.c_str()), atoi(command.c_str()));
        data.stack(p4);
    }

    return 0;
}