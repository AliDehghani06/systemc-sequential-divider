#include "dividerTB.h"

void dividerTB::clocking(){
    while(true){
        clk = SC_LOGIC_0;
        wait(5, SC_NS); 
        clk = SC_LOGIC_1;
        wait(5, SC_NS); 
    }
}

void dividerTB::reseting(){
    rst = SC_LOGIC_1;
    wait(12, SC_NS);
    rst = SC_LOGIC_0; 
}

void dividerTB::inputing(){
    start = SC_LOGIC_0;
    inBus = "00000000";
    wait(20, SC_NS);

    start = SC_LOGIC_1;
    inBus = 37;
    wait(20, SC_NS);
    start = SC_LOGIC_0;
    inBus = 12;
    wait(10, SC_NS);
    
    
    wait(500, SC_NS);


    sc_stop();
}

void dividerTB::displaying(){
    while(true){
        wait(done.posedge_event());
        
        int quotient = outBus.read().to_uint();
        
        wait(clk.posedge_event());
        int remainder = outBus.read().to_uint();
        
        cout << "@" << sc_time_stamp() << " | Division Complete -> Quotient: " 
             << quotient << ", Remainder: " << remainder << endl; 
    }
}
