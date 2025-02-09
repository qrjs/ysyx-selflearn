`include "/root/ysyx-workbench/simplest_rtl/vsrc/define.v"
module register(
    input  wire           clk,
    input  wire           rst,
    input  wire           clk1_flag,
    input  wire [4:0]     rs1,
    input  wire [4:0]     rs2,
    input  wire [4:0]     rd,
    input  wire [`Reg_Bus] result,
    output wire [`Reg_Bus] src1,
    output wire [`Reg_Bus] src2
);

    integer i;
    reg[`Reg_Bus] regs[`Reg_Num-1 : 0];
    wire         en;

    assign en = (clk1_flag == 1'b1);

    //wire register
    always @(posedge clk) begin
        if(rst == `RST_VAL) begin
            for(i=0; i<32; i=i+1) begin
                regs[i] <= `RegRstVal;  
            end
        end else if((en == 1'b1) && (rd != `Reg0))
            regs[rd] <= result; 
        else
            regs[rd] <= regs[rd]; 
    end

    //read register
    assign src1 = (rs1 == `Reg0) ? `Reg0_VAL : regs[rs1];
    assign src2 = (rs2 == `Reg0) ? `Reg0_VAL : regs[rs2];
   
endmodule