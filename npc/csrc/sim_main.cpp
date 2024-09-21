#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <nvboard.h>
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h" // 引入 Verilator 生成的顶层模块头文件

// 定义全局变量
VerilatedContext* contextp;
VerilatedVcdC* tfp;
Vtop* top; // 确保 top 被声明为全局变量

void nvboard_bind_all_pins(Vtop* top);

// 初始化仿真环境
void sim_init() {
    // 初始化 VerilatedContext 和 VerilatedVcdC
    contextp = new VerilatedContext;
    tfp = new VerilatedVcdC;
    top = new Vtop{contextp}; // 正确定义 top

    // 启用波形跟踪
    contextp->traceEverOn(true);
    top->trace(tfp, 99);
    tfp->open("dump.vcd");

    // 初始化 nvboard
    nvboard_bind_all_pins(top);  // 引脚绑定
    nvboard_init();
}

// 进行仿真并转储波形
void step_and_dump_wave() {
    top->eval();
    contextp->timeInc(1);
    tfp->dump(contextp->time());
    nvboard_update(); // 确保更新 nvboard 显示
}

// 结束仿真环境
void sim_exit() {
    step_and_dump_wave();
    tfp->close();
    delete top;
    delete tfp;
    delete contextp;
}

int main() {
    // 初始化仿真
    sim_init();

    // 初始化输入信号
    top->x0 = 0b00; // 二进制表示
    top->x1 = 0b01;
    top->x2 = 0b10;
    top->x3 = 0b11;

    // 测试不同的选择信号 Y
    top->y = 0b00; step_and_dump_wave();  // 选择 X0，期望 F = X0
    top->y = 0b01; step_and_dump_wave();  // 选择 X1，期望 F = X1
    top->y = 0b10; step_and_dump_wave();  // 选择 X2，期望 F = X2
    top->y = 0b11; step_and_dump_wave();  // 选择 X3，期望 F = X3

    // 结束仿真
    sim_exit();
    return 0;
}

