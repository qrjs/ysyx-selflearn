// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"

class Vtop__Syms;

class Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(din,7,0);
    VL_IN8(shamt,2,0);
    VL_IN8(LR,0,0);
    VL_IN8(AL,0,0);
    VL_OUT8(dout,7,0);
    CData/*0:0*/ top__DOT__w0;
    CData/*0:0*/ top__DOT__w1;
    CData/*0:0*/ top__DOT__w2;
    CData/*0:0*/ top__DOT__w3;
    CData/*0:0*/ top__DOT__w4;
    CData/*0:0*/ top__DOT__w5;
    CData/*0:0*/ top__DOT__w6;
    CData/*0:0*/ top__DOT__w7;
    CData/*0:0*/ top__DOT__w8;
    CData/*0:0*/ top__DOT__w9;
    CData/*0:0*/ top__DOT__w10;
    CData/*0:0*/ top__DOT__w11;
    CData/*0:0*/ top__DOT__w12;
    CData/*0:0*/ top__DOT__w13;
    CData/*0:0*/ top__DOT__w14;
    CData/*0:0*/ top__DOT__w15;
    CData/*0:0*/ top__DOT__w16;
    CData/*1:0*/ top__DOT____Vcellinp__u_1_1__sel;
    CData/*1:0*/ top__DOT____Vcellinp__u_1_2__sel;
    CData/*1:0*/ top__DOT____Vcellinp__u_1_3__sel;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VstlIterCount;
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<0> __VactTriggered;
    VlTriggerVec<0> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
