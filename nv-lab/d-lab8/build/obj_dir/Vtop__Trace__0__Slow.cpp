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
    tracep->declBit(c+33,"clk", false,-1);
    tracep->declBit(c+34,"clrn", false,-1);
    tracep->declBit(c+35,"ps2_clk", false,-1);
    tracep->declBit(c+36,"ps2_data", false,-1);
    tracep->declBus(c+37,"seg0", false,-1, 7,0);
    tracep->declBus(c+38,"seg1", false,-1, 7,0);
    tracep->declBus(c+39,"seg2", false,-1, 7,0);
    tracep->declBus(c+40,"seg3", false,-1, 7,0);
    tracep->declBus(c+41,"seg4", false,-1, 7,0);
    tracep->declBus(c+42,"seg5", false,-1, 7,0);
    tracep->declBus(c+43,"seg6", false,-1, 7,0);
    tracep->declBus(c+44,"seg7", false,-1, 7,0);
    tracep->pushNamePrefix("top ");
    tracep->declBit(c+33,"clk", false,-1);
    tracep->declBit(c+34,"clrn", false,-1);
    tracep->declBit(c+35,"ps2_clk", false,-1);
    tracep->declBit(c+36,"ps2_data", false,-1);
    tracep->declBus(c+37,"seg0", false,-1, 7,0);
    tracep->declBus(c+38,"seg1", false,-1, 7,0);
    tracep->declBus(c+39,"seg2", false,-1, 7,0);
    tracep->declBus(c+40,"seg3", false,-1, 7,0);
    tracep->declBus(c+41,"seg4", false,-1, 7,0);
    tracep->declBus(c+42,"seg5", false,-1, 7,0);
    tracep->declBus(c+43,"seg6", false,-1, 7,0);
    tracep->declBus(c+44,"seg7", false,-1, 7,0);
    tracep->declBit(c+48,"nextdata_n", false,-1);
    tracep->declBit(c+1,"ready", false,-1);
    tracep->declBit(c+2,"overflow", false,-1);
    tracep->declBus(c+45,"data", false,-1, 7,0);
    tracep->declBus(c+3,"tmp_data", false,-1, 7,0);
    tracep->declBus(c+4,"out_data", false,-1, 7,0);
    tracep->declBus(c+5,"key_count", false,-1, 7,0);
    tracep->declBus(c+25,"ascii", false,-1, 7,0);
    tracep->declBus(c+26,"tmp_seg0", false,-1, 7,0);
    tracep->declBus(c+27,"tmp_seg1", false,-1, 7,0);
    tracep->declBus(c+28,"tmp_seg2", false,-1, 7,0);
    tracep->declBus(c+29,"tmp_seg3", false,-1, 7,0);
    tracep->declBus(c+49,"a", false,-1, 3,0);
    tracep->declBus(c+50,"b", false,-1, 3,0);
    tracep->declBus(c+51,"c", false,-1, 3,0);
    tracep->declBus(c+52,"d", false,-1, 3,0);
    tracep->declBus(c+22,"state", false,-1, 3,0);
    tracep->declBus(c+30,"next_state", false,-1, 3,0);
    tracep->pushNamePrefix("my_keyboard ");
    tracep->declBit(c+33,"clk", false,-1);
    tracep->declBit(c+34,"clrn", false,-1);
    tracep->declBit(c+35,"ps2_clk", false,-1);
    tracep->declBit(c+36,"ps2_data", false,-1);
    tracep->declBit(c+48,"nextdata_n", false,-1);
    tracep->declBus(c+3,"data", false,-1, 7,0);
    tracep->declBit(c+1,"ready", false,-1);
    tracep->declBit(c+2,"overflow", false,-1);
    tracep->declBus(c+5,"key_count", false,-1, 7,0);
    tracep->declBus(c+6,"buffer", false,-1, 9,0);
    for (int i = 0; i < 8; ++i) {
        tracep->declBus(c+7+i*1,"fifo", true,(i+0), 7,0);
    }
    tracep->declBus(c+15,"w_ptr", false,-1, 2,0);
    tracep->declBus(c+16,"r_ptr", false,-1, 2,0);
    tracep->declBus(c+17,"count", false,-1, 3,0);
    tracep->declBus(c+18,"ps2_clk_sync", false,-1, 2,0);
    tracep->declBit(c+19,"sampling", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_ps2_to_ascii ");
    tracep->declBus(c+45,"x", false,-1, 7,0);
    tracep->declBus(c+25,"y", false,-1, 7,0);
    tracep->declBus(c+25,"tmp", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_reg1 ");
    tracep->declBus(c+53,"WIDTH", false,-1, 31,0);
    tracep->declBus(c+54,"RESET_VAL", false,-1, 7,0);
    tracep->declBit(c+33,"clk", false,-1);
    tracep->declBit(c+23,"rst", false,-1);
    tracep->declBus(c+26,"din", false,-1, 7,0);
    tracep->declBus(c+37,"dout", false,-1, 7,0);
    tracep->declBit(c+24,"wen", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_reg2 ");
    tracep->declBus(c+53,"WIDTH", false,-1, 31,0);
    tracep->declBus(c+54,"RESET_VAL", false,-1, 7,0);
    tracep->declBit(c+33,"clk", false,-1);
    tracep->declBit(c+23,"rst", false,-1);
    tracep->declBus(c+27,"din", false,-1, 7,0);
    tracep->declBus(c+38,"dout", false,-1, 7,0);
    tracep->declBit(c+24,"wen", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_reg3 ");
    tracep->declBus(c+53,"WIDTH", false,-1, 31,0);
    tracep->declBus(c+54,"RESET_VAL", false,-1, 7,0);
    tracep->declBit(c+33,"clk", false,-1);
    tracep->declBit(c+23,"rst", false,-1);
    tracep->declBus(c+28,"din", false,-1, 7,0);
    tracep->declBus(c+39,"dout", false,-1, 7,0);
    tracep->declBit(c+24,"wen", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_reg4 ");
    tracep->declBus(c+53,"WIDTH", false,-1, 31,0);
    tracep->declBus(c+54,"RESET_VAL", false,-1, 7,0);
    tracep->declBit(c+33,"clk", false,-1);
    tracep->declBit(c+23,"rst", false,-1);
    tracep->declBus(c+29,"din", false,-1, 7,0);
    tracep->declBus(c+40,"dout", false,-1, 7,0);
    tracep->declBit(c+24,"wen", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_seg1 ");
    tracep->declBus(c+46,"b", false,-1, 3,0);
    tracep->declBus(c+26,"h", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_seg2 ");
    tracep->declBus(c+47,"b", false,-1, 3,0);
    tracep->declBus(c+27,"h", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_seg3 ");
    tracep->declBus(c+31,"b", false,-1, 3,0);
    tracep->declBus(c+28,"h", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_seg4 ");
    tracep->declBus(c+32,"b", false,-1, 3,0);
    tracep->declBus(c+29,"h", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_seg5 ");
    tracep->declBus(c+20,"b", false,-1, 3,0);
    tracep->declBus(c+41,"h", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_seg6 ");
    tracep->declBus(c+21,"b", false,-1, 3,0);
    tracep->declBus(c+42,"h", false,-1, 7,0);
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
    bufp->fullBit(oldp+1,(vlSelf->top__DOT__ready));
    bufp->fullBit(oldp+2,(vlSelf->top__DOT__overflow));
    bufp->fullCData(oldp+3,(vlSelf->top__DOT__tmp_data),8);
    bufp->fullCData(oldp+4,(vlSelf->top__DOT__out_data),8);
    bufp->fullCData(oldp+5,(vlSelf->top__DOT__key_count),8);
    bufp->fullSData(oldp+6,(vlSelf->top__DOT__my_keyboard__DOT__buffer),10);
    bufp->fullCData(oldp+7,(vlSelf->top__DOT__my_keyboard__DOT__fifo[0]),8);
    bufp->fullCData(oldp+8,(vlSelf->top__DOT__my_keyboard__DOT__fifo[1]),8);
    bufp->fullCData(oldp+9,(vlSelf->top__DOT__my_keyboard__DOT__fifo[2]),8);
    bufp->fullCData(oldp+10,(vlSelf->top__DOT__my_keyboard__DOT__fifo[3]),8);
    bufp->fullCData(oldp+11,(vlSelf->top__DOT__my_keyboard__DOT__fifo[4]),8);
    bufp->fullCData(oldp+12,(vlSelf->top__DOT__my_keyboard__DOT__fifo[5]),8);
    bufp->fullCData(oldp+13,(vlSelf->top__DOT__my_keyboard__DOT__fifo[6]),8);
    bufp->fullCData(oldp+14,(vlSelf->top__DOT__my_keyboard__DOT__fifo[7]),8);
    bufp->fullCData(oldp+15,(vlSelf->top__DOT__my_keyboard__DOT__w_ptr),3);
    bufp->fullCData(oldp+16,(vlSelf->top__DOT__my_keyboard__DOT__r_ptr),3);
    bufp->fullCData(oldp+17,(vlSelf->top__DOT__my_keyboard__DOT__count),4);
    bufp->fullCData(oldp+18,(vlSelf->top__DOT__my_keyboard__DOT__ps2_clk_sync),3);
    bufp->fullBit(oldp+19,((IData)((4U == (6U & (IData)(vlSelf->top__DOT__my_keyboard__DOT__ps2_clk_sync))))));
    bufp->fullCData(oldp+20,((0xfU & (IData)(vlSelf->top__DOT__key_count))),4);
    bufp->fullCData(oldp+21,((0xfU & ((IData)(vlSelf->top__DOT__key_count) 
                                      >> 4U))),4);
    bufp->fullCData(oldp+22,(vlSelf->top__DOT__state),4);
    bufp->fullBit(oldp+23,((1U != (IData)(vlSelf->top__DOT__state))));
    bufp->fullBit(oldp+24,((1U == (IData)(vlSelf->top__DOT__state))));
    bufp->fullCData(oldp+25,(vlSelf->top__DOT__my_ps2_to_ascii__DOT__tmp),8);
    bufp->fullCData(oldp+26,(vlSelf->top__DOT__tmp_seg0),8);
    bufp->fullCData(oldp+27,(vlSelf->top__DOT__tmp_seg1),8);
    bufp->fullCData(oldp+28,(vlSelf->top__DOT__tmp_seg2),8);
    bufp->fullCData(oldp+29,(vlSelf->top__DOT__tmp_seg3),8);
    bufp->fullCData(oldp+30,(vlSelf->top__DOT__next_state),4);
    bufp->fullCData(oldp+31,((0xfU & (IData)(vlSelf->top__DOT__my_ps2_to_ascii__DOT__tmp))),4);
    bufp->fullCData(oldp+32,((0xfU & ((IData)(vlSelf->top__DOT__my_ps2_to_ascii__DOT__tmp) 
                                      >> 4U))),4);
    bufp->fullBit(oldp+33,(vlSelf->clk));
    bufp->fullBit(oldp+34,(vlSelf->clrn));
    bufp->fullBit(oldp+35,(vlSelf->ps2_clk));
    bufp->fullBit(oldp+36,(vlSelf->ps2_data));
    bufp->fullCData(oldp+37,(vlSelf->seg0),8);
    bufp->fullCData(oldp+38,(vlSelf->seg1),8);
    bufp->fullCData(oldp+39,(vlSelf->seg2),8);
    bufp->fullCData(oldp+40,(vlSelf->seg3),8);
    bufp->fullCData(oldp+41,(vlSelf->seg4),8);
    bufp->fullCData(oldp+42,(vlSelf->seg5),8);
    bufp->fullCData(oldp+43,(vlSelf->seg6),8);
    bufp->fullCData(oldp+44,(vlSelf->seg7),8);
    bufp->fullCData(oldp+45,(((1U == (IData)(vlSelf->top__DOT__state))
                               ? (IData)(vlSelf->top__DOT__out_data)
                               : 0U)),8);
    bufp->fullCData(oldp+46,(((1U == (IData)(vlSelf->top__DOT__state))
                               ? (0xfU & (IData)(vlSelf->top__DOT__out_data))
                               : 0U)),4);
    bufp->fullCData(oldp+47,(((1U == (IData)(vlSelf->top__DOT__state))
                               ? (0xfU & ((IData)(vlSelf->top__DOT__out_data) 
                                          >> 4U)) : 0U)),4);
    bufp->fullBit(oldp+48,(vlSelf->top__DOT__nextdata_n));
    bufp->fullCData(oldp+49,(0U),4);
    bufp->fullCData(oldp+50,(1U),4);
    bufp->fullCData(oldp+51,(2U),4);
    bufp->fullCData(oldp+52,(4U),4);
    bufp->fullIData(oldp+53,(8U),32);
    bufp->fullCData(oldp+54,(0xffU),8);
}
