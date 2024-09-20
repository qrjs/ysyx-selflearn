module top(
    input [3:0] a,b,
    input [2:0] alu_ch
    output reg [3:0] alu_f,
    output reg zero_f,over_f,cout_f,
    output reg [3:0] temp,
    output reg less
);
    reg [3:0] xb;
    always@(*)begin
        alu_f=4'b0;temp=4'b0;less=0;over_f=0;
        zero_f=0;cin_f=0;
        casez(alu_ch)
        3'b00z:begin
            xb=b^{4{alu_ch[0]}};
        {cout_f,alu_f}=xb+a+{3'b0,alu_ch[0]};
        over_f=(a[3]==xb[3]) && (a[3]!=alu_f[3]);
        zero_f=~(|alu_f);
        end
    end
    3'b011:alu_f=a & b;
    3'b100:alu_f=a | b;
    3'b101:alu_f=a ^ b;
    3'b110:begin
    xb=b^ 4'b1111;
    {cout_f,temp}=xb+a+4'b0001;
    of=(a[3]==xb[3]) && (temp[3]!=a[3]);
    zero_f=~(|temp);
    less=cout_f^temp[3];
    
    end
endmodule //top
