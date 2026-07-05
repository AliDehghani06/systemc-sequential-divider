#include "dividerSignedTB.h"

void dividerSignedTB::clocking(){
    while(true){
        clk = SC_LOGIC_0;
        wait(5, SC_NS);

        clk = SC_LOGIC_1;
        wait(5, SC_NS);
    }
}

void dividerSignedTB::reseting(){
    rst = SC_LOGIC_1;
    wait(12, SC_NS);

    rst = SC_LOGIC_0;
}

void dividerSignedTB::inputing(){

    start = SC_LOGIC_0;
    inBus = "00000000";

    wait(20, SC_NS);

    start = SC_LOGIC_1;
    inBus = 37;
    wait(10, SC_NS);

    inBus = -5;
    wait(10, SC_NS);

    start = SC_LOGIC_0;

    wait(400, SC_NS);

    sc_stop();
}

void dividerSignedTB::displaying(){

    while(true){

        wait(done.posedge_event());

        int quotient = outBus.read().to_int();

        wait(clk.posedge_event());

        int remainder = outBus.read().to_int();

        cout << "@" << sc_time_stamp()
             << " | Division Complete -> Quotient: "
             << quotient
             << " , Remainder: "
             << remainder
             << endl;
    }
}
