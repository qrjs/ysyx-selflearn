module mux41(
    input [1:0] sel,
    input  x0,x1,x2,x3,
    output reg  f
);
always@(*)begin
    case(sel)
    2'b00:f=x0;
    2'b01:f=x1;
    2'b10:f=x2;
    2'b11:f=x3;
    default:f=x0;
    endcase
end
endmodule
