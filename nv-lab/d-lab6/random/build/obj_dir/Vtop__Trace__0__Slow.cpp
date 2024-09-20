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
    tracep->declBit(c+5,"clk", false,-1);
    tracep->declBit(c+6,"rst_n", false,-1);
    tracep->declBus(c+7,"seg1", false,-1, 6,0);
    tracep->declBus(c+8,"seg2", false,-1, 6,0);
    tracep->pushNamePrefix("top ");
    tracep->declBit(c+5,"clk", false,-1);
    tracep->declBit(c+6,"rst_n", false,-1);
    tracep->declBus(c+7,"seg1", false,-1, 6,0);
    tracep->declBus(c+8,"seg2", false,-1, 6,0);
    tracep->declBus(c+1,"random_num", false,-1, 7,0);
    tracep->pushNamePrefix("display1 ");
    tracep->declBus(c+2,"hex", false,-1, 3,0);
    tracep->declBus(c+7,"seg", false,-1, 6,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("display2 ");
    tracep->declBus(c+3,"hex", false,-1, 3,0);
    tracep->declBus(c+8,"seg", false,-1, 6,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("lfsr_inst ");
    tracep->declBit(c+5,"clk", false,-1);
    tracep->declBit(c+6,"rst_n", false,-1);
    tracep->declBus(c+1,"random", false,-1, 7,0);
    tracep->declBit(c+4,"feedback", false,-1);
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
    bufp->fullCData(oldp+1,(vlSelf->top__DOT__random_num),8);
    bufp->fullCData(oldp+2,((0xfU & ((IData)(vlSelf->top__DOT__random_num) 
                                     >> 4U))),4);
    bufp->fullCData(oldp+3,((0xfU & (IData)(vlSelf->top__DOT__random_num))),4);
    bufp->fullBit(oldp+4,((1U & VL_REDXOR_8((0x1dU 
                                             & (IData)(vlSelf->top__DOT__random_num))))));
    bufp->fullBit(oldp+5,(vlSelf->clk));
    bufp->fullBit(oldp+6,(vlSelf->rst_n));
    bufp->fullCData(oldp+7,(vlSelf->seg1),7);
    bufp->fullCData(oldp+8,(vlSelf->seg2),7);
}
