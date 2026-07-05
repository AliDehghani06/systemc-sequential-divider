#ifndef SHIFTREGISTERCLR_H
#define SHIFTREGISTERCLR_H

#include <systemc.h>

SC_MODULE(shiftRegisterClr_8bit)
{
    sc_in<sc_lv<8> > inData;
    sc_in<sc_logic> sh;
    sc_in<sc_logic> ld;
    sc_in<sc_logic> clr;
    sc_in<sc_logic> clk;
    sc_in<sc_logic> sin;
    sc_out<sc_logic> sout;
    sc_out<sc_lv<8> > outDate;

    sc_signal<sc_bv<8> > regData;

    SC_CTOR(shiftRegisterClr_8bit)
    {
        SC_METHOD(process);
            sensitive << clk.pos();

        SC_METHOD(output);
            sensitive << regData;
    }

    void process();
    void output();
};

#endif