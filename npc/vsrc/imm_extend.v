// 包含全局定义文件
`include "/home/jrq/ysyx-workbench/npc/vsrc/define.v"

/**
 * RISB_type模块 - 负责处理R/I/S/B型指令的立即数提取
 * 
 * 从指令的不同字段中提取12位立即数
 * - R型指令没有立即数，返回0
 * - I型指令的立即数在fun7和rs2字段 [31:20]
 * - S型指令的立即数在fun7和rd字段 [31:25,11:7]
 * - B型指令的立即数分散在fun7和rd字段，需要重新排列
 */
module RISB_type(
    input  wire [4:0]       rs2,        // 源寄存器2地址(指令位[24:20])
    input  wire [4:0]       rd,         // 目标寄存器地址(指令位[11:7])
    input  wire [6:0]       fun7,       // 功能码7(指令位[31:25])
    input  wire [`TYPE_BUS] IType,      // 指令类型
    output reg  [11:0]      imm_12      // 提取的12位立即数
);

// 导入DPI-C函数用于异常处理
import "DPI-C" function void ebreak (input int station, input int inst, input byte unit);

 always @(*) begin
        case (IType)
            `INST_R: imm_12 = 12'b0000_0000_0000;   // R型指令无立即数，返回0
            `INST_I: imm_12 = {fun7, rs2};          // I型指令：imm[11:0] = inst[31:20]
            `INST_S: imm_12 = {fun7, rd};           // S型指令：imm[11:5] = inst[31:25], imm[4:0] = inst[11:7]
            `INST_B: imm_12 = {fun7[6], rd[0], fun7[5:0], rd[4:1]}; // B型指令：imm[12|10:5|4:1|11] = inst[31|30:25|11:8|7]
            `INST_U,
            `INST_J: imm_12 = 12'b0000_0000_0000;   // U/J型指令使用UJ_type模块处理，这里返回0
            default: begin
                        imm_12 = 0;                  // 默认值
                        ebreak(`ABORT, 32'hdeadbeaf, `Unit_IE1); // 错误处理
                    end
        endcase
    end
endmodule

/**
 * UJ_type模块 - 负责处理U/J型指令的立即数提取
 * 
 * 从指令的不同字段中提取20位立即数
 * - U型指令的立即数在高20位 [31:12]
 * - J型指令的立即数分散在多个字段，需要重新排列
 */
module UJ_type(
    input  wire [4:0]       rs1,        // 源寄存器1地址(指令位[19:15])
    input  wire [4:0]       rs2,        // 源寄存器2地址(指令位[24:20])
    input  wire [2:0]       fun3,       // 功能码3(指令位[14:12])
    input  wire [6:0]       fun7,       // 功能码7(指令位[31:25])
    input  wire [`TYPE_BUS] IType,      // 指令类型
    output reg  [19:0]      imm_20      // 提取的20位立即数
);

    // 导入DPI-C函数用于异常处理
    import "DPI-C" function void ebreak(input int station, input int inst, input byte unit);

    always @(*) begin
        case (IType)
            `INST_R,
            `INST_I,
            `INST_S,
            `INST_B: imm_20 = 20'b0000_0000_0000_0000_0000; // R/I/S/B型指令使用RISB_type模块处理，这里返回0
            `INST_U: imm_20 = {fun7, rs2, rs1, fun3};       // U型指令：imm[31:12] = inst[31:12]
            `INST_J: imm_20 = {fun7[6], rs1, fun3, rs2[0], fun7[5:0], rs2[4:1]}; // J型指令：imm[20|10:1|11|19:12] = inst[31|30:21|20|19:12]
            default: begin
                        imm_20 = 0;                          // 默认值
                        ebreak(`ABORT, 32'hdeadbeaf, `Unit_IE2); // 错误处理
                    end 
        endcase
    end
endmodule

/**
 * extend_12模块 - 12位立即数符号扩展到32位
 * 
 * 将RISB_type模块提取的12位立即数扩展为32位
 * 使用最高位(符号位)进行符号扩展
 */
module extend_12(
    input  wire [11:0]    imm_12,        // 输入的12位立即数
    output wire [`Reg_Bus] imm_12_to_32  // 扩展后的32位立即数
);
    // 使用高位(符号位)填充高20位，保持低12位不变
    assign imm_12_to_32 = {{20{imm_12[11]}}, imm_12};
endmodule

/**
 * extend_20模块 - 20位立即数符号扩展到32位
 * 
 * 将UJ_type模块提取的20位立即数扩展为32位
 * 使用最高位(符号位)进行符号扩展
 */
module extend_20(
    input  wire [19:0]    imm_20,        // 输入的20位立即数
    output wire [`Reg_Bus] imm_20_to_32  // 扩展后的32位立即数
);
    // 使用高位(符号位)填充高12位，保持低20位不变
    assign imm_20_to_32 = {{12{imm_20[19]}}, imm_20};
endmodule


/**
 * imm_extend模块 - 顶层立即数扩展模块
 * 
 * 整合RISB_type和UJ_type模块，处理各种指令类型的立即数
 * 根据指令类型进行适当的位移操作，生成最终的32位立即数
 */
module imm_extend(
    input  wire [4:0]       rs1,         // 源寄存器1地址
    input  wire [4:0]       rs2,         // 源寄存器2地址
    input  wire [4:0]       rd,          // 目标寄存器地址
    input  wire [2:0]       fun3,        // 功能码3
    input  wire [6:0]       fun7,        // 功能码7
    input  wire [`TYPE_BUS] IType,       // 指令类型
    output reg  [`Reg_Bus]   imm32       // 最终生成的32位立即数
);

    // 导入DPI-C函数用于异常处理
    import "DPI-C" function void ebreak(input int station, input int inst, input byte unit);

    // 中间信号声明
    wire[11:0]    imm_12;               // 12位立即数(RISB型)
    wire[19:0]    imm_20;               // 20位立即数(UJ型)
    wire[`Reg_Bus] imm_12_to_32;        // 扩展后的32位立即数(RISB型)
    wire[`Reg_Bus] imm_20_to_32;        // 扩展后的32位立即数(UJ型)

    // RISB_type模块实例化 - 处理R/I/S/B型指令
    RISB_type RISB_type_inst(
        .rs2   (rs2),                   // 源寄存器2地址
        .rd    (rd),                    // 目标寄存器地址
        .fun7(fun7),                    // 功能码7
        .IType (IType),                 // 指令类型
        .imm_12(imm_12)                 // 输出12位立即数
    );

    // UJ_type模块实例化 - 处理U/J型指令
    UJ_type UJ_type_inst(
        .rs1   (rs1),                   // 源寄存器1地址
        .rs2   (rs2),                   // 源寄存器2地址
        .fun3(fun3),                    // 功能码3
        .fun7(fun7),                    // 功能码7
        .IType (IType),                 // 指令类型
        .imm_20(imm_20)                 // 输出20位立即数
    );

    // extend_12模块实例化 - 12位立即数扩展到32位
    extend_12 extend_12_inst(
        .imm_12      (imm_12),          // 输入12位立即数
        .imm_12_to_32(imm_12_to_32)     // 输出扩展后的32位立即数
    );

    // extend_20模块实例化 - 20位立即数扩展到32位
    extend_20 extend_20_inst(
        .imm_20      (imm_20),          // 输入20位立即数
        .imm_20_to_32(imm_20_to_32)     // 输出扩展后的32位立即数
    );

    // 根据指令类型进行适当的位移并生成最终立即数
    always @(*) begin
        case (IType)
            `INST_R, `INST_I, `INST_S: imm32 = imm_12_to_32;        // R/I/S型指令直接使用扩展后的12位立即数
            `INST_B:                   imm32 = imm_12_to_32 << 1;   // B型指令左移1位(因为跳转指令地址按字对齐)
            `INST_U:                   imm32 = imm_20_to_32 << 12;  // U型指令左移12位(LUI/AUIPC指令)
            `INST_J:                   imm32 = imm_20_to_32 << 1;   // J型指令左移1位(因为跳转指令地址按字对齐)
            default: begin
                        imm32 = 32'hdeafbeaf;                       // 默认值(出错标记)
                        ebreak(`ABORT, 32'hdeafbeaf, `Unit_IE3);    // 错误处理
                    end
        endcase
    end
endmodule