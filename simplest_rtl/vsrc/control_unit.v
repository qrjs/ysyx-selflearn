`include "/root/ysyx-workbench/simplest_rtl/vsrc/define.v"

module control_unit(
    input wire [`Reg_Bus] inst,
    output wire [4:0] rd, //11_7
    output wire [4:0] rs1_19_15, //19_15
    output wire [4:0] rs2_24_20, //24_20
    output wire [6:0] fun7, //31_25
    output reg [`TYPE_BUS] type1, //inst type
    output reg             alus, //alu operation type
    output reg             mux1  //mux1 select
);

import "DPI-C" function void ebreak(input int station,input int inst);


wire [6:0] opcode=inst[6:0];
wire [2:0] fun3=inst[14:12];
assign rd=inst[11:7];
assign rs1_19_15=inst[19:15];
assign rs2_24_20=inst[24:20];
assign fun7=inst[31:25];

always@(*)begin
    case(opcode)
    `INST_TYPE_I:begin
        type1=`INST_I; //I type
        mux1=`MUX1_imm; //imm
        case(fun3)
        `INST_ADDI:
            alus=`ADD;
            default:alus=`ADD;
        endcase
        end
    `INST_TYPE_E:begin
        case({fun7,rs2_24_20})
        `INST_EBREAK:ebreak(`HIT_GOOD_TRAP,inst);
        default:ebreak(`ABORT,inst);
        endcase
        end
     default: begin   
                type1 = 3'd0;
                alus  = `ADD;
                mux1    = `MUX1_imm;
            end
        endcase
    end
endmodule