// 包含全局定义文件
`include "/home/jrq/ysyx-workbench/npc/vsrc/define.v"

/**
 * 解码模块(decode) - 指令解码与控制信号生成
 * 
 * 该模块负责解析RISC-V指令并生成各种控制信号
 * 根据指令的操作码(opcode)、功能码(fun3,fun7)等字段，
 * 确定指令类型并设置相应的控制信号
 */
module decode(
    input  wire [`Reg_Bus] inst,        // 输入的指令
    output wire [4:0]      rd_11_7,     // 目标寄存器地址(指令位[11:7])
    output wire [4:0]      rs1_19_15,   // 源寄存器1地址(指令位[19:15])
    output wire [4:0]      rs2_24_20,   // 源寄存器2地址(指令位[24:20])
    output wire [2:0]      fun3_14_12,  // 功能码3(指令位[14:12])
    output wire [6:0]      fun7_31_25,  // 功能码7(指令位[31:25])
    output reg  [`TYPE_BUS] IType,      // 指令类型(R/I/S/B/U/J型)
    output reg  [`Alu_S]  alus,         // ALU操作类型
    output reg              reg_wen,    // 寄存器写使能
    output reg              mem_wen,    // 内存写使能
    output reg              mem_ren,    // 内存读使能
    output reg  [7:0]       wmask,      // 内存写掩码(控制写入的字节)
    output reg  [2:0]       rmask,      // 内存读掩码(控制读取的字节)
    output reg              m1,         // 多路选择器1选择信号(PC跳转控制)
    output reg              m2,         // 多路选择器2选择信号(PC来源选择)
    output reg              m3,         // 多路选择器3选择信号(ALU操作数2选择)
    output reg              m4,         // 多路选择器4选择信号(ALU操作数1选择)
    output reg  [1:0]       m5          // 多路选择器5选择信号(寄存器写入数据选择)
);

// 导入DPI-C函数用于异常处理(用于模拟器与C++代码交互)
import "DPI-C" function void ebreak (input int station , input int inst , input byte unit );

// 提取指令中的操作码
wire [6:0] opcode_6_0;
// 从指令中提取各个字段
assign fun7_31_25        =  inst[31:25];    // 功能码7
assign fun3_14_12        =  inst[14:12];    // 功能码3
assign rs1_19_15         =  inst[19:15];    // 源寄存器1地址
assign rs2_24_20         =  inst[24:20];    // 源寄存器2地址
assign rd_11_7           =  inst[11:7];     // 目标寄存器地址
assign opcode_6_0 [6:0]  =  inst[6:0];      // 操作码

// 指令解码逻辑(组合逻辑)
always@(*)begin
   case(opcode_6_0)
    // I型指令(ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI, SRAI)
    `INST_TYPE_I:begin
        IType   =  `INST_I;             // 设置为I型指令
        reg_wen =  1;                   // 启用寄存器写入
        mem_wen =  0;                   // 禁用内存写入
        mem_ren =  0;                   // 禁用内存读取
        wmask   =  `WByte;              // 内存写掩码(此处无关，设为字节写入)
        rmask   =  `LoadB;              // 内存读掩码(此处无关，设为字节读取)
        m1      =  `MUX1_NB;            // 不进行分支跳转
        m2      =  `MUX2_PCadd4;        // PC+4(顺序执行)
        m3      =  `MUX3_imm32;         // ALU操作数2选择立即数
        m4      =  `MUX4_src1;          // ALU操作数1选择寄存器rs1值
        m5      =  `MUX5_result;        // 寄存器写入数据选择ALU结果
        
        // 根据fun3进一步解码具体的I型指令
        case(fun3_14_12)
        `INST_ADDI:  alus = `ADD;       // 加立即数(ADDI)
        `INST_SLTI:  alus = `LT;        // 有符号小于立即数设置(SLTI)
        `INST_SLTIU: alus = `LTU;       // 无符号小于立即数设置(SLTIU)
        `INST_XORI:  alus = `XOR;       // 异或立即数(XORI)
        `INST_ORI:   alus = `OR;        // 或立即数(ORI)
        `INST_ANDI:  alus = `AND;       // 与立即数(ANDI)
        `INST_SLLI:  alus = `SLL;       // 逻辑左移立即数(SLLI)
        `INST_SRLAI:begin               // 右移立即数(SRLI/SRAI)
            case(fun7_31_25)
            7'b000_0000:alus = `SRL;    // 逻辑右移立即数(SRLI)
            7'b010_0000:alus = `SRA;    // 算术右移立即数(SRAI)
            default:ebreak(`ABORT,inst,`Unit_CU1); // 错误处理
            endcase
        end
        default:    ebreak(`ABORT,inst,`Unit_CU2); // 错误处理
        endcase
    end
    // R型指令(ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND)
    `INST_TYPE_R:begin
        IType   = `INST_R;              // 设置为R型指令
        reg_wen = 1;                    // 启用寄存器写入
        mem_wen = 0;                    // 禁用内存写入
        mem_ren = 0;                    // 禁用内存读取
        wmask   = `WByte;               // 内存写掩码(此处无关)
        rmask   = `LoadB;               // 内存读掩码(此处无关)
        m1      = `MUX1_NB;             // 不进行分支跳转
        m2      = `MUX2_PCadd4;         // PC+4(顺序执行)
        m3      = `MUX3_src2;           // ALU操作数2选择寄存器rs2值
        m4      = `MUX4_src1;           // ALU操作数1选择寄存器rs1值
        m5      = `MUX5_result;         // 寄存器写入数据选择ALU结果
        
        // 根据fun7和fun3进一步解码具体的R型指令
        if(fun7_31_25 == 7'b000_0000) begin
                    case (fun3_14_12)
                        `INST_ADD:  alus = `ADD;   // 加法(ADD)
                        `INST_SLL:  alus = `SLL;   // 逻辑左移(SLL)
                        `INST_SLT:  alus = `LT;    // 有符号小于比较(SLT)
                        `INST_SLTU: alus = `LTU;   // 无符号小于比较(SLTU)
                        `INST_XOR:  alus = `XOR;   // 异或(XOR)
                        `INST_SRL:  alus = `SRL;   // 逻辑右移(SRL)
                        `INST_OR:   alus = `OR;    // 或(OR)
                        `INST_AND:  alus = `AND;   // 与(AND)
                        default:    ebreak(`ABORT, inst, `Unit_CU3); // 错误处理
                    endcase                
                end else if(fun7_31_25 == 7'b010_0000) begin
                    case (fun3_14_12)
                        `INST_SUB: alus = `SUB;    // 减法(SUB)
                        `INST_SRA: alus = `SRA;    // 算术右移(SRA)
                        default:   ebreak(`ABORT, inst, `Unit_CU4); // 错误处理
                    endcase  
                end else begin
                    ebreak(`ABORT, inst, `Unit_CU5); // 错误处理
    end
    end
    
    // 加载指令(LB, LH, LW, LBU, LHU)
    `INST_TYPE_L:begin
        IType   = `INST_I;              // 设置为I型指令(加载指令使用I型格式)
        reg_wen = 1;                    // 启用寄存器写入
        mem_wen = 0;                    // 禁用内存写入
        mem_ren = 1;                    // 启用内存读取
        wmask   = `WByte;               // 内存写掩码(此处无关)
        m1      = `MUX1_NB;             // 不进行分支跳转
        m2      = `MUX2_PCadd4;         // PC+4(顺序执行)
        m3      = `MUX3_imm32;          // ALU操作数2选择立即数(偏移量)
        m4      = `MUX4_src1;           // ALU操作数1选择寄存器rs1值(基址)
        m5      = `MUX5_memdat;         // 寄存器写入数据选择内存读取数据
        alus    = `ADD;                 // ALU执行加法操作(计算内存地址)
        
        // 根据fun3确定内存访问类型(字节/半字/字)
        case(fun3_14_12)
            `INST_LB:  rmask = `LoadB;  // 加载字节(带符号扩展)(LB)
            `INST_LH:  rmask = `LoadH;  // 加载半字(带符号扩展)(LH)
            `INST_LW:  rmask = `LoadW;  // 加载字(LW)
            `INST_LBU: rmask = `LoadBU; // 加载字节(无符号扩展)(LBU)
            `INST_LHU: rmask = `LoadHU; // 加载半字(无符号扩展)(LHU)
            default:  ebreak(`ABORT, inst, `Unit_CU6); // 错误处理
        endcase
    end
    // 分支指令(BEQ, BNE, BLT, BGE, BLTU, BGEU)
    `INST_TYPE_B: begin
                IType   = `INST_B;        // 设置为B型指令(分支指令)
                reg_wen = 0;              // 禁用寄存器写入
                mem_wen = 0;              // 禁用内存写入
                mem_ren = 0;              // 禁用内存读取
                wmask   = `WWord;         // 内存写掩码(此处无关)
                rmask   = `LoadW;         // 内存读掩码(此处无关)
                m1      = `MUX1_B;        // 分支跳转控制(由ALU结果决定)
                m2      = `MUX2_PCadd4;   // PC+4(不跳转时使用)
                m3      = `MUX3_src2;     // ALU操作数2选择寄存器rs2值
                m4      = `MUX4_src1;     // ALU操作数1选择寄存器rs1值
                m5      = `MUX5_result;   // 寄存器写入数据选择(此处无关)
                
                // 根据fun3确定分支条件类型
                case (fun3_14_12)
                    `INST_BEQ:  alus = `EQ;     // 相等时分支(BEQ)
                    `INST_BNE:  alus = `NE;     // 不等时分支(BNE)
                    `INST_BLT:  alus = `LT;     // 小于时分支(带符号)(BLT)
                    `INST_BGE:  alus = `GE;     // 大于等于时分支(带符号)(BGE)
                    `INST_BLTU: alus = `LTU;    // 小于时分支(无符号)(BLTU)
                    `INST_BGEU: alus = `GEU;    // 大于等于时分支(无符号)(BGEU)
                    default:   ebreak(`ABORT, inst, `Unit_CU7); // 错误处理
                endcase
     end
     
     // 存储指令(SB, SH, SW)
     `INST_TYPE_S: begin
                IType   = `INST_S;        // 设置为S型指令(存储指令)
                alus    = `ADD;           // ALU执行加法操作(计算内存地址)
                reg_wen = 0;              // 禁用寄存器写入
                mem_wen = 1;              // 启用内存写入
                mem_ren = 0;              // 禁用内存读取
                rmask   = `LoadW;         // 内存读掩码(此处无关)
                m1      = `MUX1_NB;       // 不进行分支跳转
                m2      = `MUX2_PCadd4;   // PC+4(顺序执行)
                m3      = `MUX3_imm32;    // ALU操作数2选择立即数(偏移量)
                m4      = `MUX4_src1;     // ALU操作数1选择寄存器rs1值(基址)
                m5      = `MUX5_memdat;   // 寄存器写入数据选择(此处无关)
                
                // 根据fun3确定内存写入类型(字节/半字/字)
                case (fun3_14_12)
                    `INST_SB: wmask = `WByte;  // 存储字节(SB)
                    `INST_SH: wmask = `WHalf;  // 存储半字(SH)
                    `INST_SW: wmask = `WWord;  // 存储字(SW)
                    default:  ebreak(`ABORT, inst, `Unit_CU8); // 错误处理
                endcase
     end
     // LUI指令(Load Upper Immediate)
     `INST_TYPE_LUI: begin
                IType   = `INST_U;        // 设置为U型指令
                alus    = `ADD_LUI;       // ALU特殊操作(LUI专用，直接传递立即数)
                reg_wen = 1;              // 启用寄存器写入
                mem_wen = 0;              // 禁用内存写入
                mem_ren = 0;              // 禁用内存读取
                wmask   = `WWord;         // 内存写掩码(此处无关)
                rmask   = `LoadW;         // 内存读掩码(此处无关)
                m1      = `MUX1_NB;       // 不进行分支跳转
                m2      = `MUX2_PCadd4;   // PC+4(顺序执行)
                m3      = `MUX3_imm32;    // ALU操作数2选择立即数
                m4      = `MUX4_src1;     // ALU操作数1选择(此处无关，因为直接使用立即数)
                m5      = `MUX5_result;   // 寄存器写入数据选择ALU结果
     end
     
    // AUIPC指令(Add Upper Immediate to PC)
    `INST_TYPE_AUIPC: begin
                IType   = `INST_U;        // 设置为U型指令
                alus    = `ADD;           // ALU执行加法操作
                reg_wen = 1;              // 启用寄存器写入
                mem_wen = 0;              // 禁用内存写入
                mem_ren = 0;              // 禁用内存读取
                wmask   = `WWord;         // 内存写掩码(此处无关)
                rmask   = `LoadW;         // 内存读掩码(此处无关)
                m1      = `MUX1_NB;       // 不进行分支跳转
                m2      = `MUX2_PCadd4;   // PC+4(顺序执行)
                m3      = `MUX3_imm32;    // ALU操作数2选择立即数
                m4      = `MUX4_pc;       // ALU操作数1选择PC
                m5      = `MUX5_result;   // 寄存器写入数据选择ALU结果
    end
    
    // JALR指令(Jump And Link Register)
    `INST_TYPE_JALR: begin
                IType   = `INST_I;        // 设置为I型指令
                alus    = `ADD_JALR;      // ALU特殊操作(JALR专用，将结果最低位置0)
                reg_wen = 1;              // 启用寄存器写入
                mem_wen = 0;              // 禁用内存写入
                mem_ren = 0;              // 禁用内存读取
                wmask   = `WWord;         // 内存写掩码(此处无关)
                rmask   = `LoadW;         // 内存读掩码(此处无关)
                m1      = `MUX1_NB;       // 不进行分支跳转
                m2      = `MUX2_result;   // 选择ALU结果作为下一个PC值
                m3      = `MUX3_imm32;    // ALU操作数2选择立即数
                m4      = `MUX4_src1;     // ALU操作数1选择寄存器rs1值
                m5      = `MUX5_PCadd4;   // 寄存器写入数据选择PC+4(保存返回地址)
    end            
    
    // JAL指令(Jump And Link)
     `INST_TYPE_JAL: begin
                IType   = `INST_J;        // 设置为J型指令
                alus    = `ADD;           // ALU执行加法操作
                reg_wen = 1;              // 启用寄存器写入
                mem_wen = 0;              // 禁用内存写入
                mem_ren = 0;              // 禁用内存读取
                wmask   = `WWord;         // 内存写掩码(此处无关)
                rmask   = `LoadW;         // 内存读掩码(此处无关)
                m1      = `MUX1_NB;       // 不使用分支逻辑
                m2      = `MUX2_result;   // 选择ALU结果作为下一个PC值
                m3      = `MUX3_imm32;    // ALU操作数2选择立即数(跳转偏移量)
                m4      = `MUX4_pc;       // ALU操作数1选择PC
                m5      = `MUX5_PCadd4;   // 寄存器写入数据选择PC+4(保存返回地址)
    end
    
    // 环境指令(ECALL, EBREAK)
    `INST_TYPE_E: begin
                // 根据功能码进一步识别具体指令
                case ({fun7_31_25, rs2_24_20})
                    `INST_EBREAK: ebreak(`HIT_TRAP, inst, `Unit_CU9); // EBREAK指令，触发断点
                     default:     ebreak(`ABORT, inst, `Unit_CU10);    // 错误处理
                endcase
    end
    default: ebreak(`ABORT, inst, `Unit_CU11);  // 未知指令操作码，错误处理
    endcase
    end


endmodule
