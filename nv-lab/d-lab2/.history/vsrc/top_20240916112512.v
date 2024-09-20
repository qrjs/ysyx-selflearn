module top(
    input [7:0]x,
    input en,
    output reg vx,
    output reg [2:0] y,
    output reg [6:0] seg0
);
always @(*) begin
    if(en)begin
    vb=1;
    casex(x)
    8'b0000_0000:begin y=3'b000;vb=

    end
end
    
endmodule //top

