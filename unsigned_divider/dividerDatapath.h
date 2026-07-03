#include <systemc.h>
#include "shiftRegisterClr.h"
#include "shiftRegister.h"
#include "register.h"
#include "subtractor.h"
#include "upCounter.h"
#include "mux.h"

SC_MODULE(datapath)
{
    // Port Declaration
    sc_in<sc_logic> clk;
    sc_in<sc_logic> ldA, shA, clrA;
    sc_in<sc_logic> ldQ, shQ;
    sc_in<sc_logic> ldM;
    sc_in<sc_logic> Qsin;
    sc_in<sc_logic> clrC, countEnable;
    sc_in<sc_logic> muxSelect;
    sc_in<sc_lv<8> > inBus;
    sc_out<sc_logic> co;
    sc_out<sc_logic> subSign;
    sc_out<sc_lv<8> > outBus;

    // Signal Declaration
    sc_signal<sc_logic> q_msb;
    sc_signal<sc_lv<9> > subResult;
    sc_signal<sc_lv<8> > inA;
    sc_signal<sc_lv<8> > outA;
    sc_signal<sc_lv<8> > outQ;
    sc_signal<sc_lv<8> > outM;
    sc_signal<sc_lv<8> > subIn1;
    sc_out<sc_lv<3>> countResult_out;
    sc_signal<sc_logic> Qsout;
    sc_signal<sc_logic> Asin;
    sc_signal<sc_logic> Asout;

    // Instantiation
    shiftRegisterClr_8bit *A;
    shiftRegister_8bit *Q;
    register_8bit *M;
    subtractor_8bit *sub;
    upCounter_3bit *C;
    mux_8bit *mux;

    SC_CTOR(datapath)
    {
        A = new shiftRegisterClr_8bit("A_shiftRegister");
            A->inData(inA);
            A->sh(shA);
            A->ld(ldA);
            A->clr(clrA);
            A->clk(clk);
            A->sin(q_msb);
            A->sout(Asout);
            A->outDate(outA);

        Q = new shiftRegister_8bit("Q_shiftRegister");
            Q->inData(inBus);
            Q->clk(clk);
            Q->ld(ldQ);
            Q->sh(shQ);
            Q->sin(Qsin);
            Q->sout(Qsout);
            Q->outData(outQ);

        M = new register_8bit("M_register");
            M->inData(inBus);
            M->ld(ldM);
            M->clk(clk);
            M->outData(outM);

        sub = new subtractor_8bit("subtractor");
            sub->AData(outA);
            sub->BData(outM);
            sub->outData(subResult);

        C = new upCounter_3bit("C_upCounter");
            C->clk(clk);
            C->clr(clrC);
            C->ce(countEnable);
            C->co(co);
            C->outData(countResult_out);

        mux = new mux_8bit("mux");
            mux->inA(outA);
            mux->inB(outQ);
            mux->sel(muxSelect);
            mux->outData(outBus);

        SC_METHOD(subResultAssign);
            sensitive << subResult;
        
        SC_METHOD(extract_q_msb);
            sensitive << outQ;
        SC_METHOD(checkco);
            sensitive << co << countResult_out << countEnable << subResult;
    }

    void subResultAssign();
    void extract_q_msb();
};