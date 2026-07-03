#include "dividerDatapath.h"

void datapath::subResultAssign()
{
    sc_lv<9> result = subResult.read(); 
    subSign.write(result.get_bit(8));
    inA.write(result.range(7, 0));
}

void datapath::extract_q_msb()
{
    q_msb.write(outQ.read()[7]);
}
