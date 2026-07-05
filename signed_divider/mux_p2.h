#ifndef MUX_P2_H
#define MUX_P2_H

#include <systemc.h>

SC_MODULE(mux_8bit_p2) {
    sc_in<sc_lv<8> > a;
    sc_in<sc_lv<8> > b;
    sc_in<sc_logic> sel;
    sc_out<sc_lv<8> > y;

    void process() {
        if (sel.read() == SC_LOGIC_0)
            y.write(a.read());
        else
            y.write(b.read());
    }

    SC_CTOR(mux_8bit_p2) {
        SC_METHOD(process);
        sensitive << a << b << sel;
    }
};

#endif
