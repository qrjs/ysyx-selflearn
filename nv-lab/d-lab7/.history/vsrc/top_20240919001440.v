module top(
    input [7:0] din,
    input [2:0] shamt,
    input LR,
    input AL,
    output reg [7:0] dout
);
mux21 0_1(.sel())
mux41 1_1(.sel({LR,shamt[0]}),.x0(din[7]),.x1())