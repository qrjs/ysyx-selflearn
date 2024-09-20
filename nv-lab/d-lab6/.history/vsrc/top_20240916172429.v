module top(
    input wire clk,          // 时钟信号
    input wire rst_n,        // 低电平复位
    output reg [7:0] random  // 8 位伪随机数输出
);

    wire feedback;

    // 使用 XOR 计算反馈位，反馈多项式为 (x^8 + x^6 + x^5 + x^4 + 1)
    assign feedback = random[4] ^ random[5] ^ random[4] ^ random[3];

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            random <= 8'b00000001;  // 初始状态为非零
        else
            // 右移并将 feedback 放入最高位
            random <= {random[6:0], feedback};
    end

endmodule
