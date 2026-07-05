#include "subtractor.h"

void subtractor_8bit::subtract()
{
    /*Because of using int(not uint) we have to use one bit more
    and the result is signed integer number and we can use the 
    MSB of outData as control signal
    if 0 : number is valid(load new data in A)
    else : number is invalid(Don't load new data in A)
    Also numbers are in 2's comp representation*/
    
    sc_lv<8> a = AData.read();
    sc_lv<8> b = BData.read();

    if(a.is_01() && b.is_01())
    {
        sc_int<9> aData = a.to_int();
        sc_int<9> bData = b.to_int();
        sc_int<9> result = aData - bData;

        
        outData.write(result);
        cout << "@ " << sc_core::sc_time_stamp() 
          << " | Subtractor -> A: " << a 
          << ", B: " << b 
          << "outData : " << result.to_string(SC_BIN) 
          << std::endl;
    }
}
