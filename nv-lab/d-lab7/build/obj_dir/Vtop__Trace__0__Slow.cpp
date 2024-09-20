// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBus(c+29,"din", false,-1, 7,0);
    tracep->declBus(c+30,"shamt", false,-1, 2,0);
    tracep->declBit(c+31,"LR", false,-1);
    tracep->declBit(c+32,"AL", false,-1);
    tracep->declBus(c+33,"dout", false,-1, 7,0);
    tracep->pushNamePrefix("top ");
    tracep->declBus(c+29,"din", false,-1, 7,0);
    tracep->declBus(c+30,"shamt", false,-1, 2,0);
    tracep->declBit(c+31,"LR", false,-1);
    tracep->declBit(c+32,"AL", false,-1);
    tracep->declBus(c+33,"dout", false,-1, 7,0);
    tracep->declBit(c+1,"w0", false,-1);
    tracep->declBit(c+2,"w1", false,-1);
    tracep->declBit(c+3,"w2", false,-1);
    tracep->declBit(c+4,"w3", false,-1);
    tracep->declBit(c+5,"w4", false,-1);
    tracep->declBit(c+6,"w5", false,-1);
    tracep->declBit(c+7,"w6", false,-1);
    tracep->declBit(c+8,"w7", false,-1);
    tracep->declBit(c+9,"w8", false,-1);
    tracep->declBit(c+10,"w9", false,-1);
    tracep->declBit(c+11,"w10", false,-1);
    tracep->declBit(c+12,"w11", false,-1);
    tracep->declBit(c+13,"w12", false,-1);
    tracep->declBit(c+14,"w13", false,-1);
    tracep->declBit(c+15,"w14", false,-1);
    tracep->declBit(c+16,"w15", false,-1);
    tracep->declBit(c+17,"w16", false,-1);
    tracep->pushNamePrefix("u_0_1 ");
    tracep->declBit(c+32,"sel", false,-1);
    tracep->declBit(c+42,"x0", false,-1);
    tracep->declBit(c+34,"x1", false,-1);
    tracep->declBit(c+1,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_1_1 ");
    tracep->declBus(c+18,"sel", false,-1, 1,0);
    tracep->declBit(c+34,"x0", false,-1);
    tracep->declBit(c+1,"x1", false,-1);
    tracep->declBit(c+34,"x2", false,-1);
    tracep->declBit(c+35,"x3", false,-1);
    tracep->declBit(c+2,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_1_2 ");
    tracep->declBus(c+19,"sel", false,-1, 1,0);
    tracep->declBit(c+2,"x0", false,-1);
    tracep->declBit(c+1,"x1", false,-1);
    tracep->declBit(c+2,"x2", false,-1);
    tracep->declBit(c+4,"x3", false,-1);
    tracep->declBit(c+10,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_1_3 ");
    tracep->declBus(c+20,"sel", false,-1, 1,0);
    tracep->declBit(c+10,"x0", false,-1);
    tracep->declBit(c+1,"x1", false,-1);
    tracep->declBit(c+10,"x2", false,-1);
    tracep->declBit(c+14,"x3", false,-1);
    tracep->declBit(c+21,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_2_1 ");
    tracep->declBus(c+18,"sel", false,-1, 1,0);
    tracep->declBit(c+35,"x0", false,-1);
    tracep->declBit(c+34,"x1", false,-1);
    tracep->declBit(c+35,"x2", false,-1);
    tracep->declBit(c+36,"x3", false,-1);
    tracep->declBit(c+3,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_2_2 ");
    tracep->declBus(c+19,"sel", false,-1, 1,0);
    tracep->declBit(c+3,"x0", false,-1);
    tracep->declBit(c+1,"x1", false,-1);
    tracep->declBit(c+3,"x2", false,-1);
    tracep->declBit(c+5,"x3", false,-1);
    tracep->declBit(c+11,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_2_3 ");
    tracep->declBus(c+20,"sel", false,-1, 1,0);
    tracep->declBit(c+11,"x0", false,-1);
    tracep->declBit(c+1,"x1", false,-1);
    tracep->declBit(c+11,"x2", false,-1);
    tracep->declBit(c+15,"x3", false,-1);
    tracep->declBit(c+22,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_3_1 ");
    tracep->declBus(c+18,"sel", false,-1, 1,0);
    tracep->declBit(c+36,"x0", false,-1);
    tracep->declBit(c+35,"x1", false,-1);
    tracep->declBit(c+36,"x2", false,-1);
    tracep->declBit(c+37,"x3", false,-1);
    tracep->declBit(c+4,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_3_2 ");
    tracep->declBus(c+19,"sel", false,-1, 1,0);
    tracep->declBit(c+4,"x0", false,-1);
    tracep->declBit(c+2,"x1", false,-1);
    tracep->declBit(c+4,"x2", false,-1);
    tracep->declBit(c+6,"x3", false,-1);
    tracep->declBit(c+12,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_3_3 ");
    tracep->declBus(c+20,"sel", false,-1, 1,0);
    tracep->declBit(c+12,"x0", false,-1);
    tracep->declBit(c+1,"x1", false,-1);
    tracep->declBit(c+12,"x2", false,-1);
    tracep->declBit(c+16,"x3", false,-1);
    tracep->declBit(c+23,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_4_1 ");
    tracep->declBus(c+18,"sel", false,-1, 1,0);
    tracep->declBit(c+37,"x0", false,-1);
    tracep->declBit(c+36,"x1", false,-1);
    tracep->declBit(c+37,"x2", false,-1);
    tracep->declBit(c+38,"x3", false,-1);
    tracep->declBit(c+5,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_4_2 ");
    tracep->declBus(c+19,"sel", false,-1, 1,0);
    tracep->declBit(c+5,"x0", false,-1);
    tracep->declBit(c+3,"x1", false,-1);
    tracep->declBit(c+5,"x2", false,-1);
    tracep->declBit(c+7,"x3", false,-1);
    tracep->declBit(c+13,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_4_3 ");
    tracep->declBus(c+20,"sel", false,-1, 1,0);
    tracep->declBit(c+13,"x0", false,-1);
    tracep->declBit(c+1,"x1", false,-1);
    tracep->declBit(c+13,"x2", false,-1);
    tracep->declBit(c+17,"x3", false,-1);
    tracep->declBit(c+24,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_5_1 ");
    tracep->declBus(c+18,"sel", false,-1, 1,0);
    tracep->declBit(c+38,"x0", false,-1);
    tracep->declBit(c+37,"x1", false,-1);
    tracep->declBit(c+38,"x2", false,-1);
    tracep->declBit(c+39,"x3", false,-1);
    tracep->declBit(c+6,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_5_2 ");
    tracep->declBus(c+19,"sel", false,-1, 1,0);
    tracep->declBit(c+6,"x0", false,-1);
    tracep->declBit(c+4,"x1", false,-1);
    tracep->declBit(c+6,"x2", false,-1);
    tracep->declBit(c+8,"x3", false,-1);
    tracep->declBit(c+14,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_5_3 ");
    tracep->declBus(c+20,"sel", false,-1, 1,0);
    tracep->declBit(c+14,"x0", false,-1);
    tracep->declBit(c+10,"x1", false,-1);
    tracep->declBit(c+14,"x2", false,-1);
    tracep->declBit(c+42,"x3", false,-1);
    tracep->declBit(c+25,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_6_1 ");
    tracep->declBus(c+18,"sel", false,-1, 1,0);
    tracep->declBit(c+39,"x0", false,-1);
    tracep->declBit(c+38,"x1", false,-1);
    tracep->declBit(c+39,"x2", false,-1);
    tracep->declBit(c+40,"x3", false,-1);
    tracep->declBit(c+7,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_6_2 ");
    tracep->declBus(c+19,"sel", false,-1, 1,0);
    tracep->declBit(c+7,"x0", false,-1);
    tracep->declBit(c+5,"x1", false,-1);
    tracep->declBit(c+7,"x2", false,-1);
    tracep->declBit(c+9,"x3", false,-1);
    tracep->declBit(c+15,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_6_3 ");
    tracep->declBus(c+20,"sel", false,-1, 1,0);
    tracep->declBit(c+15,"x0", false,-1);
    tracep->declBit(c+11,"x1", false,-1);
    tracep->declBit(c+15,"x2", false,-1);
    tracep->declBit(c+42,"x3", false,-1);
    tracep->declBit(c+26,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_7_1 ");
    tracep->declBus(c+18,"sel", false,-1, 1,0);
    tracep->declBit(c+40,"x0", false,-1);
    tracep->declBit(c+39,"x1", false,-1);
    tracep->declBit(c+40,"x2", false,-1);
    tracep->declBit(c+41,"x3", false,-1);
    tracep->declBit(c+8,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_7_2 ");
    tracep->declBus(c+19,"sel", false,-1, 1,0);
    tracep->declBit(c+8,"x0", false,-1);
    tracep->declBit(c+6,"x1", false,-1);
    tracep->declBit(c+8,"x2", false,-1);
    tracep->declBit(c+42,"x3", false,-1);
    tracep->declBit(c+16,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_7_3 ");
    tracep->declBus(c+20,"sel", false,-1, 1,0);
    tracep->declBit(c+16,"x0", false,-1);
    tracep->declBit(c+12,"x1", false,-1);
    tracep->declBit(c+16,"x2", false,-1);
    tracep->declBit(c+42,"x3", false,-1);
    tracep->declBit(c+27,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_8_1 ");
    tracep->declBus(c+18,"sel", false,-1, 1,0);
    tracep->declBit(c+41,"x0", false,-1);
    tracep->declBit(c+40,"x1", false,-1);
    tracep->declBit(c+41,"x2", false,-1);
    tracep->declBit(c+42,"x3", false,-1);
    tracep->declBit(c+9,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_8_2 ");
    tracep->declBus(c+19,"sel", false,-1, 1,0);
    tracep->declBit(c+9,"x0", false,-1);
    tracep->declBit(c+7,"x1", false,-1);
    tracep->declBit(c+9,"x2", false,-1);
    tracep->declBit(c+42,"x3", false,-1);
    tracep->declBit(c+17,"f", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_8_3 ");
    tracep->declBus(c+20,"sel", false,-1, 1,0);
    tracep->declBit(c+17,"x0", false,-1);
    tracep->declBit(c+13,"x1", false,-1);
    tracep->declBit(c+17,"x2", false,-1);
    tracep->declBit(c+42,"x3", false,-1);
    tracep->declBit(c+28,"f", false,-1);
    tracep->popNamePrefix(2);
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vtop___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullBit(oldp+1,(vlSelf->top__DOT__w0));
    bufp->fullBit(oldp+2,(vlSelf->top__DOT__w1));
    bufp->fullBit(oldp+3,(vlSelf->top__DOT__w2));
    bufp->fullBit(oldp+4,(vlSelf->top__DOT__w3));
    bufp->fullBit(oldp+5,(vlSelf->top__DOT__w4));
    bufp->fullBit(oldp+6,(vlSelf->top__DOT__w5));
    bufp->fullBit(oldp+7,(vlSelf->top__DOT__w6));
    bufp->fullBit(oldp+8,(vlSelf->top__DOT__w7));
    bufp->fullBit(oldp+9,(vlSelf->top__DOT__w8));
    bufp->fullBit(oldp+10,(vlSelf->top__DOT__w9));
    bufp->fullBit(oldp+11,(vlSelf->top__DOT__w10));
    bufp->fullBit(oldp+12,(vlSelf->top__DOT__w11));
    bufp->fullBit(oldp+13,(vlSelf->top__DOT__w12));
    bufp->fullBit(oldp+14,(vlSelf->top__DOT__w13));
    bufp->fullBit(oldp+15,(vlSelf->top__DOT__w14));
    bufp->fullBit(oldp+16,(vlSelf->top__DOT__w15));
    bufp->fullBit(oldp+17,(vlSelf->top__DOT__w16));
    bufp->fullCData(oldp+18,(vlSelf->top__DOT____Vcellinp__u_1_1__sel),2);
    bufp->fullCData(oldp+19,(vlSelf->top__DOT____Vcellinp__u_1_2__sel),2);
    bufp->fullCData(oldp+20,(vlSelf->top__DOT____Vcellinp__u_1_3__sel),2);
    bufp->fullBit(oldp+21,(((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                             ? ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                 ? (IData)(vlSelf->top__DOT__w13)
                                 : (IData)(vlSelf->top__DOT__w9))
                             : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                 ? (IData)(vlSelf->top__DOT__w0)
                                 : (IData)(vlSelf->top__DOT__w9)))));
    bufp->fullBit(oldp+22,(((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                             ? ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                 ? (IData)(vlSelf->top__DOT__w14)
                                 : (IData)(vlSelf->top__DOT__w10))
                             : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                 ? (IData)(vlSelf->top__DOT__w0)
                                 : (IData)(vlSelf->top__DOT__w10)))));
    bufp->fullBit(oldp+23,(((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                             ? ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                 ? (IData)(vlSelf->top__DOT__w15)
                                 : (IData)(vlSelf->top__DOT__w11))
                             : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                 ? (IData)(vlSelf->top__DOT__w0)
                                 : (IData)(vlSelf->top__DOT__w11)))));
    bufp->fullBit(oldp+24,(((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                             ? ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                 ? (IData)(vlSelf->top__DOT__w16)
                                 : (IData)(vlSelf->top__DOT__w12))
                             : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                 ? (IData)(vlSelf->top__DOT__w0)
                                 : (IData)(vlSelf->top__DOT__w12)))));
    bufp->fullBit(oldp+25,(((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                             ? ((~ (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel)) 
                                & (IData)(vlSelf->top__DOT__w13))
                             : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                 ? (IData)(vlSelf->top__DOT__w9)
                                 : (IData)(vlSelf->top__DOT__w13)))));
    bufp->fullBit(oldp+26,(((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                             ? ((~ (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel)) 
                                & (IData)(vlSelf->top__DOT__w14))
                             : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                 ? (IData)(vlSelf->top__DOT__w10)
                                 : (IData)(vlSelf->top__DOT__w14)))));
    bufp->fullBit(oldp+27,(((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                             ? ((~ (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel)) 
                                & (IData)(vlSelf->top__DOT__w15))
                             : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                 ? (IData)(vlSelf->top__DOT__w11)
                                 : (IData)(vlSelf->top__DOT__w15)))));
    bufp->fullBit(oldp+28,(((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                             ? ((~ (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel)) 
                                & (IData)(vlSelf->top__DOT__w16))
                             : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                 ? (IData)(vlSelf->top__DOT__w12)
                                 : (IData)(vlSelf->top__DOT__w16)))));
    bufp->fullCData(oldp+29,(vlSelf->din),8);
    bufp->fullCData(oldp+30,(vlSelf->shamt),3);
    bufp->fullBit(oldp+31,(vlSelf->LR));
    bufp->fullBit(oldp+32,(vlSelf->AL));
    bufp->fullCData(oldp+33,(vlSelf->dout),8);
    bufp->fullBit(oldp+34,((1U & ((IData)(vlSelf->din) 
                                  >> 7U))));
    bufp->fullBit(oldp+35,((1U & ((IData)(vlSelf->din) 
                                  >> 6U))));
    bufp->fullBit(oldp+36,((1U & ((IData)(vlSelf->din) 
                                  >> 5U))));
    bufp->fullBit(oldp+37,((1U & ((IData)(vlSelf->din) 
                                  >> 4U))));
    bufp->fullBit(oldp+38,((1U & ((IData)(vlSelf->din) 
                                  >> 3U))));
    bufp->fullBit(oldp+39,((1U & ((IData)(vlSelf->din) 
                                  >> 2U))));
    bufp->fullBit(oldp+40,((1U & ((IData)(vlSelf->din) 
                                  >> 1U))));
    bufp->fullBit(oldp+41,((1U & (IData)(vlSelf->din))));
    bufp->fullBit(oldp+42,(0U));
}
