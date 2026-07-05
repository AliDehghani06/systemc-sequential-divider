#include <systemc.h>

#include "adder.h"

SC_MODULE(negator_8bit)
{
    sc_in< sc_lv<8> > in;
    sc_out< sc_lv<8> > out;

    adder_8bit *adder;

    sc_signal< sc_lv<8> > inv_sig;
    sc_signal< sc_lv<8> > zero_sig;
    sc_signal< sc_logic > cin_sig;
    sc_signal< sc_logic > cout_sig;

    void invert_process()
    {
        sc_lv<8> a = in.read();
        sc_lv<8> inv;

        for(int i = 0; i < 8; i++)
            inv[i] = ~a[i];

        inv_sig.write(inv);
        zero_sig.write("00000000");
        cin_sig.write(SC_LOGIC_1);
    }

    SC_CTOR(negator_8bit)
    {
        adder = new adder_8bit("adder");

        adder->a(inv_sig);
        adder->b(zero_sig);
        adder->cin(cin_sig);

        adder->sum(out);
        adder->cout(cout_sig);

        SC_METHOD(invert_process);
        sensitive << in;
    }
};
