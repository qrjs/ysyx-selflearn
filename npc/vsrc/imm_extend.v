`include "/home/jrq/ysyx-workbench/npc/vsrc/define.v"

module RISB_type(
    input  wire [4:0]       rs2,
    input  wire [4:0]       rd,
    input  wire [6:0]       fun7,
    input  wire [`TYPE_BUS] IType,
    output reg  [11:0]      imm_12
);

import "DPI-C" function void ebreak (input int station, input int inst, input byte unit);

 always @(*) begin
        case (IType)
            `INST_R: imm_12 = 12'b0000_0000_0000;
            `INST_I: imm_12 = {fun7, rs2};
            `INST_S: imm_12 = {fun7, rd};
            `INST_B: imm_12 = {fun7[6], rd[0], fun7[5:0], rd[4:1]};
            `INST_U,
            `INST_J: imm_12 = 12'b0000_0000_0000;
            default: begin
                        imm_12 = 0;
                        ebreak(`ABORT, 32'hdeadbeaf, `Unit_IE1);
                    end
        endcase
    end
endmodule

module UJ_type(
    input  wire [4:0]       rs1,
    input  wire [4:0]       rs2,
    input  wire [2:0]       fun3,
    input  wire [6:0]       fun7,
    input  wire [`TYPE_BUS] IType,
    output reg  [19:0]      imm_20
);

    import "DPI-C" function void ebreak(input int station, input int inst, input byte unit);

    always @(*) begin
        case (IType)
            `INST_R,
            `INST_I,
            `INST_S,
            `INST_B: imm_20 = 20'b0000_0000_0000_0000_0000;
            `INST_U: imm_20 = {fun7, rs2, rs1, fun3};
            `INST_J: imm_20 = {fun7[6], rs1, fun3, rs2[0], fun7[5:0], rs2[4:1]};
            default: begin
                        imm_20 = 0;
                        ebreak(`ABORT, 32'hdeadbeaf, `Unit_IE2);
                    end 
        endcase
    end
endmodule

module extend_12(
    input  wire [11:0]    imm_12,
    output wire [`Reg_Bus] imm_12_to_32
);
    assign imm_12_to_32 = {{20{imm_12[11]}}, imm_12};
endmodule

module extend_20(
    input  wire [19:0]    imm_20,
    output wire [`Reg_Bus] imm_20_to_32
);
    assign imm_20_to_32 = {{12{imm_20[19]}}, imm_20};
endmodule


module imm_extend(
    input  wire [4:0]       rs1,
    input  wire [4:0]       rs2,
    input  wire [4:0]       rd,
    input  wire [2:0]       fun3,
    input  wire [6:0]       fun7,
    input  wire [`TYPE_BUS] IType,
    output reg  [`Reg_Bus]   imm32
);

    import "DPI-C" function void ebreak(input int station, input int inst, input byte unit);

    wire[11:0]    imm_12;
    wire[19:0]    imm_20;
    wire[`Reg_Bus] imm_12_to_32;
    wire[`Reg_Bus] imm_20_to_32;

    RISB_type RISB_type_inst(
        .rs2   (rs2),
        .rd    (rd),
        .fun7(fun7),
        .IType (IType),
        .imm_12(imm_12)
    );

    UJ_type UJ_type_inst(
        .rs1   (rs1),
        .rs2   (rs2),
        .fun3(fun3),
        .fun7(fun7),
        .IType (IType),
        .imm_20(imm_20)
    );

    extend_12 extend_12_inst(
        .imm_12      (imm_12),
        .imm_12_to_32(imm_12_to_32)
    );

    extend_20 extend_20_inst(
        .imm_20      (imm_20),
        .imm_20_to_32(imm_20_to_32)
    );

    always @(*) begin
        case (IType)
            `INST_R, `INST_I, `INST_S: imm32 = imm_12_to_32;
            `INST_B:                   imm32 = imm_12_to_32 << 1;
            `INST_U:                   imm32 = imm_20_to_32 << 12;
            `INST_J:                   imm32 = imm_20_to_32 << 1;
            default: begin
                        imm32 = 32'hdeafbeaf;
                        ebreak(`ABORT, 32'hdeafbeaf, `Unit_IE3);
                    end
        endcase
    end
endmodule