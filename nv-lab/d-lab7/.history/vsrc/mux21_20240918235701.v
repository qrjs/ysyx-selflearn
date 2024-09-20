module mux21(
    input sel,
    input x0,x1,
    output reg f
);
always@(*)begin
    case(sel)
    1'b0:f=
end