#include <systemc.h>
#include "dividerSignedTB.h"

int sc_main(int argc, char **argv){

    dividerSignedTB TB1("testbench1");

    sc_trace_file* vcdfile;
    vcdfile = sc_create_vcd_trace_file("DividerSigned_test");

    vcdfile->set_time_unit(1, SC_NS);

    sc_trace(vcdfile, TB1.clk, "clk");
    sc_trace(vcdfile, TB1.rst, "rst");
    sc_trace(vcdfile, TB1.start, "start");

    sc_trace(vcdfile, TB1.inBus, "inBus");
    sc_trace(vcdfile, TB1.outBus, "outBus");

    sc_trace(vcdfile, TB1.done, "done");

    sc_start();

    sc_close_vcd_trace_file(vcdfile);

    return 0;
}
