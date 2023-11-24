`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    09:57:28 12/23/2016 
// Design Name: 
// Module Name:    matrix_disp 
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
//memory should be 384 bytes 24x128
//first 8 memory is the first culomn
//////////////////////////////////////////////////////////////////////////////////
module matrix_display(
input clk,
input [23:0]memory,//directly connect to the memory seccond output
						//memory second wea port should always be 0 for  fust reading
output reg [6:0]mem_add,//second port address firs 8 is first culumn and ...
output [23:0]rgb_pwm,
output reg [15:0]anode

//input lock
    );
	 initial anode = 16'h0001;
	 initial mem_add = 6'h00;
	 
	 reg [15:0]anode_temp=0;
	 reg clk_anode=0;
	 reg [10:0]anode_div=0;
	 reg [3:0]anode_address=0;
	 reg [2:0]local_add=0;
	 
	 reg pwm_en=0;
	 reg [3:0]a_temp=1;
	 reg start = 0;
	 reg last=0;
	 reg [23:0]ocr[7:0];
	 
//	 always @(posedge clk)
//	 begin
//		 anode_div <= anode_div +1;
//		 if(anode_div == 1874)//6400 ofr anode refresh 400 hz entire matrix
//			begin
//			clk_anode <= ~clk_anode;
//			anode_div <=0;
//			end
//	 end
	 
//	 always @(posedge clk_anode)
//		anode <= {anode_temp[14:0],anode_temp[15]};//rotate anode to left
	 
	 always @(posedge clk)
	 begin
		 anode_div <= anode_div +1;
		 if(anode_div == 1500 && clk_anode == 0)
			begin
			anode_temp <= anode;
			anode <=0;
			end
		if(anode_div == 1874 && clk_anode == 0) anode <= {anode_temp[14:0],anode_temp[15]};//rotate anode to left
		if(anode_div == 1874)//6400 for anode refresh 400 hz entire matrix
			begin
			clk_anode <= ~clk_anode;
			anode_div <=0;
			end
	 end

	 always @(posedge clk_anode)
	 begin
	 anode_address <= anode_address + 1 ;
	 
	 end
	 
	 always @(posedge clk)
	 begin
		 a_temp <= anode_address;
		 if( anode_address != a_temp) begin start <= 1;	pwm_en <= 0; end
		 if(start ==1) 
			begin
			 local_add <= local_add + 1;
			//mem_add <= {0,0,0,anode_address} + {0,0,0,0,local_add};
			mem_add <= mem_add + 1;
			ocr[(local_add-1)] <= memory;
			if(local_add == 7) begin pwm_en<= 1; start <= 0;last<=1; end
			end
		 if(last==1) begin ocr[7] <= memory;last<=0; end
	 end
	 
	 pwm_generator my_pwm (
    .clk(clk),
    .ocr1(ocr[0]), 	 
    .ocr2(ocr[1]), 
    .ocr3(ocr[2]), 
    .ocr4(ocr[3]), 
    .ocr5(ocr[4]), 
    .ocr6(ocr[5]), 
    .ocr7(ocr[6]), 
    .ocr8(ocr[7]), 
    .en(pwm_en), 
    .rgb1(rgb_pwm[2:0]), 
    .rgb2(rgb_pwm[5:3]), 
    .rgb3(rgb_pwm[8:6]), 
    .rgb4(rgb_pwm[11:9]), 
    .rgb5(rgb_pwm[14:12]), 
    .rgb6(rgb_pwm[17:15]), 
    .rgb7(rgb_pwm[20:18]), 
    .rgb8(rgb_pwm[23:21])
    );



endmodule
