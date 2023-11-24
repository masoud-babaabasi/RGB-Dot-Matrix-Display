`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:40:36 01/01/2017 
// Design Name: 
// Module Name:    ps2_receiver 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

module ps2_receiver
   (
    input clk,
    input ps2d, ps2c,
    output reg rx_done_tick = 0,
    output reg [7:0]key
   );

   // signal declaration
   reg [3:0] filter_reg;
   wire [3:0] filter_next;
   reg f_ps2c_reg;
   wire f_ps2c_next;
	
	reg f1_ps2d;
	reg f2_ps2d;

   wire fall_edge;
	reg end_byte = 0;
	
	reg [10:0]temp = 11'h7FF;
	reg [7:0]keys[1:0];
	reg [2:0]key_cnt = 0;
	reg [7:0]ps2_data;

   always @(posedge clk)
   begin
		filter_reg <= filter_next;
		f_ps2c_reg <= f_ps2c_next;
   end

   assign filter_next = {ps2c, filter_reg[3:1]};
   assign f_ps2c_next = (filter_reg==4'b1111) ? 1'b1 :
                        (filter_reg==4'b0000) ? 1'b0 :
                         f_ps2c_reg;
   assign fall_edge = f_ps2c_reg & ~f_ps2c_next;
	
	
	always @(posedge clk)
   begin
		if(fall_edge)
			temp <= {f2_ps2d,temp[10:1]};
		
		if({temp[10],temp[0]}==2'b10) begin
			temp <= 11'h7FF;
			ps2_data <= temp[8:1];
			end_byte <= 1;
		end
		else begin
			end_byte <= 0;
		end
	end
	
	always @(posedge clk)
	begin
		if(end_byte) begin
			keys[1] <= keys[0];
			keys[0] <= ps2_data;
		end
		
		if(keys[1] == 8'hf0) begin
			rx_done_tick <= 1;
			keys[1] <= 0;
			key <= keys[0];
		end
		else begin
			rx_done_tick <= 0;
		end
		
	end
	
	always @(posedge clk)
	begin
		f1_ps2d <= ps2d;
		f2_ps2d <= f1_ps2d;
	end

endmodule
