module mux21(
    input sel,
    input x0,x1,
    output reg f
);
always@(*)begin
    case(sel)
    1'b0:f=x0;
    1'b1:f=x1;
    default:f=x0;
    endcase
end