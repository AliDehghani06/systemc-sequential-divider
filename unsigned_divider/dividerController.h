#ifndef DIVIDERCONTROLLER_H
#define DIVIDERCONTROLLER_H

#include <systemc.h>

SC_MODULE(controller)
{
    sc_in  <sc_logic> rst, clk, start, co, subSign; 
    sc_out <sc_logic> clrA, clrC, ldQ;
    sc_out <sc_logic> ldM;
    sc_out <sc_logic> shA, Qin, ldA, shQ, ce;
    sc_out <sc_logic> sel;
    sc_out <sc_logic> done;
    sc_in<sc_lv<3>> countResult;

    enum states {INIT, SUB_SHIFT, LOAD_Q, LOAD_M, LOAD_A, SHIFT_Q, SHIFT, SUB, WAIT3, WAIT2, OUT_Q, OUT_A}; // Fixed typo here

    sc_signal <states> p_state, n_state; 

    SC_CTOR(controller)
    {
        SC_METHOD(comb_S_func);
        sensitive << start << co << p_state<<subSign;

        SC_METHOD(comb_O_func);
        sensitive << p_state << subSign;

        SC_METHOD(seq_func);
        sensitive << clk.pos() << rst;
    }

    void comb_S_func();
    void comb_O_func();
    void seq_func();
};

#endif
