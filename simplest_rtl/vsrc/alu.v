`include "/root/ysyx-workbench/simplest_rtl/vsrc/define.v"


module alu(
    input wire alus,
    input wire [`Reg_Bus] num1,
    input wire [`Reg_Bus] num2,
    output reg [`Reg_Bus] result    
);

always @(*)begin
    case(alus)
    `ADD: result = num1 + num2;
    default: result =num1 + num2;
endcase
end
endmodule