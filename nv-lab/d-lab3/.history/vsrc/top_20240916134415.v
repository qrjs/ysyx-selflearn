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
        alu_f=4'b0;temp=4'b0;less=0;over_f=0;
        zero_f=0;cin_f=0;
        casez(alu_ch)
        
    end
endmodule //top
