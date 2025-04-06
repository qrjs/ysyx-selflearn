`include "/home/jrq/ysyx-workbench/npc/vsrc/define.v"

module register_file(
    input  wire           clk,
    input  wire           rst,
    input  wire           reg_wen,
    input  wire [4:0]     rs1,
    input  wire [4:0]     rs2,
    input  wire [4:0]     rd,
    input  wire [`Reg_Bus] reg_in,
    output wire [`Reg_Bus] src1,
    output wire [`Reg_Bus] src2
);
     reg[`Reg_Bus] regs[`Bit_Width-1 : 0]/* verilator public */;
    integer i;
    
    //wire register
    always @(posedge clk) begin
        if(rst == `RST_VAL) begin
            for(i=0; i<`Reg_Num; i=i+1) begin
                regs[i] <= `RegRstVal;  
            end
        end else if((reg_wen == 1'b1) && (rd != `Reg0))
            regs[rd] <= reg_in; 
        else
            regs[rd] <= regs[rd]; 
    end

    //read register
    assign src1 = (rs1 == `Reg0) ? `Reg0_VAL : regs[rs1];
    assign src2 = (rs2 == `Reg0) ? `Reg0_VAL : regs[rs2];
   
endmodule