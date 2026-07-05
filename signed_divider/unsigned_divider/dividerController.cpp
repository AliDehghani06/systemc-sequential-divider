#include "dividerController.h"

void controller::comb_O_func() {
    clrA.write(sc_logic_0);
    clrC.write(sc_logic_0);
    ldQ.write(sc_logic_0);
    ldM.write(sc_logic_0);
    shA.write(sc_logic_0);
    Qin.write(sc_logic_0);
    ldA.write(sc_logic_0);
    shQ.write(sc_logic_0);
    ce.write(sc_logic_0);
    sel.write(sc_logic_0);
    done.write(sc_logic_0);
    
    switch (p_state.read()) {
        case INIT:
            done.write(sc_logic_0);
            break;
        case LOAD_Q:
            clrA.write(sc_logic_1);
            clrC.write(sc_logic_1);
            ldQ.write(sc_logic_1);
            break;
        case LOAD_M:
            ldM.write(sc_logic_1);
            shQ.write(sc_logic_1);
            shA.write(sc_logic_1);
            break;
        case SHIFT:
            shQ.write(sc_logic_1);
            shA.write(sc_logic_1);
            ce.write(sc_logic_1);
            break;
        case LOAD_A:
            ldA.write(sc_logic_1);     
            break;
        case SUB_SHIFT:
            if ((co.read()) != sc_logic_1) {
                shA.write(sc_logic_1);
            }
            else 
            Qin.write(sc_logic_1); 
            shQ.write(sc_logic_1);
            ce.write(sc_logic_1);
            break;
        case SUB:
            break;
        case OUT_A:
            done.write(sc_logic_1);
            sel.write(sc_logic_0);
            break;
        case OUT_Q:
            done.write(sc_logic_1);
            sel.write(sc_logic_1);
            break;
    }
}

void controller::comb_S_func() {
    n_state.write(INIT);
    switch (p_state.read()) {
        case INIT:
            if (start.read() == sc_logic_1) {
                n_state.write(LOAD_Q);
            } else {
                n_state.write(INIT);
            }
            break;
        case LOAD_Q:
            n_state.write(LOAD_M);
            break;
        case LOAD_M:
            n_state.write(SUB);
            break;
        case LOAD_A:
            n_state.write(SUB_SHIFT);
            break;
        case SHIFT:
            if ((co.read()) == sc_logic_1)
                n_state.write(OUT_A);
            n_state.write(SUB);
            break; 
        case SUB_SHIFT:
            if ((co.read()) == sc_logic_1)
                n_state.write(OUT_A);
            else 
                n_state.write(SUB);
            break; 
        case SUB:
            if (subSign.read() == sc_logic_0) {
                n_state.write(LOAD_A);
            } else {
                n_state.write(SHIFT);
            }
            break;
        case OUT_A:
            n_state.write(OUT_Q);
            break;
        case OUT_Q:
            n_state.write(INIT);
            break;
    }
}

void controller::seq_func() {
    if (rst.read() == sc_logic_1) {
        p_state.write(INIT);
    } else {
        p_state.write(n_state.read());
    }
}