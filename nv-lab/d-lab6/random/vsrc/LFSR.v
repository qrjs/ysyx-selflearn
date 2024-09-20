module LFSR(
    input wire clk,          // 时钟信号
    input wire rst_n,        // 低电平复位
    output reg [7:0] random
);

    wire feedback;
    assign feedback = random[4] ^ random[3] ^ random[2] ^ random[0];
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            random <= 8'b00000001;  // 初始状态为非零
        else
            // 右移并将 feedback 放入最高位
            random <= {feedback,random[7:1]};
    end

endmodule
