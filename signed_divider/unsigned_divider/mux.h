#ifndef MUX_H
#define MUX_H

#include <systemc.h>

SC_MODULE(mux_8bit)
{
    sc_in<sc_lv<8> > inA;
    sc_in<sc_lv<8> > inB;
    sc_in<sc_logic> sel;
    sc_out<sc_lv<8> > outData;

    SC_CTOR(mux_8bit)
    {
        SC_METHOD(output);
            sensitive << inA << inB << sel;
    }

    void output();
};

#endif