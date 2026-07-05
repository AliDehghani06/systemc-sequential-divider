#include "mux.h"

void mux_8bit::output()
{
    if(sel.read() == sc_logic_0)
        outData.write(inA.read());
    else if(sel.read() == sc_logic_1)
        outData.write(inB.read());
}