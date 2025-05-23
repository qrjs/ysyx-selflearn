// 包含全局定义文件
`include "/home/jrq/ysyx-workbench/npc/vsrc/define.v"

/**
 * ALU模块(算术逻辑单元)
 * 
 * 实现RISC-V的各种算术和逻辑运算操作
 * 支持加减法、位移、逻辑运算和比较运算等
 * 根据alus信号选择执行不同操作
 */
module alu(
   input  wire [`Alu_S] alus,        // ALU操作选择信号
    input  wire [`Reg_Bus]  src1,    // 源操作数1
    input  wire [`Reg_Bus]  src2,    // 源操作数2
    output reg  [`Reg_Bus]  result   // 计算结果
);

// 导入DPI-C函数用于异常处理
import "DPI-C" function void ebreak(input int station,input int inst,input byte unit);

// ALU操作逻辑
always@(*)begin
   case(alus)
   `ADD:  result = src1 + src2;                                      // 加法运算
   `SUB:  result = src1 - src2;                                      // 减法运算
   `SLL:  result = src1 << (src2 & 32'h1f);                          // 逻辑左移（只使用低5位）
   `XOR:  result = src1 ^ src2;                                      // 异或运算
   `SRL:  result = src1 >> (src2 & 32'h1f);                          // 逻辑右移（只使用低5位）
   `SRA:  result = ($signed(src1)) >>> (src2 & 32'h1f);              // 算术右移(带符号右移)
   `OR:       result = src1 | src2;                                  // 或运算
   `AND:      result = src1 & src2;                                  // 与运算
   `EQ:       result = {{(`Bit_Width - 1){1'b0}}, (src1 == src2)};   // 相等比较(结果为1位)
   `NE:       result = {{(`Bit_Width - 1){1'b0}}, (src1 != src2)};   // 不等比较(结果为1位)
   `LT:       result = {{(`Bit_Width - 1){1'b0}}, (($signed(src1)) <  ($signed(src2)))}; // 带符号小于比较
   `GE:       result = {{(`Bit_Width - 1){1'b0}}, (($signed(src1)) >= ($signed(src2)))}; // 带符号大于等于比较
   `LTU:      result = {{(`Bit_Width - 1){1'b0}}, (src1 <  src2)};   // 无符号小于比较
   `GEU:      result = {{(`Bit_Width - 1){1'b0}}, (src1 >= src2)};   // 无符号大于等于比较
   `ADD_LUI:  result = src2;                                         // LUI指令专用(直接传递src2)
   `ADD_JALR: result = (src1 + src2) & 32'hfffffffe;                 // JALR指令专用(结果最低位置0)
   default:   begin
                  ebreak(`ABORT, 32'hdeabdeaf, `Unit_ALU);           // 调用外部函数报告错误
                  result = 0;                                         // 默认结果为0
               end
   endcase
   end

endmodule
