#include <systemc.h>

SC_MODULE(dff)
{
    sc_in<sc_logic> clk;
    sc_in<sc_logic> rst;
    sc_in<sc_logic> en;
    sc_in<sc_logic> d;
    sc_out<sc_logic> q;

    void process()
    {
        if (rst.read() == SC_LOGIC_1)
            q.write(SC_LOGIC_0);
        else
            if(en.read() == SC_LOGIC_1)
                q.write(d.read());
    }

    SC_CTOR(dff)
    {
        SC_METHOD(process);
        sensitive << clk.pos();
    }
};
