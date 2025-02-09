`include "/root/ysyx-workbench/simplest_rtl/vsrc/define.v"


module clk_count(
  input  wire clk,
  input  wire rst,
  output wire clk1_flag,
  output wire clk2_flag
);

  reg [1:0] clk_cnt;
  always @(posedge clk) begin
    if(rst == `RST_VAL)
      clk_cnt <= 2'd0;
    else if(clk_cnt == 2'd2)
      clk_cnt <= 2'd0;
    else
      clk_cnt <= clk_cnt + 2'd1;
  end

  assign clk1_flag = (clk_cnt == 2'd1);
  assign clk2_flag = (clk_cnt == 2'd2);

endmodule



module PC(
  input  wire           clk,
  input  wire           rst,
  input  wire           clk2_flag,
  output reg  [`Reg_Bus] pc
);

  always @(posedge clk) begin
    if(rst == `RST_VAL)
      pc <= `RESET_VECTOR;
    else if(clk2_flag == 1'b1)
      pc <= pc + `PC_INCREMENT;
  end

endmodule



module top(
  input  wire           clk,
  input  wire           rst,
  input  wire [`Reg_Bus] inst,
  output wire [`Reg_Bus] pc
);
  
  wire            clk1_flag;
  wire            clk2_flag;
  wire [4:0]      rs1;
  wire [4:0]      rs2;
  wire [4:0]      rd;
  wire [6:0]      funct7;
  wire[`TYPE_BUS] type4;      //inst type
  wire            mux1;         //mux1 sel
  wire[`AlucBus]  alus;       //alu operation type, like add, sub...
  wire[`Reg_Bus]   result;     //alu operation result
  wire[`Reg_Bus]   src1;       //rs1 value
  wire[`Reg_Bus]   src2;       //rs2 value
  wire[`Reg_Bus]   imm;        //extended 32 bit immediate
  wire[`Reg_Bus]   num1;       //alu operation number1       
  wire[`Reg_Bus]   num2;       //alu operation number2
  assign num1 = src1;


  // clk_count module
  clk_count clk_count_inst(
    .clk      (clk),
    .rst      (rst),
    .clk1_flag(clk1_flag),
    .clk2_flag(clk2_flag)
  );

  // PC module
  PC PC_inst(
    .clk      (clk),
    .rst      (rst),
    .clk2_flag(clk2_flag),
    .pc       (pc)   
  );

  // Control Unit module
  control_unit control_unit_inst(
    .inst      (inst),
    .rd        (rd),
    .rs1_19_15 (rs1),
    .rs2_24_20 (rs2),
    .fun7      (funct7),
    .type1     (type4),
    .alus     (alus),
    .mux1        (mux1)    
  );

  // Register File module
  register register_file_inst(
    .clk      (clk),
    .rst      (rst),
    .clk1_flag(clk1_flag),
    .rs1      (rs1),
    .rs2      (rs2),
    .rd       (rd),
    .result   (result),
    .src1     (src1),
    .src2     (src2)
  );

  // Imm Extend module
  imm_extend imm_extend_inst(
    .rs2   (rs2),
    .funct7(funct7),
    .type3 (type4),
    .imm32 (imm)
  );

  // MUX1 module
  MuxKey #(2, 1, 32) i1(num2, mux1, {
      `MUX1_src2, src2,
      `MUX1_imm,  imm}
  );


  // ALU module
  alu alu_inst(
    .alus  (alus),
    .num1  (num1),
    .num2  (num2),
    .result(result)
  );
endmodule

