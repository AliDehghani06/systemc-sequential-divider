#ifndef ADDER_H
#define ADDER_H
#include <systemc.h>

SC_MODULE(adder_8bit)
{
    sc_in< sc_lv<8> > a;
    sc_in< sc_lv<8> > b;
    sc_in< sc_logic > cin;

    sc_out< sc_lv<8> > sum;
    sc_out< sc_logic > cout;

    void process()
    {
        sc_lv<8> av = a.read();
        sc_lv<8> bv = b.read();

        sc_lv<8> result;
        sc_logic carry = cin.read();

        for (int i = 0; i < 8; i++)
        {
            sc_logic ai = av[i];
            sc_logic bi = bv[i];

            sc_logic s = ai ^ bi ^ carry;
            sc_logic c = (ai & bi) | (ai & carry) | (bi & carry);

            result[i] = s;
            carry = c;
        }

        sum.write(result);
        cout.write(carry);
    }

    SC_CTOR(adder_8bit)
    {
        SC_METHOD(process);
        sensitive << a << b << cin;
    }
};
#endif