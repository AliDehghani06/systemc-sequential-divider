#include <systemc.h>

#include "adder.h"

SC_MODULE(subtractor_8bit_p2)
{
    sc_in< sc_lv<8> > a;
    sc_in< sc_lv<8> > b;
    sc_out< sc_lv<8> > diff;

    adder_8bit *adder;

    sc_signal< sc_lv<8> > b_inv_sig;
    sc_signal< sc_logic > cin_sig;
    sc_signal< sc_logic > cout_sig;

    void invert_process()
    {
        sc_lv<8> bv = b.read();
        sc_lv<8> temp;

        for(int i = 0; i < 8; i++)
            temp[i] = ~bv[i];

        b_inv_sig.write(temp);
        cin_sig.write(SC_LOGIC_1);
    }

    SC_CTOR(subtractor_8bit_p2)
    {
        adder = new adder_8bit("adder");

        adder->a(a);
        adder->b(b_inv_sig);
        adder->cin(cin_sig);
        adder->sum(diff);
        adder->cout(cout_sig);

        SC_METHOD(invert_process);
        sensitive << b;
    }
};
