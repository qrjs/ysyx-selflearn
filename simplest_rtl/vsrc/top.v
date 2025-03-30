`include "/home/jrq/ysyx-workbench/simplest_rtl/vsrc/define.v"


module clk_count(
  input  wire clk,
  input  wire rst,
  output wire clk1_flag,  // 分频时钟1（50%占空比）
  output wire clk2_flag   // 分频时钟2（50%占空比）
);

  // 二分频逻辑（周期=2T，占空比50%）
  reg clk_div1;
  always @(posedge clk) begin
    if (rst == `RST_VAL)
      clk_div1 <= 1'b0;
    else
      clk_div1 <= ~clk_div1;  // 每个时钟周期翻转一次
  end

  // 四分频逻辑（周期=4T，占空比50%）
  reg [1:0] clk_div2_cnt;
  reg clk_div2;
  always @(posedge clk) begin
    if (rst == `RST_VAL) begin
      clk_div2_cnt <= 2'd0;
      clk_div2     <= 1'b0;
    end else begin
      clk_div2_cnt <= clk_div2_cnt + 1;
      if (clk_div2_cnt == 2'd1)  // 每2个周期翻转一次
        clk_div2 <= ~clk_div2;
    end
  end

  assign clk1_flag = clk_div1;  // 二分频时钟（50%占空比）
  assign clk2_flag = clk_div2;  // 四分频时钟（50%占空比）

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
    else 
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

