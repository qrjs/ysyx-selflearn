module top (
	input [1:0] x0,x1,x2,x3,
	input [1:0] y,
	output reg [1:0] f
);
always@(*)begin
	case(y)
		2'b00:f=x0;
		2'b01:f=x1;
		2'b10:f=x2;
		2'b11:f=x3;
		default:f=x0;
	endcase
end
endmodule

