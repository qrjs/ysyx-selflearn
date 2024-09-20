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
    8'b0000_0000:begin y=3'b000;vb=0;end
    8'b0000_0001:y=3'b000;
    8'b0000_001?:y=3'b001;
    8'b0000_01??:y=3'b010;
    8'b0000_1???:y=3'b011;
    8'b0001_????:y=3'b100;
    8'b001?_????:y=3'b101;
    8'b01??_????:y=3'b110;
    8'b1

    end
end
    
endmodule //top

