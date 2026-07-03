#include "register.h"

void register_8bit::load()
{
    if(ld.read() == sc_logic_1)
        //  std::cout << "@ " << sc_core::sc_time_stamp() 
        //           << " | Register: LOAD -> Data: " << inData.read() <<endl;
        regData.write(inData.read());
}

void register_8bit::output()
{
    outData.write(regData.read());
}

