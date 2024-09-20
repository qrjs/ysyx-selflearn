module bcd7seg(
	input [3:0] b,
	output reg [6:0] h
	);
	always@(*)
	begin
		case(b)
			4'b0000: h=7'b0000_001;
			4'b0001: h=7'b1001_111;
			4'b0010: h=7'b0010_010;
			4'b0011: h=7'b0000_110;
			4'b0100: h=7'b100_011;
			4'b0101: h=7'b0100_100;
			4'b0110: h=7'b0100_000;
			4'b0111: h=7'b0001_111;
			4'b1000: h=7'b0000_000;
			4'b1001: h=7'b0000_100;
			4'b1010: h=7'b0001_000;
			4'b1011: h=7'b1100_000;
			4'b1100: h=7'b0110_001;
			4'b1101: h=7'b1000_010;
			4'b1110: h=7'b0110_000;
			4'b1111: h=7'b0111_000;
		endcase
	end
endmodule
