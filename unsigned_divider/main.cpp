#include <systemc.h>
#include "dividerTB.h"

int sc_main(int argc, char **argv){
    
    dividerTB TB1("testbench1");  

    sc_trace_file* vcdfile;
    vcdfile = sc_create_vcd_trace_file("Divider_test");
    
    vcdfile->set_time_unit(1, SC_NS);

    sc_trace(vcdfile, TB1.clk, "clk");
    sc_trace(vcdfile, TB1.rst, "rst");
    sc_trace(vcdfile, TB1.start, "start"); 
    sc_trace(vcdfile, TB1.inBus, "inBus");
    sc_trace(vcdfile, TB1.outBus, "outBus");
    sc_trace(vcdfile, TB1.done, "done");

    sc_trace(vcdfile, TB1.div->DP->outA, "Reg_A");
    sc_trace(vcdfile, TB1.div->DP->outQ, "Reg_Q");
    sc_trace(vcdfile, TB1.div->CNTRL->p_state, "State");

    sc_start();
    
    sc_close_vcd_trace_file(vcdfile);
    return 0; 
}
