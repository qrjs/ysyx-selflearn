module top(
    input [3:0] a, b,
    input [2:0] alu_ch,
    output reg [3:0] alu_f,
    output reg zero_f, over_f, cout_f,
    output reg [3:0] temp,
    output reg less
);
    reg [3:0] xb;

    always @(*) begin
        alu_f = 4'b0;
        temp = 4'b0;
        less = 0;
        over_f = 0;
        zero_f = 0;
        cout_f = 0;
        xb = 4'b0; // Initialize xb to avoid latch inference

        casez (alu_ch)
            3'b00z: begin
                xb = b ^ {4{alu_ch[0]}}; // XOR b with a mask based on alu_ch[0]
                {cout_f, alu_f} = xb + a + {3'b0, alu_ch[0]};
                over_f = (a[3] == xb[3]) && (a[3] != alu_f[3]);
                zero_f = ~(|alu_f);
            end
            3'b011: alu_f = a & b;
            3'b100: alu_f = a | b;
            3'b101: alu_f = a ^ b;
            3'b110: begin
                xb = b ^ 4'b1111; // XOR b with all ones for 2's complement
                {cout_f, temp} = xb + a + 4'b0001;
                over_f = (a[3] == xb[3]) && (temp[3] != a[3]);
                zero_f = ~(|temp);
               if (a[3] != b[3]) begin
              // a[3]为1表示a是负数，b是正数，less应为1
              less = a[3];
             end else begin
            // 如果符号位相同，直接比较a和b的大小
            less = (a < b);
            end
            3'b111: begin
                xb = b ^ 4'b1111; // XOR b with all ones for 2's complement
                {cout_f, temp} = xb + a + 4'b0001;
                over_f = (a[3] == xb[3]) && (temp[3] != a[3]);
                zero_f = ~(|temp);
                if (zero_f) 
                    alu_f = 4'b0001;
                else 
                    alu_f = 4'b0000;
            end
            default: alu_f = 4'b0000;
        endcase
    end
endmodule
