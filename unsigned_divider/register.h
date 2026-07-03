#ifndef REGISTER_H
#define REGISTER_H

#include <systemc.h>

SC_MODULE(register_8bit)
{
    sc_in<sc_lv<8> > inData;
    sc_in<sc_logic> ld;
    sc_in<sc_logic> clk;
    sc_out<sc_lv<8> > outData;

    sc_signal<sc_bv<8> > regData;
    
    SC_CTOR(register_8bit)
    {
        SC_METHOD(load);
            sensitive << clk.pos();
        
        SC_METHOD(output);
            sensitive << regData;
    }

    void load();
    void output();
};

#endif