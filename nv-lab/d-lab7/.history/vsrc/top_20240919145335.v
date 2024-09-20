module top(
    input [7:0] din,
    input [2:0] shamt,
    input LR,
    input AL,
    output reg [7:0] dout
);
wire w0,w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14,w15,w16;
mux21 0_1(.sel(AL),.x0(0),.x1(din[7]),.f(w0));
mux41 1_1(.sel({LR,shamt[0]}),.x0(din[7]),.x1(w0),.x2(din[7]),.x3(din[6]),f(w1));
mux41 2_1(.sel({LR,shamt[0]}),.x0(din[6]),.x1(din[7]),.x2(din[6]),.x3(din[5]),f(w2));
mux41 3_1(.sel({LR,shamt[0]}),.x0(din[5]),.x1(din[6]),.x2(din[5]),.x3(din[4]),f(w3));
mux41 4_1(.sel({LR,shamt[0]}),.x0(din[4]),.x1(din[5]),.x2(din[4]),.x3(din[3]),f(w4));
mux41 5_1(.sel({LR,shamt[0]}),.x0(din[3]),.x1(din[4]),.x2(din[3]),.x3(din[2]),f(w5));
mux41 6_1(.sel({LR,shamt[0]}),.x0(din[2]),.x1(din[3]),.x2(din[2]),.x3(din[1]),f(w6));
mux41 7_1(.sel({LR,shamt[0]}),.x0(din[1]),.x1(din[2]),.x2(din[1]),.x3(din[0]),f(w7));
mux41 8_1(.sel({LR,shamt[0]}),.x0(din[0]),.x1(din[1]),.x2(din[0]),.x3(0),f(w8));

mux41 1_2(.sel(LR,shamt[1]),.x0(w1),.x1(w0),.x2(w1),.x3(din[5]),.f)