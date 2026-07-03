#ifndef DIVIDER_H
#define DIVIDER_H

#include <systemc.h>

#include "dividerDatapath.h"
#include "dividerController.h"

SC_MODULE(divider_8bit){
    sc_in<sc_logic> clk, rst, start;
    sc_in<sc_lv<8> > inBus;
    sc_out< sc_lv<8> > outBus;
    sc_out<sc_logic> done;

    sc_signal<sc_logic> clrA, shA, ldA;
    sc_signal<sc_logic> shQ, ldQ, Qin;
    sc_signal<sc_logic> clrC, ce;
    sc_signal<sc_logic> ldM;
    sc_signal<sc_logic> sel;
    sc_signal<sc_logic> subSign, co;
    sc_signal<sc_lv<3>> count_sig; 

    datapath* DP;
    controller* CNTRL;

    SC_CTOR(divider_8bit){
        DP = new datapath("Datapath");
            DP->clk(clk);
            DP->ldA(ldA);
            DP->shA(shA);
            DP->clrA(clrA);
            DP->ldQ(ldQ);
            DP->shQ(shQ);
            DP->ldM(ldM);
            DP->Qsin(Qin);
            DP->clrC(clrC);
            DP->countEnable(ce);
            DP->muxSelect(sel);
            DP->inBus(inBus);
            DP->subSign(subSign);
            DP->co(co);
            DP->outBus(outBus);
            DP->countResult_out(count_sig);
        CNTRL = new controller("controller");
            CNTRL->rst(rst);
            CNTRL->clk(clk);
            CNTRL->start(start);
            CNTRL->co(co);
            CNTRL->subSign(subSign);
            CNTRL->clrA(clrA);
            CNTRL->clrC(clrC);
            CNTRL->ldQ(ldQ);
            CNTRL->ldM(ldM);
            CNTRL->shA(shA);
            CNTRL->Qin(Qin);
            CNTRL->ldA(ldA);
            CNTRL->shQ(shQ);
            CNTRL->ce(ce);
            CNTRL->sel(sel);
            CNTRL->done(done);
            CNTRL->countResult(count_sig);
    }

};

#endif