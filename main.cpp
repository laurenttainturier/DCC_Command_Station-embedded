#include <iostream>
#include <bitset>

#include "packet.h"
#include "datatosend.h"

int main()
{
    Packet p = Packet(57, {145});
    cout << p.getBits() << "\n" << endl;
    DataToSend data = DataToSend();
    data.stack(p);
    for (int i=0; i<420; i++)
    {
        if (i%42 == 0)
            cout << i << "\t";
        cout << data.unstack();
        if (i == 125)
            data.stack(Packet(57, {234}));
        if ((i+1)%42 == 0)
            cout << endl;
    }

    return 0;
}