// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtop___024root__trace_chg_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgBit(oldp+0,(vlSelf->top__DOT__w0));
        bufp->chgBit(oldp+1,(vlSelf->top__DOT__w1));
        bufp->chgBit(oldp+2,(vlSelf->top__DOT__w2));
        bufp->chgBit(oldp+3,(vlSelf->top__DOT__w3));
        bufp->chgBit(oldp+4,(vlSelf->top__DOT__w4));
        bufp->chgBit(oldp+5,(vlSelf->top__DOT__w5));
        bufp->chgBit(oldp+6,(vlSelf->top__DOT__w6));
        bufp->chgBit(oldp+7,(vlSelf->top__DOT__w7));
        bufp->chgBit(oldp+8,(vlSelf->top__DOT__w8));
        bufp->chgBit(oldp+9,(vlSelf->top__DOT__w9));
        bufp->chgBit(oldp+10,(vlSelf->top__DOT__w10));
        bufp->chgBit(oldp+11,(vlSelf->top__DOT__w11));
        bufp->chgBit(oldp+12,(vlSelf->top__DOT__w12));
        bufp->chgBit(oldp+13,(vlSelf->top__DOT__w13));
        bufp->chgBit(oldp+14,(vlSelf->top__DOT__w14));
        bufp->chgBit(oldp+15,(vlSelf->top__DOT__w15));
        bufp->chgBit(oldp+16,(vlSelf->top__DOT__w16));
        bufp->chgCData(oldp+17,(vlSelf->top__DOT____Vcellinp__u_1_1__sel),2);
        bufp->chgCData(oldp+18,(vlSelf->top__DOT____Vcellinp__u_1_2__sel),2);
        bufp->chgCData(oldp+19,(vlSelf->top__DOT____Vcellinp__u_1_3__sel),2);
        bufp->chgBit(oldp+20,(((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                ? ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                    ? (IData)(vlSelf->top__DOT__w13)
                                    : (IData)(vlSelf->top__DOT__w9))
                                : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                    ? (IData)(vlSelf->top__DOT__w0)
                                    : (IData)(vlSelf->top__DOT__w9)))));
        bufp->chgBit(oldp+21,(((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                ? ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                    ? (IData)(vlSelf->top__DOT__w14)
                                    : (IData)(vlSelf->top__DOT__w10))
                                : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                    ? (IData)(vlSelf->top__DOT__w0)
                                    : (IData)(vlSelf->top__DOT__w10)))));
        bufp->chgBit(oldp+22,(((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                ? ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                    ? (IData)(vlSelf->top__DOT__w15)
                                    : (IData)(vlSelf->top__DOT__w11))
                                : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                    ? (IData)(vlSelf->top__DOT__w0)
                                    : (IData)(vlSelf->top__DOT__w11)))));
        bufp->chgBit(oldp+23,(((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                ? ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                    ? (IData)(vlSelf->top__DOT__w16)
                                    : (IData)(vlSelf->top__DOT__w12))
                                : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                    ? (IData)(vlSelf->top__DOT__w0)
                                    : (IData)(vlSelf->top__DOT__w12)))));
        bufp->chgBit(oldp+24,(((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                ? ((~ (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel)) 
                                   & (IData)(vlSelf->top__DOT__w13))
                                : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                    ? (IData)(vlSelf->top__DOT__w9)
                                    : (IData)(vlSelf->top__DOT__w13)))));
        bufp->chgBit(oldp+25,(((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                ? ((~ (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel)) 
                                   & (IData)(vlSelf->top__DOT__w14))
                                : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                    ? (IData)(vlSelf->top__DOT__w10)
                                    : (IData)(vlSelf->top__DOT__w14)))));
        bufp->chgBit(oldp+26,(((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                ? ((~ (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel)) 
                                   & (IData)(vlSelf->top__DOT__w15))
                                : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                    ? (IData)(vlSelf->top__DOT__w11)
                                    : (IData)(vlSelf->top__DOT__w15)))));
        bufp->chgBit(oldp+27,(((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                ? ((~ (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel)) 
                                   & (IData)(vlSelf->top__DOT__w16))
                                : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                    ? (IData)(vlSelf->top__DOT__w12)
                                    : (IData)(vlSelf->top__DOT__w16)))));
    }
    bufp->chgCData(oldp+28,(vlSelf->din),8);
    bufp->chgCData(oldp+29,(vlSelf->shamt),3);
    bufp->chgBit(oldp+30,(vlSelf->LR));
    bufp->chgBit(oldp+31,(vlSelf->AL));
    bufp->chgCData(oldp+32,(vlSelf->dout),8);
    bufp->chgBit(oldp+33,((1U & ((IData)(vlSelf->din) 
                                 >> 7U))));
    bufp->chgBit(oldp+34,((1U & ((IData)(vlSelf->din) 
                                 >> 6U))));
    bufp->chgBit(oldp+35,((1U & ((IData)(vlSelf->din) 
                                 >> 5U))));
    bufp->chgBit(oldp+36,((1U & ((IData)(vlSelf->din) 
                                 >> 4U))));
    bufp->chgBit(oldp+37,((1U & ((IData)(vlSelf->din) 
                                 >> 3U))));
    bufp->chgBit(oldp+38,((1U & ((IData)(vlSelf->din) 
                                 >> 2U))));
    bufp->chgBit(oldp+39,((1U & ((IData)(vlSelf->din) 
                                 >> 1U))));
    bufp->chgBit(oldp+40,((1U & (IData)(vlSelf->din))));
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
