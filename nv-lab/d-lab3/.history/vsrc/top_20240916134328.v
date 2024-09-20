module top(
    input [3:0] a,b,
    input [2:0] alu_ch
    output reg [3:0] alu_f,
    output reg zero_f,over_f,cin_f,
    output reg [3:0] temp,
    output reg less
);
    reg [3:0] xb;
    always@(*)begin
        alu_f=4'b0;temp=4'b0;less
    end
endmodule //top
