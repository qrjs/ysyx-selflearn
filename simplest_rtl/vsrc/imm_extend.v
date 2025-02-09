`include "/root/ysyx-workbench/simplest_rtl/vsrc/define.v"

module RI_type(
    input  wire [4:0]       rs2,
    input  wire [6:0]       funct7,
    input  wire [`TYPE_BUS] type2,
    output reg  [11:0]      imm_12
);
    always @(*) begin
        case (type2)
            `INST_R: imm_12 = 12'b0000_0000_0000;
            `INST_I: imm_12 = {funct7, rs2};
            //`INST_S: imm_12 = {funct7, rd};
            //`INST_B: imm_12 = {funct7[6], rd[0], funct7[5:0], rd[4:1]};
            default:imm_12 = 12'b0000_0000_0000; 
        endcase
    end
endmodule

module Extend_12(
    input  wire [11:0]    imm_12,
    output wire [`Reg_Bus] imm_12_to_32
);
    assign imm_12_to_32 = {{20{imm_12[11]}}, imm_12};
endmodule


module imm_extend(
    input  wire [4:0]       rs2,
    input  wire [6:0]       funct7,
    input  wire [`TYPE_BUS] type3,
    output wire [`Reg_Bus]   imm32
);

    wire[11:0] imm_12;

    RI_type RI_type_inst(
        .rs2   (rs2),
        .funct7(funct7),
        .type2 (type3),
        .imm_12(imm_12)
    );

    Extend_12 Extend_12_inst(
        .imm_12      (imm_12),
        .imm_12_to_32(imm32)
    );

endmodule