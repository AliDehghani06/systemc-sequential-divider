#include <systemc.h>

#include "adder.h"

SC_MODULE(twosComplementAbs)
{
    sc_in< sc_lv<8> > in;
    sc_out< sc_lv<8> > out;

    adder_8bit *adder;

    sc_signal< sc_lv<8> > xor_sig;
    sc_signal< sc_lv<8> > zero_sig;
    sc_signal< sc_logic > cin_sig;
    sc_signal< sc_logic > cout_sig;

    void xor_process()
    {
        sc_lv<8> a = in.read();
        sc_logic sign = a[7];

        sc_lv<8> temp;

        for(int i = 0; i < 8; i++)
            temp[i] = a[i] ^ sign;

        xor_sig.write(temp);
        cin_sig.write(sign);
    }

    SC_CTOR(twosComplementAbs)
    {
        adder = new adder_8bit("adder");

        zero_sig.write("00000000");

        adder->a(xor_sig);
        adder->b(zero_sig);
        adder->cin(cin_sig);

        adder->sum(out);
        adder->cout(cout_sig);

        SC_METHOD(xor_process);
        sensitive << in;
    }
};
