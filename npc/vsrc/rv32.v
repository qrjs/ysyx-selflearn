`include "/home/jrq/ysyx-workbench/npc/vsrc/define.v"
module PC(
  input  wire           clk,
  input  wire           rst,
  input  wire           m1,
  input  wire           m2,
  input  wire [`Reg_Bus] result,
  input  wire [`Reg_Bus] imm32,
  output wire [`Reg_Bus] PCadd4,
  output reg  [`Reg_Bus] pc /* verilator public */
);

  wire [`Reg_Bus] npc;
  wire [`Reg_Bus] npc_temp;
  wire [`Reg_Bus] PCaddIMM32;
  
  assign PCadd4     = pc + 4;
  assign PCaddIMM32 = pc + imm32;

  always @(posedge clk) begin
    if(rst == `RST_VAL)
      pc <= `RESET_VECTOR;
    else if(clk)
      pc <= npc;
    else
      pc <= pc;
  end

  // MUX1 module
  MuxKey #(2, 1, `Bit_Width) i1(npc, (m1 & result[0]), {
      1'b0, npc_temp,
      1'b1, PCaddIMM32}

  );

  // MUX2 module
  MuxKey #(2, 1, `Bit_Width) i2(npc_temp, (m2), {
      `MUX2_PCadd4, PCadd4,
      `MUX2_result, result}
  );

endmodule




module rv32(
  input  wire           clk,
  input  wire           rst
);
  /* verilator lint_off UNOPTFLAT */
  wire[`Reg_Bus]   pc/* verilator public */;  
  /* verilator lint_off UNOPTFLAT */
  wire[`Reg_Bus]   inst/* verilator public */;   
  wire[4:0]       rs1;
  wire[4:0]       rs2;
  wire[4:0]       rd;
  wire[2:0]       fun3;
  wire[6:0]       fun7;      
  wire[`TYPE_BUS] IType;      //inst type
  wire            reg_wen;    //RegFile write enable
  wire            mem_wen;    //mem write enable
  wire            mem_ren;    //mem read  enable
  wire[7:0]       wmask;      //mem write mask
  wire[2:0]       rmask;      //mem read  mask
  wire            m1;         //mux1 sel
  wire            m2;         //mux2 sel
  wire            m3;         //mux3 sel
  wire            m4;         //mux4 sel
  wire[1:0]       m5;         //mux5 sel
  wire[`Alu_S]  alus;       //alu operation type, like add, sub...
  wire[`Reg_Bus]   PCadd4;     //pc + 4
  wire[`Reg_Bus]   result;     //alu operation result
  wire[`Reg_Bus]   reg_in;     //regisrer file input value
  wire[`Reg_Bus]   src1;       //rs1 value
  wire[`Reg_Bus]   src2;       //rs2 value
  wire[`Reg_Bus]   imm32;      //extended 32 bit immediate
  wire[`Reg_Bus]   num1;       //alu operation number1       
  wire[`Reg_Bus]   num2;       //alu operation number2
  wire[`Reg_Bus]   mem_rdata;  //mem read data


  // PC module
  PC PC_inst(
    .clk      (clk),
    .rst      (rst),
    .m1       (m1),
    .m2       (m2),
    .result   (result),
    .imm32    (imm32),
    .PCadd4   (PCadd4),
    .pc       (pc)   
  );

  // mem module
  mem mem_inst(
    .clk      (clk),  
    .mem_wen  (mem_wen),  
    .wmask    (wmask),
    .waddr    (result),
    .wdata    (src2),
    .mem_ren  (mem_ren),  
    .rmask    (rmask),
    .raddr    (result),
    .inst_addr(pc),
    .rdata    (mem_rdata),
    .inst_data(inst)
  );

  // Decode Unit module
  decode decode_unit_inst(
    .inst      (inst),
    .rd_11_7   (rd),
    .rs1_19_15 (rs1),
    .rs2_24_20 (rs2),
    .fun3_14_12(fun3),
    .fun7_31_25(fun7),
    .IType     (IType),
    .alus      (alus),
    .reg_wen   (reg_wen),    
    .mem_wen   (mem_wen),
    .mem_ren   (mem_ren),  
    .wmask     (wmask),
    .rmask     (rmask),
    .m1        (m1),    
    .m2        (m2),    
    .m3        (m3),   
    .m4        (m4),   
    .m5        (m5)
  );

  // Register File module
  register_file register_file_inst(
    .clk      (clk),
    .rst      (rst),
    .reg_wen  (reg_wen),
    .rs1      (rs1),
    .rs2      (rs2),
    .rd       (rd),
    .reg_in   (reg_in),
    .src1     (src1),
    .src2     (src2)
  );

  // Imm Extend module
  imm_extend imm_extend_inst(
    .rs1   (rs1),
    .rs2   (rs2),
    .rd    (rd),
    .fun3(fun3),
    .fun7(fun7),
    .IType (IType),
    .imm32 (imm32)
  );

  // MUX3 module
  MuxKey #(2, 1, `Bit_Width) i3(num2, m3, {
      `MUX3_src2,  src2,
      `MUX3_imm32, imm32}
  );

  // MUX4 module
  MuxKey #(2, 1, `Bit_Width) i4(num1, m4, {
      `MUX4_pc,   pc,
      `MUX4_src1, src1}
  );

  // MUX5 module
  MuxKey #(4, 2, `Bit_Width) i5(reg_in, m5, {
      `MUX5_PCadd4, PCadd4,
      `MUX5_memdat, mem_rdata,
      `MUX5_result, result,
      `MUX5_IDLE,   32'hdeadbeaf}       //uae
  );
  
  // ALU module
  alu alu_inst(
    .alus  (alus),
    .src1  (num1),
    .src2  (num2),
    .result(result)
  );
endmodule

