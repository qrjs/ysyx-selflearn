`include "/home/jrq/ysyx-workbench/npc/vsrc/define.v"

module mem(
    input  wire           clk,
    input  wire           mem_wen,
    input  wire [7:0]     wmask,
    input  wire [`Reg_Bus] waddr,
    input  wire [`Reg_Bus] wdata,
    input  wire           mem_ren,
    input  wire [2:0]     rmask,
    input  wire [`Reg_Bus] raddr,
    input  wire [`Reg_Bus] inst_addr,
    output reg  [`Reg_Bus] rdata,
    // output reg  [`Reg_Bus] inst_data
    output wire  [`Reg_Bus] inst_data /* verilator public_flat */
);
    
    import "DPI-C" function int  pmem_read(input int raddr);
    import "DPI-C" function void pmem_write(input int waddr, input int wdata, input byte wmask);
    import "DPI-C" function void ebreak(input int station, input int inst, input byte unit);

    reg  [`Reg_Bus] rdata_temp;

    assign inst_data = pmem_read(inst_addr);

    always @(*) begin
        if(mem_wen) begin // 有写请求时
            pmem_write(waddr, wdata, wmask);
        end
    end


    always @(*) begin
        if(mem_ren) begin // 有读数据请求时
            rdata_temp = pmem_read(raddr);
        end else begin
            rdata_temp = 32'h0;
        end
    end


    // rdata_temp -> rdata
    always @(*) begin
        case (rmask)
            `LoadBU:  rdata = {24'd0, rdata_temp[7:0]};
            `LoadHU:  rdata = {16'd0, rdata_temp[15:0]};
            `LoadB:   rdata = {{24{rdata_temp[7]}}, rdata_temp[7:0]};
            `LoadH:   rdata = {{16{rdata_temp[15]}}, rdata_temp[15:0]};
            `LoadW:   rdata = rdata_temp;
            default:  begin
                        rdata = 32'hdeadbeaf;
                        ebreak(`ABORT, 32'hdeadbeaf, `Unit_MEM);
                      end
        endcase
    end

endmodule