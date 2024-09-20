module top(
    input [7:0] din,
    input [2:0] shamt,
    input LR,
    input AL,
    output reg [7:0] dout
);
wire w0,w1,w2,w3;
mux21 0_1(.sel(AL),.x0(0),.x1(din[7]),.f(w1));
mux41 1_1(.sel({LR,shamt[0]}),.x0(din[7]),.x1(w1),.x2(din[7]),.x3(din[6]),f())