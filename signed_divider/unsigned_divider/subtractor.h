#ifndef SUBTRACTOR_H
#define SUBTRACTOR_H

#include <systemc.h>

SC_MODULE(subtractor_8bit)
{
    sc_in<sc_lv<8> > AData;
    sc_in<sc_lv<8> > BData;
    sc_out<sc_lv<9> > outData;

    SC_CTOR(subtractor_8bit)
    {
        SC_METHOD(subtract);
            sensitive << AData << BData;
    }

    void subtract();
};

#endif