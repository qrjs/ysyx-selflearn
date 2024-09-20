module top (
    input wire clk,   // 按钮作为时钟输入
    input wire rst_n,        // 复位按钮（低电平复位）
    output wire [6:0] seg1,  // 第一位数码管
    output wire [6:0] seg2   // 第二位数码管
);

    wire [7:0] random_num;

    // 实例化 LFSR
    LFSR_8bit lfsr_inst (
        .clk(clk),
        .rst_n(rst_n),
        .random(random_num)
    );

    // 显示高 4 位到第一位数码管
    hex_to_7segment display1 (
        .hex(random_num[7:4]),
        .seg(seg1)
    );

    // 显示低 4 位到第二位数码管
    hex_to_7segment display2 (
        .hex(random_num[3:0]),
        .seg(seg2)
    );

endmodule
