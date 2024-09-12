#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<nvboard.h>

#include"Vtop.h"  // 从top.v生成
#include"verilated.h"
#include"verilated_vcd_c.h"

void nvboard_bind_all_pins(Vtop* top);

int main(int argc, char** argv) {
    VerilatedContext* contextp = new VerilatedContext;
    contextp->traceEverOn(true); // 开启波形 
    contextp->commandArgs(argc, argv);

    Vtop* top = new Vtop{contextp};

    nvboard_bind_all_pins(top);  // 引脚绑定
    nvboard_init();
    VerilatedVcdC* m_trace = new VerilatedVcdC; // trace_object
    top->trace(m_trace, 99);  // 99表示记录最详细的信号信息
    m_trace->open("wave.vcd");  // 波形文件
    
    top->clk = 0;  // clk初始化
    // ----原reset函数----start
    int n = 10;
    top->rst = 1;
    while (n-- > 0){top->clk = !top->clk;top->eval();}
    top->rst = 0;
    // ----原reset函数----end
    while (!contextp->gotFinish()) {
		nvboard_update();
        contextp->timeInc(1);  // 推进仿真时间
        top->clk = !top->clk; top->eval(); // eval()模型更新 可以理解为执行一次.v文件
        m_trace->dump(contextp->time()); // 记录波形
    }
    m_trace->close();
    delete top;
    delete contextp;
    return 0;
}

