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
    vlSelf->alu_f = 0U;
    vlSelf->temp = 0U;
    vlSelf->over_f = 0U;
    vlSelf->zero_f = 0U;
    vlSelf->cout_f = 0U;
    vlSelf->top__DOT__xb = 0U;
    if ((4U & (IData)(vlSelf->alu_ch))) {
        if ((2U & (IData)(vlSelf->alu_ch))) {
            if ((1U & (IData)(vlSelf->alu_ch))) {
                vlSelf->top__DOT__xb = (0xfU & (~ (IData)(vlSelf->b)));
                vlSelf->cout_f = (1U & (((IData)(1U) 
                                         + ((IData)(vlSelf->top__DOT__xb) 
                                            + (IData)(vlSelf->a))) 
                                        >> 4U));
                vlSelf->temp = (0xfU & ((IData)(1U) 
                                        + ((IData)(vlSelf->top__DOT__xb) 
                                           + (IData)(vlSelf->a))));
                vlSelf->over_f = (((1U & ((IData)(vlSelf->a) 
                                          >> 3U)) == 
                                   (1U & ((IData)(vlSelf->top__DOT__xb) 
                                          >> 3U))) 
                                  & ((1U & ((IData)(vlSelf->temp) 
                                            >> 3U)) 
                                     != (1U & ((IData)(vlSelf->a) 
                                               >> 3U))));
                vlSelf->zero_f = (1U & (~ (IData)((0U 
                                                   != (IData)(vlSelf->temp)))));
                vlSelf->alu_f = ((IData)(vlSelf->zero_f)
                                  ? 1U : 0U);
            } else {
                vlSelf->top__DOT__xb = (0xfU & (~ (IData)(vlSelf->b)));
                vlSelf->cout_f = (1U & (((IData)(1U) 
                                         + ((IData)(vlSelf->top__DOT__xb) 
                                            + (IData)(vlSelf->a))) 
                                        >> 4U));
                vlSelf->alu_f = (((1U & ((IData)(vlSelf->a) 
                                         >> 3U)) != 
                                  (1U & ((IData)(vlSelf->b) 
                                         >> 3U))) ? 
                                 (1U & ((IData)(vlSelf->a) 
                                        >> 3U)) : ((IData)(vlSelf->a) 
                                                   < (IData)(vlSelf->b)));
                vlSelf->temp = (0xfU & ((IData)(1U) 
                                        + ((IData)(vlSelf->top__DOT__xb) 
                                           + (IData)(vlSelf->a))));
                vlSelf->over_f = (((1U & ((IData)(vlSelf->a) 
                                          >> 3U)) == 
                                   (1U & ((IData)(vlSelf->top__DOT__xb) 
                                          >> 3U))) 
                                  & ((1U & ((IData)(vlSelf->temp) 
                                            >> 3U)) 
                                     != (1U & ((IData)(vlSelf->a) 
                                               >> 3U))));
                vlSelf->zero_f = (1U & (~ (IData)((0U 
                                                   != (IData)(vlSelf->temp)))));
            }
        } else {
            vlSelf->alu_f = ((1U & (IData)(vlSelf->alu_ch))
                              ? ((IData)(vlSelf->a) 
                                 ^ (IData)(vlSelf->b))
                              : ((IData)(vlSelf->a) 
                                 | (IData)(vlSelf->b)));
        }
    } else if ((2U & (IData)(vlSelf->alu_ch))) {
        vlSelf->alu_f = ((1U & (IData)(vlSelf->alu_ch))
                          ? ((IData)(vlSelf->a) & (IData)(vlSelf->b))
                          : 0U);
    } else {
        vlSelf->top__DOT__xb = (0xfU & ((IData)(vlSelf->b) 
                                        ^ (- (IData)(
                                                     (1U 
                                                      & (IData)(vlSelf->alu_ch))))));
        vlSelf->cout_f = (1U & ((((IData)(vlSelf->top__DOT__xb) 
                                  + (IData)(vlSelf->a)) 
                                 + (1U & (IData)(vlSelf->alu_ch))) 
                                >> 4U));
        vlSelf->alu_f = (0xfU & (((IData)(vlSelf->top__DOT__xb) 
                                  + (IData)(vlSelf->a)) 
                                 + (1U & (IData)(vlSelf->alu_ch))));
        vlSelf->over_f = (((1U & ((IData)(vlSelf->a) 
                                  >> 3U)) == (1U & 
                                              ((IData)(vlSelf->top__DOT__xb) 
                                               >> 3U))) 
                          & ((1U & ((IData)(vlSelf->a) 
                                    >> 3U)) != (1U 
                                                & ((IData)(vlSelf->alu_f) 
                                                   >> 3U))));
        vlSelf->zero_f = (1U & (~ (IData)((0U != (IData)(vlSelf->alu_f)))));
    }
}

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    // Body
    if (vlSelf->__VicoTriggered.at(0U)) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
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
                VL_FATAL_MT("/home/icse/Desktop/nv-lab/d-lab3/vsrc/top.v", 1, "", "Input combinational region did not converge.");
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
                    VL_FATAL_MT("/home/icse/Desktop/nv-lab/d-lab3/vsrc/top.v", 1, "", "Active region did not converge.");
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
                VL_FATAL_MT("/home/icse/Desktop/nv-lab/d-lab3/vsrc/top.v", 1, "", "NBA region did not converge.");
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
    if (VL_UNLIKELY((vlSelf->a & 0xf0U))) {
        Verilated::overWidthError("a");}
    if (VL_UNLIKELY((vlSelf->b & 0xf0U))) {
        Verilated::overWidthError("b");}
    if (VL_UNLIKELY((vlSelf->alu_ch & 0xf8U))) {
        Verilated::overWidthError("alu_ch");}
}
#endif  // VL_DEBUG
