// 包含全局定义文件
`include "/home/jrq/ysyx-workbench/npc/vsrc/define.v"

/**
 * PC模块 - 程序计数器
 * 该模块负责PC的更新与跳转控制
 * 
 * 根据输入的控制信号(m1,m2)和数据(result,imm32)决定下一个PC值
 * 支持顺序执行(PC+4)、条件分支跳转和无条件跳转
 */
module PC(
  input  wire           clk,          // 时钟信号
  input  wire           rst,          // 复位信号
  input  wire           m1,           // 多路选择器1控制信号，用于分支指令
  input  wire           m2,           // 多路选择器2控制信号，用于跳转指令
  input  wire [`Reg_Bus] result,      // ALU计算结果，用于JALR指令
  input  wire [`Reg_Bus] imm32,       // 立即数，用于分支跳转偏移量
  output wire [`Reg_Bus] PCadd4,      // PC+4，用于顺序执行和保存返回地址
  output reg  [`Reg_Bus] pc /* verilator public */ // 当前PC值
);

  // 内部信号声明
  wire [`Reg_Bus] npc;               // 新的PC值
  wire [`Reg_Bus] npc_temp;          // 中间PC值(多路选择器1的输出)
  wire [`Reg_Bus] PCaddIMM32;        // PC+立即数，用于条件分支和JAL指令
  
  // 计算PC+4和PC+立即数
  assign PCadd4     = pc + 4;          // 顺序执行的下一个PC
  assign PCaddIMM32 = pc + imm32;      // 分支/跳转目标地址

  // PC寄存器更新逻辑
  always @(posedge clk) begin
    if(rst == `RST_VAL)               // 复位条件
      pc <= `RESET_VECTOR;            // 设置为复位向量地址
    else if(clk)                      // 时钟上升沿
      pc <= npc;                      // 更新为新的PC值
    else
      pc <= pc;                       // 保持不变
  end

  // MUX1 多路选择器 - 基于分支条件选择PC值
  // 当(m1 & result[0])为1时选择PCaddIMM32(分支跳转)，否则选择npc_temp
  MuxKey #(2, 1, `Bit_Width) i1(npc, (m1 & result[0]), {
      1'b0, npc_temp,                 // 不跳转，使用MUX2的输出
      1'b1, PCaddIMM32}               // 跳转，使用PC+立即数
  );

  // MUX2 多路选择器 - 选择非分支情况下的PC值
  // 根据m2选择PC+4(普通指令)或result(JALR指令)
  MuxKey #(2, 1, `Bit_Width) i2(npc_temp, (m2), {
      `MUX2_PCadd4, PCadd4,           // 选择PC+4
      `MUX2_result, result}           // 选择ALU结果(JALR指令)
  );

endmodule




/**
 * rv32模块 - RISC-V 32位CPU顶层模块
 * 
 * 整合了CPU的所有功能单元，包括：
 * - 程序计数器(PC)
 * - 寄存器文件(Register File)
 * - 算术逻辑单元(ALU)
 * - 译码单元(Decode)
 * - 存储器接口(Memory)
 * - 立即数扩展单元(Imm Extend)
 * 
 * 该模块实现了一个单周期RISC-V 32位CPU核心
 */
module rv32(
  input  wire           clk,          // 时钟信号
  input  wire           rst           // 复位信号
);
  /* verilator lint_off UNOPTFLAT */
  wire[`Reg_Bus]   pc/* verilator public */;    // 程序计数器
  /* verilator lint_off UNOPTFLAT */
  wire[`Reg_Bus]   inst/* verilator public */;  // 当前指令
  wire[4:0]       rs1;                // 源寄存器1地址
  wire[4:0]       rs2;                // 源寄存器2地址
  wire[4:0]       rd;                 // 目标寄存器地址
  wire[2:0]       fun3;               // 功能码3
  wire[6:0]       fun7;               // 功能码7
  wire[`TYPE_BUS] IType;              // 指令类型
  wire            reg_wen;            // 寄存器写使能
  wire            mem_wen;            // 内存写使能
  wire            mem_ren;            // 内存读使能
  wire[7:0]       wmask;              // 内存写掩码
  wire[2:0]       rmask;              // 内存读掩码
  wire            m1;                 // 多路选择器1选择信号
  wire            m2;                 // 多路选择器2选择信号
  wire            m3;                 // 多路选择器3选择信号
  wire            m4;                 // 多路选择器4选择信号
  wire[1:0]       m5;                 // 多路选择器5选择信号
  wire[`Alu_S]  alus;                 // ALU操作类型
  wire[`Reg_Bus]   PCadd4;            // PC+4值
  wire[`Reg_Bus]   result;            // ALU计算结果
  wire[`Reg_Bus]   reg_in;            // 寄存器写入值
  wire[`Reg_Bus]   src1;              // 源寄存器1的值
  wire[`Reg_Bus]   src2;              // 源寄存器2的值
  wire[`Reg_Bus]   imm32;             // 扩展后的32位立即数
  wire[`Reg_Bus]   num1;              // ALU操作数1
  wire[`Reg_Bus]   num2;              // ALU操作数2
  wire[`Reg_Bus]   mem_rdata;         // 内存读取数据


  // PC模块实例化 - 管理程序计数器更新
  PC PC_inst(
    .clk      (clk),                  // 时钟信号
    .rst      (rst),                  // 复位信号
    .m1       (m1),                   // 分支控制信号
    .m2       (m2),                   // 跳转控制信号
    .result   (result),               // ALU结果(用于JALR指令)
    .imm32    (imm32),                // 立即数(用于分支/跳转偏移)
    .PCadd4   (PCadd4),               // PC+4值
    .pc       (pc)                    // 当前PC输出
  );

  // 存储器模块实例化 - 处理指令和数据存储器访问
  mem mem_inst(
    .clk      (clk),                  // 时钟信号
    .mem_wen  (mem_wen),              // 内存写使能
    .wmask    (wmask),                // 写掩码(控制写入的字节)
    .waddr    (result),               // 写地址(来自ALU结果)
    .wdata    (src2),                 // 写数据(来自寄存器rs2)
    .mem_ren  (mem_ren),              // 内存读使能
    .rmask    (rmask),                // 读掩码(控制读取的字节)
    .raddr    (result),               // 读地址(来自ALU结果)
    .inst_addr(pc),                   // 指令读取地址(来自PC)
    .rdata    (mem_rdata),            // 数据读取结果
    .inst_data(inst)                  // 指令读取结果
  );

  // 译码单元模块实例化 - 解码指令并生成控制信号
  decode decode_unit_inst(
    .inst      (inst),                // 当前指令
    .rd_11_7   (rd),                  // 目标寄存器地址
    .rs1_19_15 (rs1),                 // 源寄存器1地址
    .rs2_24_20 (rs2),                 // 源寄存器2地址
    .fun3_14_12(fun3),                // 功能码3
    .fun7_31_25(fun7),                // 功能码7
    .IType     (IType),               // 指令类型
    .alus      (alus),                // ALU操作类型
    .reg_wen   (reg_wen),             // 寄存器写使能
    .mem_wen   (mem_wen),             // 内存写使能
    .mem_ren   (mem_ren),             // 内存读使能
    .wmask     (wmask),               // 内存写掩码
    .rmask     (rmask),               // 内存读掩码
    .m1        (m1),                  // 多路选择器1控制(分支控制)
    .m2        (m2),                  // 多路选择器2控制(跳转控制)
    .m3        (m3),                  // 多路选择器3控制(ALU操作数2选择)
    .m4        (m4),                  // 多路选择器4控制(ALU操作数1选择)
    .m5        (m5)                   // 多路选择器5控制(寄存器写入数据选择)
  );

  // 寄存器文件模块实例化 - 管理CPU寄存器
  register_file register_file_inst(
    .clk      (clk),                  // 时钟信号
    .rst      (rst),                  // 复位信号
    .reg_wen  (reg_wen),              // 寄存器写使能
    .rs1      (rs1),                  // 源寄存器1地址
    .rs2      (rs2),                  // 源寄存器2地址
    .rd       (rd),                   // 目标寄存器地址
    .reg_in   (reg_in),               // 写入数据
    .src1     (src1),                 // 源寄存器1读出值
    .src2     (src2)                  // 源寄存器2读出值
  );

  // 立即数扩展模块实例化 - 根据指令类型生成32位立即数
  imm_extend imm_extend_inst(
    .rs1   (rs1),                     // 源寄存器1地址(部分立即数可能用到)
    .rs2   (rs2),                     // 源寄存器2地址(部分立即数可能用到)
    .rd    (rd),                      // 目标寄存器地址(部分立即数可能用到)
    .fun3  (fun3),                    // 功能码3
    .fun7  (fun7),                    // 功能码7
    .IType (IType),                   // 指令类型(决定立即数格式)
    .imm32 (imm32)                    // 生成的32位立即数
  );

  // 多路选择器3 - 选择ALU的第二个操作数
  // 根据m3选择src2(寄存器值)或imm32(立即数)
  MuxKey #(2, 1, `Bit_Width) i3(num2, m3, {
      `MUX3_src2,  src2,              // 选择寄存器rs2的值
      `MUX3_imm32, imm32}             // 选择立即数
  );

  // 多路选择器4 - 选择ALU的第一个操作数
  // 根据m4选择pc或src1(寄存器值)
  MuxKey #(2, 1, `Bit_Width) i4(num1, m4, {
      `MUX4_pc,   pc,                 // 选择PC值(用于AUIPC和JAL指令)
      `MUX4_src1, src1}               // 选择寄存器rs1的值
  );

  // 多路选择器5 - 选择写回寄存器的数据
  // 根据m5选择不同的数据源
  MuxKey #(4, 2, `Bit_Width) i5(reg_in, m5, {
      `MUX5_PCadd4, PCadd4,           // 选择PC+4(用于JAL/JALR指令)
      `MUX5_memdat, mem_rdata,        // 选择内存读取数据(用于LOAD指令)
      `MUX5_result, result,           // 选择ALU结果(用于大多数算术/逻辑指令)
      `MUX5_IDLE,   32'hdeadbeaf}     // 空闲状态(未使用)
  );
  
  // ALU模块实例化 - 执行算术和逻辑运算
  alu alu_inst(
    .alus  (alus),                    // ALU操作类型
    .src1  (num1),                    // 第一个操作数
    .src2  (num2),                    // 第二个操作数
    .result(result)                   // 计算结果
  );
endmodule

