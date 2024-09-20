module top(
input [1:0]X0,X1,X2,X3,
input [1:0]Y,
output [1:0] F
);
always@(*)begin
    case(Y)
    2'b00:F=X0;
    2'b01:F=X1;
    2'b10:F=X2;
    2'b11:F=X3;
    default:F=2'b00;
    endcase

end   
endmodule 
