// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

VL_INLINE_OPT void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    // Body
    vlSelf->top__DOT____Vcellinp__u_1_3__sel = (((IData)(vlSelf->LR) 
                                                 << 1U) 
                                                | (1U 
                                                   & ((IData)(vlSelf->shamt) 
                                                      >> 2U)));
    vlSelf->top__DOT__w0 = ((IData)(vlSelf->AL) & ((IData)(vlSelf->din) 
                                                   >> 7U));
    vlSelf->top__DOT____Vcellinp__u_1_2__sel = (((IData)(vlSelf->LR) 
                                                 << 1U) 
                                                | (1U 
                                                   & ((IData)(vlSelf->shamt) 
                                                      >> 1U)));
    vlSelf->top__DOT____Vcellinp__u_1_1__sel = (((IData)(vlSelf->LR) 
                                                 << 1U) 
                                                | (1U 
                                                   & (IData)(vlSelf->shamt)));
    if ((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_1__sel))) {
        if ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_1__sel))) {
            vlSelf->top__DOT__w7 = (1U & (IData)(vlSelf->din));
            vlSelf->top__DOT__w2 = (1U & ((IData)(vlSelf->din) 
                                          >> 5U));
            vlSelf->top__DOT__w1 = (1U & ((IData)(vlSelf->din) 
                                          >> 6U));
            vlSelf->top__DOT__w5 = (1U & ((IData)(vlSelf->din) 
                                          >> 2U));
            vlSelf->top__DOT__w6 = (1U & ((IData)(vlSelf->din) 
                                          >> 1U));
            vlSelf->top__DOT__w3 = (1U & ((IData)(vlSelf->din) 
                                          >> 4U));
            vlSelf->top__DOT__w4 = (1U & ((IData)(vlSelf->din) 
                                          >> 3U));
        } else {
            vlSelf->top__DOT__w7 = (1U & ((IData)(vlSelf->din) 
                                          >> 1U));
            vlSelf->top__DOT__w2 = (1U & ((IData)(vlSelf->din) 
                                          >> 6U));
            vlSelf->top__DOT__w1 = (1U & ((IData)(vlSelf->din) 
                                          >> 7U));
            vlSelf->top__DOT__w5 = (1U & ((IData)(vlSelf->din) 
                                          >> 3U));
            vlSelf->top__DOT__w6 = (1U & ((IData)(vlSelf->din) 
                                          >> 2U));
            vlSelf->top__DOT__w3 = (1U & ((IData)(vlSelf->din) 
                                          >> 5U));
            vlSelf->top__DOT__w4 = (1U & ((IData)(vlSelf->din) 
                                          >> 4U));
        }
        vlSelf->top__DOT__w8 = (1U & ((~ (IData)(vlSelf->top__DOT____Vcellinp__u_1_1__sel)) 
                                      & (IData)(vlSelf->din)));
    } else if ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_1__sel))) {
        vlSelf->top__DOT__w7 = (1U & ((IData)(vlSelf->din) 
                                      >> 2U));
        vlSelf->top__DOT__w8 = (1U & ((IData)(vlSelf->din) 
                                      >> 1U));
        vlSelf->top__DOT__w2 = (1U & ((IData)(vlSelf->din) 
                                      >> 7U));
        vlSelf->top__DOT__w1 = (1U & (IData)(vlSelf->top__DOT__w0));
        vlSelf->top__DOT__w5 = (1U & ((IData)(vlSelf->din) 
                                      >> 4U));
        vlSelf->top__DOT__w6 = (1U & ((IData)(vlSelf->din) 
                                      >> 3U));
        vlSelf->top__DOT__w3 = (1U & ((IData)(vlSelf->din) 
                                      >> 6U));
        vlSelf->top__DOT__w4 = (1U & ((IData)(vlSelf->din) 
                                      >> 5U));
    } else {
        vlSelf->top__DOT__w7 = (1U & ((IData)(vlSelf->din) 
                                      >> 1U));
        vlSelf->top__DOT__w8 = (1U & (IData)(vlSelf->din));
        vlSelf->top__DOT__w2 = (1U & ((IData)(vlSelf->din) 
                                      >> 6U));
        vlSelf->top__DOT__w1 = (1U & ((IData)(vlSelf->din) 
                                      >> 7U));
        vlSelf->top__DOT__w5 = (1U & ((IData)(vlSelf->din) 
                                      >> 3U));
        vlSelf->top__DOT__w6 = (1U & ((IData)(vlSelf->din) 
                                      >> 2U));
        vlSelf->top__DOT__w3 = (1U & ((IData)(vlSelf->din) 
                                      >> 5U));
        vlSelf->top__DOT__w4 = (1U & ((IData)(vlSelf->din) 
                                      >> 4U));
    }
    if ((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_2__sel))) {
        vlSelf->top__DOT__w15 = ((~ (IData)(vlSelf->top__DOT____Vcellinp__u_1_2__sel)) 
                                 & (IData)(vlSelf->top__DOT__w7));
        vlSelf->top__DOT__w16 = ((~ (IData)(vlSelf->top__DOT____Vcellinp__u_1_2__sel)) 
                                 & (IData)(vlSelf->top__DOT__w8));
        if ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_2__sel))) {
            vlSelf->top__DOT__w9 = vlSelf->top__DOT__w3;
            vlSelf->top__DOT__w11 = vlSelf->top__DOT__w5;
            vlSelf->top__DOT__w13 = vlSelf->top__DOT__w7;
            vlSelf->top__DOT__w10 = vlSelf->top__DOT__w4;
            vlSelf->top__DOT__w12 = vlSelf->top__DOT__w6;
            vlSelf->top__DOT__w14 = vlSelf->top__DOT__w8;
        } else {
            vlSelf->top__DOT__w9 = vlSelf->top__DOT__w1;
            vlSelf->top__DOT__w11 = vlSelf->top__DOT__w3;
            vlSelf->top__DOT__w13 = vlSelf->top__DOT__w5;
            vlSelf->top__DOT__w10 = vlSelf->top__DOT__w2;
            vlSelf->top__DOT__w12 = vlSelf->top__DOT__w4;
            vlSelf->top__DOT__w14 = vlSelf->top__DOT__w6;
        }
    } else if ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_2__sel))) {
        vlSelf->top__DOT__w15 = vlSelf->top__DOT__w5;
        vlSelf->top__DOT__w16 = vlSelf->top__DOT__w6;
        vlSelf->top__DOT__w9 = vlSelf->top__DOT__w0;
        vlSelf->top__DOT__w11 = vlSelf->top__DOT__w1;
        vlSelf->top__DOT__w13 = vlSelf->top__DOT__w3;
        vlSelf->top__DOT__w10 = vlSelf->top__DOT__w0;
        vlSelf->top__DOT__w12 = vlSelf->top__DOT__w2;
        vlSelf->top__DOT__w14 = vlSelf->top__DOT__w4;
    } else {
        vlSelf->top__DOT__w15 = vlSelf->top__DOT__w7;
        vlSelf->top__DOT__w16 = vlSelf->top__DOT__w8;
        vlSelf->top__DOT__w9 = vlSelf->top__DOT__w1;
        vlSelf->top__DOT__w11 = vlSelf->top__DOT__w3;
        vlSelf->top__DOT__w13 = vlSelf->top__DOT__w5;
        vlSelf->top__DOT__w10 = vlSelf->top__DOT__w2;
        vlSelf->top__DOT__w12 = vlSelf->top__DOT__w4;
        vlSelf->top__DOT__w14 = vlSelf->top__DOT__w6;
    }
    vlSelf->dout = ((((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                       ? ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                           ? (IData)(vlSelf->top__DOT__w13)
                           : (IData)(vlSelf->top__DOT__w9))
                       : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                           ? (IData)(vlSelf->top__DOT__w0)
                           : (IData)(vlSelf->top__DOT__w9))) 
                     << 7U) | ((((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                  ? ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                      ? (IData)(vlSelf->top__DOT__w14)
                                      : (IData)(vlSelf->top__DOT__w10))
                                  : ((1U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                      ? (IData)(vlSelf->top__DOT__w0)
                                      : (IData)(vlSelf->top__DOT__w10))) 
                                << 6U) | ((((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                             ? ((1U 
                                                 & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                                 ? (IData)(vlSelf->top__DOT__w15)
                                                 : (IData)(vlSelf->top__DOT__w11))
                                             : ((1U 
                                                 & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                                 ? (IData)(vlSelf->top__DOT__w0)
                                                 : (IData)(vlSelf->top__DOT__w11))) 
                                           << 5U) | 
                                          ((((2U & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                              ? ((1U 
                                                  & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                                  ? (IData)(vlSelf->top__DOT__w16)
                                                  : (IData)(vlSelf->top__DOT__w12))
                                              : ((1U 
                                                  & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                                  ? (IData)(vlSelf->top__DOT__w0)
                                                  : (IData)(vlSelf->top__DOT__w12))) 
                                            << 4U) 
                                           | ((((2U 
                                                 & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                                 ? 
                                                ((~ (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel)) 
                                                 & (IData)(vlSelf->top__DOT__w13))
                                                 : 
                                                ((1U 
                                                  & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                                  ? (IData)(vlSelf->top__DOT__w9)
                                                  : (IData)(vlSelf->top__DOT__w13))) 
                                               << 3U) 
                                              | ((((2U 
                                                    & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                                    ? 
                                                   ((~ (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel)) 
                                                    & (IData)(vlSelf->top__DOT__w14))
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                                     ? (IData)(vlSelf->top__DOT__w10)
                                                     : (IData)(vlSelf->top__DOT__w14))) 
                                                  << 2U) 
                                                 | ((((2U 
                                                       & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                                       ? 
                                                      ((~ (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel)) 
                                                       & (IData)(vlSelf->top__DOT__w15))
                                                       : 
                                                      ((1U 
                                                        & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                                        ? (IData)(vlSelf->top__DOT__w11)
                                                        : (IData)(vlSelf->top__DOT__w15))) 
                                                     << 1U) 
                                                    | ((2U 
                                                        & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                                        ? 
                                                       ((~ (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel)) 
                                                        & (IData)(vlSelf->top__DOT__w16))
                                                        : 
                                                       ((1U 
                                                         & (IData)(vlSelf->top__DOT____Vcellinp__u_1_3__sel))
                                                         ? (IData)(vlSelf->top__DOT__w12)
                                                         : (IData)(vlSelf->top__DOT__w16))))))))));
}

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    // Body
    if (vlSelf->__VicoTriggered.at(0U)) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
}

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
}

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
}

void Vtop___024root___eval_triggers__ico(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Init
    CData/*0:0*/ __VicoContinue;
    VlTriggerVec<0> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    vlSelf->__VicoIterCount = 0U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        __VicoContinue = 0U;
        Vtop___024root___eval_triggers__ico(vlSelf);
        if (vlSelf->__VicoTriggered.any()) {
            __VicoContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VicoIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__ico(vlSelf);
#endif
                VL_FATAL_MT("/home/icse/Desktop/nv-lab/d-lab7/vsrc/top.v", 1, "", "Input combinational region did not converge.");
            }
            vlSelf->__VicoIterCount = ((IData)(1U) 
                                       + vlSelf->__VicoIterCount);
            Vtop___024root___eval_ico(vlSelf);
        }
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        __VnbaContinue = 0U;
        vlSelf->__VnbaTriggered.clear();
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            vlSelf->__VactContinue = 0U;
            Vtop___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    Vtop___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("/home/icse/Desktop/nv-lab/d-lab7/vsrc/top.v", 1, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                Vtop___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("/home/icse/Desktop/nv-lab/d-lab7/vsrc/top.v", 1, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            Vtop___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->shamt & 0xf8U))) {
        Verilated::overWidthError("shamt");}
    if (VL_UNLIKELY((vlSelf->LR & 0xfeU))) {
        Verilated::overWidthError("LR");}
    if (VL_UNLIKELY((vlSelf->AL & 0xfeU))) {
        Verilated::overWidthError("AL");}
}
#endif  // VL_DEBUG
