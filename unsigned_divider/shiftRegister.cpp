#include "shiftRegister.h"

void shiftRegister_8bit::process()
{
    /*
    Order of priority:
        1. load new data
        2. shift registered data
    */
    if (ld.read() == sc_logic_1){
        
        regData.write(inData.read());
                }
    else if (sh.read() == sc_logic_1)
    {
        sc_lv<8> currentData = regData.read();
        sc_lv<8> next;

        next.range(7, 1) = currentData.range(6, 0);
        next[0] = sin.read();

        regData.write(next);
        sout.write(currentData.get_bit(7));
    }
}

void shiftRegister_8bit::output()
{
    outData.write(regData.read());
}