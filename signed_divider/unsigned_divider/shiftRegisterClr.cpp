#include "shiftRegisterClr.h"

void shiftRegisterClr_8bit::process()
{
    /*
    Order of priority:
        1. clear (reset) register to zero
        2. load new data
        3. shift registered data
    */

    
    if (clr.read() == sc_logic_1)
    {   
        regData.write("00000000");

    }
    else if (ld.read() == sc_logic_1)
    {
        
        regData.write(inData.read());
        cout <<" A "<< "@" << sc_core::sc_time_stamp() 
              << " | outDate: " << inData.read() 
              << " | sin: " << sin.read() 
              << " | ld: " << ld.read() 
              << " | sh: " << sh.read() 
              << " | clr: " << clr.read() << std::endl;
    }
    else if (sh.read() == sc_logic_1)
    {
        sc_lv<8> currentData = regData.read();
        sc_logic s = sin.read();

         if ((s == SC_LOGIC_0 || s == SC_LOGIC_1))
        {
            sc_lv<8> next;

            next.range(7, 1) = currentData.range(6, 0);
            next[0] = sin.read();

            regData.write(next);
            sout.write(currentData[7]);
            cout <<" A "<< "@" << sc_core::sc_time_stamp() 
              << " | next: " << next
              << " | sin: " << sin.read() 
              << " | ld: " << ld.read() 
              << " | sh: " << sh.read() 
              << " | clr: " << clr.read() << std::endl;
        }
        
    }
}

void shiftRegisterClr_8bit::output()
{
    outDate.write(regData.read());
}