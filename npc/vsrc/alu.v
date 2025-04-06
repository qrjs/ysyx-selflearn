`include "/home/jrq/ysyx-workbench/npc/vsrc/define.v"
module alu(
   input  wire [`Alu_S] alus,
    input  wire [`Reg_Bus]  src1,
    input  wire [`Reg_Bus]  src2,
    output reg  [`Reg_Bus]  result
);

import "DPI-C" function void ebreak(input int station,input int inst,input byte unit);

always@(*)begin
   case(alus)
   `ADD:  result = src1 + src2;
   `SUB:  result = src1 - src2;
   `SLL:  result = src1 << src2;
   `XOR:  result = src1 ^ src2;
   `SRL:  result = src1 >> src2;
   `SRA:  result = ($signed(src1)) >>> (src2 & 32'h1f) ;
   `OR:       result = src1 | src2;
   `AND:      result = src1 & src2;
   `EQ:       result = {{(`Bit_Width - 1){1'b0}}, (src1 == src2)};
   `NE:       result = {{(`Bit_Width - 1){1'b0}}, (src1 != src2)};
   `LT:       result = {{(`Bit_Width - 1){1'b0}}, (($signed(src1)) <  ($signed(src2)))};
   `GE:       result = {{(`Bit_Width - 1){1'b0}}, (($signed(src1)) >= ($signed(src2)))};
   `LTU:      result = {{(`Bit_Width - 1){1'b0}}, (src1 <  src2)};
   `GEU:      result = {{(`Bit_Width - 1){1'b0}}, (src1 >= src2)};
   `ADD_LUI:  result = src2;
   `ADD_JALR: result = (src1 + src2) & 32'hfffffffe;
   default:   begin
                  ebreak(`ABORT, 32'hdeabdeaf, `Unit_ALU);
                  result = 0;
               end
   endcase
   end

endmodule
