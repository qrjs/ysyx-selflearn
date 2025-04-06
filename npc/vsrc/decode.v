`include "/home/jrq/ysyx-workbench/npc/vsrc/define.v"
module decode(
    input  wire [`Reg_Bus] inst,
    output wire [4:0]      rd_11_7,
    output wire [4:0]      rs1_19_15,
    output wire [4:0]      rs2_24_20,
    output wire [2:0]      fun3_14_12,
    output wire [6:0]      fun7_31_25,
    output reg  [`TYPE_BUS] IType,      //inst type
    output reg  [`Alu_S]  alus,       //alu operation type
    output reg              reg_wen,    //RegFile write enable
    output reg              mem_wen,    //mem write enable
    output reg              mem_ren,    //mem read  enable
    output reg  [7:0]       wmask,      //mem write mask
    output reg  [2:0]       rmask,      //mem read  mask
    output reg              m1,         //mux1 sel
    output reg              m2,         //mux2 sel
    output reg              m3,         //mux3 sel
    output reg              m4,         //mux4 sel
    output reg  [1:0]       m5          //mux5 sel

);

import "DPI-C" function void ebreak (input int station , input int inst , input byte unit );
 wire [6:0] opcode_6_0  ;
assign fun7_31_25        =  inst[31:25];
assign fun3_14_12        =  inst[14:12];
assign rs1_19_15         =  inst[19:15];
assign rs2_24_20         =  inst[24:20];
assign rd_11_7           =  inst[11:7];
assign opcode_6_0 [6:0]  =  inst[6:0];


always@(*)begin
   case(opcode_6_0)
    `INST_TYPE_I:begin
        IType   =  `INST_I;
        reg_wen =  1;
        mem_wen =  0;
        mem_ren =  0;
        wmask   =  `WByte;// free
        rmask   =  `LoadB;// free
        m1      =  `MUX1_NB;
        m2      =  `MUX2_PCadd4;
        m3      =  `MUX3_imm32;
        m4      =  `MUX4_src1;
        m5      =  `MUX5_result;
        case(fun3_14_12)
        `INST_ADDI:  alus = `ADD;
        `INST_SLTIU: alus = `LTU;
        `INST_XORI:  alus = `XOR;
        `INST_ANDI:  alus = `AND;
        `INST_SLLI:  alus = `SLL;
        `INST_SRLAI:begin
            case(fun7_31_25)
            7'b000_0000:alus = `SRL;
            7'b010_0000:alus = `SRA;
            default:ebreak(`ABORT,inst,`Unit_CU1);
            endcase
        end
        default:    ebreak(`ABORT,inst,`Unit_CU2);
        endcase
    end
    `INST_TYPE_R:begin
        IType   = `INST_R;
        reg_wen = 1;
        mem_wen = 0;
        mem_ren = 0;
        wmask   = `WByte;// free
        rmask   = `LoadB;// free
        m1      = `MUX1_NB;
        m2      = `MUX2_PCadd4;
        m3      = `MUX3_src2;
        m4      = `MUX4_src1;
        m5      = `MUX5_result;
        if(fun7_31_25 == 7'b000_0000) begin
                    case (fun3_14_12)
                        `INST_ADD:  alus = `ADD;
                        `INST_SLL:  alus = `SLL;
                        `INST_SLTU: alus = `LTU;
                        `INST_XOR:  alus = `XOR;
                        `INST_SRL:  alus = `SRL;
                        `INST_OR:   alus = `OR;
                        `INST_AND:  alus = `AND;
                        default:    ebreak(`ABORT, inst, `Unit_CU3); 
                    endcase                
                end else if(fun7_31_25 == 7'b010_0000) begin
                    case (fun3_14_12)
                        `INST_SUB: alus = `SUB;
                        `INST_SRA: alus = `SRA;
                        default:   ebreak(`ABORT, inst, `Unit_CU4); 
                    endcase  
                end else begin
                    ebreak(`ABORT, inst, `Unit_CU5);  
    end
    end
    `INST_TYPE_L:begin
        IType   = `INST_I;
        reg_wen = 1;
        mem_wen = 0;
        mem_ren = 1;
        wmask   = `WByte;// free
        m1      = `MUX1_NB;
        m2      = `MUX2_PCadd4;
        m3      = `MUX3_imm32;
        m4      = `MUX4_src1;
        m5      = `MUX5_memdat;
        alus    = `ADD;
        case(fun3_14_12)
            `INST_LB:  rmask = `LoadB;
            `INST_LH:  rmask = `LoadH;
            `INST_LW:  rmask = `LoadW;
            `INST_LBU: rmask = `LoadBU;
            `INST_LHU: rmask = `LoadHU;
            default:  ebreak(`ABORT, inst, `Unit_CU6);  
        endcase
    end
    `INST_TYPE_B: begin
                IType   = `INST_B;   
                reg_wen = 0;  
                mem_wen = 0;  
                mem_ren = 0;  
                wmask   = `WWord;            // free 
                rmask   = `LoadW;            // free  
                m1      = `MUX1_B;
                m2      = `MUX2_PCadd4;      // free
                m3      = `MUX3_src2;
                m4      = `MUX4_src1;
                m5      = `MUX5_result;      // free
                case (fun3_14_12)
                    `INST_BEQ:  alus = `EQ;
                    `INST_BNE:  alus = `NE;
                    `INST_BLT:  alus = `LT;
                    `INST_BGE:  alus = `GE;
                    `INST_BLTU: alus = `LTU;
                    `INST_BGEU: alus = `GEU;
                    default:   ebreak(`ABORT, inst, `Unit_CU7);  
                endcase
     end
     `INST_TYPE_S: begin
                IType   = `INST_S;   
                alus    = `ADD;
                reg_wen = 0;  
                mem_wen = 1;  
                mem_ren = 0;  
                rmask   = `LoadW;          // free   
                m1      = `MUX1_NB;
                m2      = `MUX2_PCadd4;
                m3      = `MUX3_imm32;
                m4      = `MUX4_src1;
                m5      = `MUX5_memdat;
                case (fun3_14_12)
                    `INST_SB: wmask = `WByte;
                    `INST_SH: wmask = `WHalf;
                    `INST_SW: wmask = `WWord;
                    default:  ebreak(`ABORT, inst, `Unit_CU8);  
                endcase
     end
     `INST_TYPE_LUI: begin
                IType   = `INST_U;   
                alus    = `ADD_LUI;
                reg_wen = 1;  
                mem_wen = 0;   
                mem_ren = 0;   
                wmask   = `WWord;          // free   
                rmask   = `LoadW;          // free   
                m1      = `MUX1_NB;
                m2      = `MUX2_PCadd4;
                m3      = `MUX3_imm32;
                m4      = `MUX4_src1;      // free   
                m5      = `MUX5_result;
     end
    `INST_TYPE_AUIPC: begin
                IType   = `INST_U;   
                alus    = `ADD;
                reg_wen = 1;   
                mem_wen = 0;   
                mem_ren = 0;   
                wmask   = `WWord;          // free      
                rmask   = `LoadW;          // free      
                m1      = `MUX1_NB;
                m2      = `MUX2_PCadd4;
                m3      = `MUX3_imm32;
                m4      = `MUX4_pc;
                m5      = `MUX5_result;
    end
    `INST_TYPE_JALR: begin
                IType   = `INST_I;   
                alus    = `ADD_JALR;
                reg_wen = 1;   
                mem_wen = 0;   
                mem_ren = 0;   
                wmask   = `WWord;          // free      
                rmask   = `LoadW;          // free      
                m1      = `MUX1_NB;
                m2      = `MUX2_result;
                m3      = `MUX3_imm32;
                m4      = `MUX4_src1;
                m5      = `MUX5_PCadd4;
    end            
     `INST_TYPE_JAL: begin
                IType   = `INST_J;   
                alus    = `ADD;
                reg_wen = 1;   
                mem_wen = 0;   
                mem_ren = 0;   
                wmask   = `WWord;          // free      
                rmask   = `LoadW;          // free      
                m1      = `MUX1_NB;
                m2      = `MUX2_result;
                m3      = `MUX3_imm32;
                m4      = `MUX4_pc;
                m5      = `MUX5_PCadd4;
    end
    `INST_TYPE_E: begin
                case ({fun7_31_25, rs2_24_20})
                    `INST_EBREAK: ebreak(`HIT_TRAP, inst, `Unit_CU9);
                     default:     ebreak(`ABORT, inst, `Unit_CU10);
                endcase
    end
    default: ebreak(`ABORT, inst, `Unit_CU11);  
    endcase
    end


endmodule
