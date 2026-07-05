#include <systemc.h>
#include "twosComplementAbs.h"
#include "unsigned_divider/register.h"
#include "unsigned_divider/divider.h"
#include "adder.h"
#include "subtractor_p2.h"
#include "negator.h"
#include "mux_p2.h"
#include "dff.h"

SC_MODULE(dividerSigned_8bit)
{
    sc_in<sc_logic> clk, rst, start;
    sc_in<sc_lv<8> > inBus;

    sc_out<sc_lv<8> > outBus;
    sc_out<sc_logic> done;

    sc_signal<sc_lv<8> > absOut;
    sc_signal<sc_lv<8> > divOut;

    sc_signal<sc_logic> signM;
    sc_signal<sc_logic> signQ;

    sc_signal<sc_logic> signM_in;
    sc_signal<sc_logic> signQ_in;

    sc_signal<sc_logic> R0;
    sc_signal<sc_logic> R0_reg;
    sc_signal<sc_logic> R0_en;

    sc_signal<sc_logic> sel13;
    sc_signal<sc_logic> sel2;

    sc_signal<sc_logic> loadM;
    sc_signal<sc_logic> loadQ;
    sc_signal<sc_logic> sel;
    sc_signal<sc_logic> dummyCarry;

    sc_signal<sc_lv<8> > divOutPlus1;
    sc_signal<sc_lv<8> > mux1Out;
    sc_signal<sc_lv<8> > mux1OutInvert;
    sc_signal<sc_lv<8> > finalQ;

    sc_signal<sc_lv<8> > TrueR;
    sc_signal<sc_lv<8> > finalR;
    sc_signal<sc_lv<8> > absM;

    sc_signal<sc_lv<8> > const_one;
    sc_signal<sc_lv<8> > const_zero;
    sc_signal<sc_logic> cin_zero;

    divider_8bit *div;
    twosComplementAbs *abs_unit;
    register_8bit *absMRegister;
    adder_8bit *q_incrementer;
    subtractor_8bit_p2 *r_subtractor;

    negator_8bit *q_negator;

    mux_8bit_p2 *mux1;
    mux_8bit_p2 *mux2;
    mux_8bit_p2 *mux3;
    mux_8bit_p2 *mux4;
    mux_8bit_p2 *mux_final;

    dff *signM_ff;
    dff *signQ_ff;
    dff *R0_ff;

    void comb_logic()
    {
        signM_in.write(inBus.read()[7]);
        signQ_in.write(inBus.read()[7]);

        sel2.write(signM.read() ^ signQ.read());

        if ((divOut.read().to_uint() == 0) & (sel.read() == SC_LOGIC_0))
            R0.write(SC_LOGIC_1);
        else
            R0.write(SC_LOGIC_0);

        sel13.write(signQ.read() & (R0.read() == SC_LOGIC_0));

        if (sel.read() == SC_LOGIC_0)
            R0_en.write(SC_LOGIC_1);
        else
            R0_en.write(SC_LOGIC_0);
    }

    void latch_results()
    {
    //     if (done.read() == SC_LOGIC_1)
    //     {
    //         R0_reg.write(R0.read());
    //     }
    }

    SC_CTOR(dividerSigned_8bit)
    {
        cin_zero.write(SC_LOGIC_0);
        const_one.write("00000001");
        const_zero.write("00000000");

        abs_unit = new twosComplementAbs("abs_unit");
        abs_unit->in(inBus);
        abs_unit->out(absOut);

        absMRegister = new register_8bit("absM");
        absMRegister->inData(absOut);
        absMRegister->ld(loadM);
        absMRegister->clk(clk);
        absMRegister->outData(absM);

        div = new divider_8bit("Divider");
        div->clk(clk);
        div->rst(rst);
        div->start(start);
        div->inBus(absOut);
        div->outBus(divOut);
        div->loadM(loadM);
        div->loadQ(loadQ);
        div->select(sel);
        div->done(done);

        signM_ff = new dff("signM_ff");
        signM_ff->clk(clk);
        signM_ff->rst(rst);
        signM_ff->en(loadM);
        signM_ff->d(signM_in);
        signM_ff->q(signM);

        signQ_ff = new dff("signQ_ff");
        signQ_ff->clk(clk);
        signQ_ff->rst(rst);
        signQ_ff->en(loadQ);
        signQ_ff->d(signQ_in);
        signQ_ff->q(signQ);

        R0_ff = new dff("R0_ff");
        R0_ff->clk(clk);
        R0_ff->rst(rst);
        R0_ff->en(R0_en);
        R0_ff->d(R0);
        R0_ff->q(R0_reg);

        q_incrementer = new adder_8bit("q_inc");
        q_incrementer->a(divOut);
        q_incrementer->b(const_one);
        q_incrementer->cin(cin_zero);
        q_incrementer->sum(divOutPlus1);
        q_incrementer->cout(dummyCarry);

        mux1 = new mux_8bit_p2("mux1");
        mux1->a(divOut);
        mux1->b(divOutPlus1);
        mux1->sel(sel13);
        mux1->y(mux1Out);

        q_negator = new negator_8bit("q_neg");
        q_negator->in(mux1Out);
        q_negator->out(mux1OutInvert);

        mux2 = new mux_8bit_p2("mux2");
        mux2->a(mux1Out);
        mux2->b(mux1OutInvert);
        mux2->sel(sel2);
        mux2->y(finalQ);

        r_subtractor = new subtractor_8bit_p2("r_sub");
        r_subtractor->a(absM);
        r_subtractor->b(divOut);
        r_subtractor->diff(TrueR);

        mux3 = new mux_8bit_p2("mux3");
        mux3->a(divOut);
        mux3->b(TrueR);
        mux3->sel(sel13);
        mux3->y(finalR);

        mux_final = new mux_8bit_p2("mux_final");
        mux_final->a(finalR);
        mux_final->b(finalQ);
        mux_final->sel(sel);
        mux_final->y(outBus);

        SC_METHOD(comb_logic);
        sensitive << inBus << signM << signQ << divOut << sel << R0;

        SC_METHOD(latch_results);
        sensitive << clk.pos();
    }
};
