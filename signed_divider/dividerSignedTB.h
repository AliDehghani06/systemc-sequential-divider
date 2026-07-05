#ifndef DIVIDERSIGNEDTB_H
#define DIVIDERSIGNEDTB_H

#include <systemc.h>
#include "dividerSigned.h"

SC_MODULE(dividerSignedTB){

    sc_signal<sc_logic> clk, rst, start;
    sc_signal<sc_lv<8> > inBus;
    sc_signal<sc_lv<8> > outBus;
    sc_signal<sc_logic> done;

    dividerSigned_8bit* div;

    SC_CTOR(dividerSignedTB){

        div = new dividerSigned_8bit("SignedDivider");

        div->clk(clk);
        div->rst(rst);
        div->start(start);
        div->inBus(inBus);
        div->outBus(outBus);
        div->done(done);

        SC_THREAD(inputing);
        SC_THREAD(reseting);
        SC_THREAD(clocking);
        SC_THREAD(displaying);
    }

    void inputing();
    void reseting();
    void clocking();
    void displaying();
};

#endif
