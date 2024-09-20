module top (
  input clk,clrn,ps2_clk,ps2_data,
  output [7:0] seg0,seg1,seg2,seg3,seg4,seg5,seg6=8'hff,seg7=8'hff
);
  reg nextdata_n;
  reg ready;
  reg overflow;
  reg [7:0] data,tmp_data,out_data;
  reg [7:0] key_count;
  reg [7:0] ascii;

  reg [7:0] tmp_seg0,tmp_seg1,tmp_seg2,tmp_seg3;
  //四个状态
  reg [3:0] a=4'b0000;//初始状态，等待输入
  reg [3:0] b=4'b0001;//这个状态，是out_data写入
  reg [3:0] c=4'b0010;//将out_data的数据显示在数码管上
  reg [3:0] d=4'b0100;//等待下一次输入

  reg [3:0] state=a,next_state;
	//输出ready，overflow，tmp_data，key_count
  ps2_keyboard my_keyboard (clk,clrn,ps2_clk,ps2_data,tmp_data,ready,nextdata_n,overflow,key_count);
  ps2_to_ascii my_ps2_to_ascii (data,ascii);//键码转化为ascii

  bcd7seg my_seg1 (data[3:0],tmp_seg0);
  bcd7seg my_seg2 (data[7:4],tmp_seg1);
  bcd7seg my_seg3 (ascii[3:0],tmp_seg2);
  bcd7seg my_seg4 (ascii[7:4],tmp_seg3);
  bcd7seg my_seg5 (key_count[3:0],seg4);
  bcd7seg my_seg6 (key_count[7:4],seg5);

  //触发器更新seg
  Reg #(8,8'b11111111) my_reg1 (clk,state!=b,tmp_seg0,seg0,state==b); //初始状态
  Reg #(8,8'b11111111) my_reg2 (clk,state!=b,tmp_seg1,seg1,state==b); //out_data写入
  Reg #(8,8'b11111111) my_reg3 (clk,state!=b,tmp_seg2,seg2,state==b); //数据显示在数码管
  Reg #(8,8'b11111111) my_reg4 (clk,state!=b,tmp_seg3,seg3,state==b); //等待下一次输入，直接进入状态b

  
  always @(posedge clk or ps2_clk) begin//更新数据
    if (clrn) state<=a;
    else  state<=next_state;
    
  end

  
  always @(*) begin//状态机改变
    if(ready) begin
      case (state)
        a:next_state=b;
        b:next_state=(tmp_data==8'hf0)?c:b;//tmp_data==8'hf0表示松开了按键
        c:next_state=(tmp_data!=8'hf0)?d:c;//状态不为0的时候尽快到状态b更新数据
        d:next_state=(tmp_data!=8'hf0)?b:d;
        default:next_state=a;
      endcase
      out_data=tmp_data;
    end
  end

  assign data=(state==b)?out_data:8'b0;
endmodule

module ps2_to_ascii (input [7:0]x, output [7:0]y);
  reg [7:0] tmp;

  always @(*) begin
    case (x)
    8'h1c:tmp=8'h61;
    8'h32:tmp=8'h62;
    8'h21:tmp=8'h63;
    8'h23:tmp=8'h64;
    8'h24:tmp=8'h65;
    8'h2b:tmp=8'h66;
    8'h34:tmp=8'h67;
    8'h33:tmp=8'h68;
    8'h43:tmp=8'h69;
    8'h3b:tmp=8'h6a;
    8'h42:tmp=8'h6b;
    8'h4b:tmp=8'h6c;
    8'h3a:tmp=8'h6d;
    8'h31:tmp=8'h6e;
    8'h44:tmp=8'h6f;
    8'h4d:tmp=8'h70;
    8'h15:tmp=8'h71;
    8'h2d:tmp=8'h72;
    8'h1b:tmp=8'h73;
    8'h2c:tmp=8'h74;
    8'h3c:tmp=8'h75;
    8'h2a:tmp=8'h76;
    8'h1d:tmp=8'h77;
    8'h22:tmp=8'h78;
    8'h35:tmp=8'h79;
    8'h1a:tmp=8'h7a;
    8'hf0:tmp=0;
    8'h45:tmp=8'h30;
    8'h16:tmp=8'h31;
    8'h1e:tmp=8'h32;
    8'h26:tmp=8'h33;
    8'h25:tmp=8'h34;
    8'h2e:tmp=8'h35;
    8'h36:tmp=8'h36;
    8'h3d:tmp=8'h37;
    8'h3e:tmp=8'h38;
    8'h46:tmp=8'h39;
    default:tmp=0;
    endcase
  end

  assign y=tmp;
endmodule