#include "upCounter.h"

void upCounter_3bit::process()
{
    /*
    Order of priority:
        1. clear(reset) counter to zero
        2. up count
    */
    if (clr.read() == sc_logic_1){
        outData.write("000");
        co.write(sc_logic_0);
    }
    else if (ce.read() == sc_logic_1)
    {
        sc_uint<3> currentValue = outData.read();

        if(currentValue == 6)
            co.write(sc_logic_1);
        else
            co.write(sc_logic_0);

        if(currentValue < 7)
            currentValue += 1;
        else
            currentValue = 0;
            
        outData.write(currentValue);
    }
    /*cout << "aaaaaaaaaaaaa" << endl;
    cout << co.read() << endl;
    cout << outData.read() << endl;*/
} 

