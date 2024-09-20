module top(
    input [7:0] din,
    input [2:0] shamt,
    input LR,
    input AL,
    output reg [7:0] dout
);
mux21 0_1(.sel(AL),.x0(0),.x1(din[7]));
mux41 1_1(.sel({LR,shamt[0]}),.x0(din[7]),.x1())