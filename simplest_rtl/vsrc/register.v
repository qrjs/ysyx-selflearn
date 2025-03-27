module register(
    input  wire           clk1_flag,  // 更改为分频时钟输入
    input  wire           rst,
    input  wire [4:0]     rs1,
    input  wire [4:0]     rs2,
    input  wire [4:0]     rd,
    input  wire [`Reg_Bus] result,
    output wire [`Reg_Bus] src1,
    output wire [`Reg_Bus] src2
);

    integer i;
    reg[`Reg_Bus] regs[`Reg_Num-1 : 0];

    // 寄存器写入逻辑，使用clk1_flag的上升沿
    always @(posedge clk1_flag or posedge rst) begin
        if(rst == `RST_VAL) begin
            for(i=0; i<32; i=i+1) begin
                regs[i] <= `RegRstVal;  
            end
        end else begin
            if (rd != `Reg0)
                regs[rd] <= result; 
        end
    end

    // 读逻辑保持不变
    assign src1 = (rs1 == `Reg0) ? `Reg0_VAL : regs[rs1];
    assign src2 = (rs2 == `Reg0) ? `Reg0_VAL : regs[rs2];
   
endmodule