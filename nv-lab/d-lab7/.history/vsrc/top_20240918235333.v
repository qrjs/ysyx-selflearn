module top(
    input [7:0] din,
    input [2:0] shamt,
    input LR,
    input AL,
    output reg [7:0] dout
);
mux41 1_1(.sel({LR,shamt[]}))