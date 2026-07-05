#ifndef UPCOUNTER_H
#define UPCOUNTER_H

#include <systemc.h>

SC_MODULE(upCounter_3bit)
{
    sc_in<sc_logic> clk;
    sc_in<sc_logic> clr;
    sc_in<sc_logic> ce;
    sc_out<sc_logic> co;
    sc_out<sc_lv<3> > outData;

    SC_CTOR(upCounter_3bit)
    {
        SC_METHOD(process);
            sensitive << clk.pos();
    }

    void process();
};

#endif