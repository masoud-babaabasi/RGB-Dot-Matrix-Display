`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:34:46 12/22/2016 
// Design Name: 
// Module Name:    pwm_generator 
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
module pwm_generator(
input clk,
input [23:0]ocr1,
input [23:0]ocr2,
input [23:0]ocr3,
input [23:0]ocr4,
input [23:0]ocr5,
input [23:0]ocr6,
input [23:0]ocr7,
input [23:0]ocr8,
//input [7:0]ocr,
//input reset,
input en,
//output [2:0]pwm
output [2:0]rgb1,
output [2:0]rgb2,
output [2:0]rgb3,
output [2:0]rgb4,
output [2:0]rgb5,
output [2:0]rgb6,
output [2:0]rgb7,
output [2:0]rgb8
    );
	 reg [7:0] counter=0;
	 reg [4:0]fr_div=0;
	 reg clk_main=0;
	 reg [7:0]bufer_ocr;
	 wire bufer_pwm;
	 
	/* reg [2:0]rgb11;
	 reg [2:0]rgb22;
	 reg [2:0]rgb33;
	 reg [2:0]rgb44;
	 reg [2:0]rgb55;
	 reg [2:0]rgb66;
	 reg [2:0]rgb77;
	 reg [2:0]rgb88;*/
	 
	 always @(posedge clk)//frequency division by 25
	 begin
	 fr_div <= fr_div +1'b1 ;
	 if(fr_div == 24)
		begin
		clk_main <= ~clk_main;
		end
	 end
	 
	 always @(posedge clk/*clk_main*/ /*or negedge reset*/)
	 begin
	 if(en /*& reset*/)
		counter <= counter + 1'b1;
	 else counter <= 0; 
	 end
	/*assign bufer_pwm = (counter <= bufer_ocr && en == 1 && bufer_ocr != 0 ) ? 1'b1 : 1'b0 ;

	always @(posedge clk)
	begin
	case(fr_div)
		0: begin bufer_ocr <= ocr1[7:0];	end
		1: begin bufer_ocr <= ocr1[15:8];	rgb11[0] <= bufer_pwm;	end
		2: begin bufer_ocr <= ocr1[23:16];	rgb11[1] <= bufer_pwm;	end
		
		3: begin bufer_ocr <= ocr2[7:0];	 	rgb11[2] <= bufer_pwm;   end
		4: begin bufer_ocr <= ocr2[15:8];	rgb22[0] <= bufer_pwm;	end
		5: begin bufer_ocr <= ocr2[23:16];	rgb22[1] <= bufer_pwm;	end
		
		6: begin bufer_ocr <= ocr3[7:0];	 	rgb22[2] <= bufer_pwm;   end
		7: begin bufer_ocr <= ocr3[15:8];	rgb33[0] <= bufer_pwm;	end
		8: begin bufer_ocr <= ocr3[23:16];	rgb33[1] <= bufer_pwm;	end
		
		9: begin bufer_ocr <= ocr4[7:0];	 	rgb33[2] <= bufer_pwm;   end
		10: begin bufer_ocr <= ocr4[15:8];	rgb44[0] <= bufer_pwm;	end
		11: begin bufer_ocr <= ocr4[23:16];	rgb44[1] <= bufer_pwm;	end
		
		12: begin bufer_ocr <= ocr5[7:0];	rgb44[2] <= bufer_pwm;   end
		13: begin bufer_ocr <= ocr5[15:8];	rgb55[0] <= bufer_pwm;	end
		14: begin bufer_ocr <= ocr5[23:16];	rgb55[1] <= bufer_pwm;	end
		
		15: begin bufer_ocr <= ocr6[7:0];	rgb55[2] <= bufer_pwm;   end
		16: begin bufer_ocr <= ocr6[15:8];	rgb66[0] <= bufer_pwm;	end
		17: begin bufer_ocr <= ocr6[23:16];	rgb66[1] <= bufer_pwm;	end
		
		18: begin bufer_ocr <= ocr7[7:0];	rgb66[2] <= bufer_pwm;   end
		19: begin bufer_ocr <= ocr7[15:8];	rgb77[0] <= bufer_pwm;	end
		20: begin bufer_ocr <= ocr7[23:16];	rgb77[1] <= bufer_pwm;	end
		
		21: begin bufer_ocr <= ocr8[7:0];	rgb77[2] <= bufer_pwm;   end
		22: begin bufer_ocr <= ocr8[15:8];	rgb88[0] <= bufer_pwm;	end
		23: begin bufer_ocr <= ocr8[23:16];	rgb88[1] <= bufer_pwm;	end
		
		24: begin rgb88[2] <= bufer_pwm;	end
		endcase
	end
	
	always @(posedge clk_main)
	begin
	rgb1[0] <= rgb11[0];
	rgb1[1] <= rgb11[1];
	rgb1[2] <= rgb11[2];
	
	rgb2[0] <= rgb22[0];
	rgb2[1] <= rgb22[1];
	rgb2[2] <= rgb22[2];
	
	rgb3[0] <= rgb33[0];
	rgb3[1] <= rgb33[1];
	rgb3[2] <= rgb33[2];
	
	rgb4[0] <= rgb44[0];
	rgb4[1] <= rgb44[1];
	rgb4[2] <= rgb44[2];
	
	rgb5[0] <= rgb55[0];
	rgb5[1] <= rgb55[1];
	rgb5[2] <= rgb55[2];
	
	rgb6[0] <= rgb66[0];
	rgb6[1] <= rgb66[1];
	rgb6[2] <= rgb66[2];
	
	rgb7[0] <= rgb77[0];
	rgb7[1] <= rgb77[1];
	rgb7[2] <= rgb77[2];
	
	rgb8[0] <= rgb88[0];
	rgb8[1] <= rgb88[1];
	rgb8[2] <= rgb88[2];
	end*/
	//assign pwm = (counter <= ocr && en == 1 && ocr != 0 ) ? 1'b1 : 1'b0 ; 
	//assign pwm[0] = (counter <= ocr[7:0] && en == 1 && ocr[7:0] != 0 ) ? 1'b1 : 1'b0 ; 
	assign rgb1[0] = (counter <= ocr1[7:0] && en == 1 && ocr1[7:0] != 0 ) ? 1'b0 : 1'b1; 
	assign rgb1[1] = (counter <= ocr1[15:8] && en == 1 && ocr1[15:8] != 0 ) ? 1'b0 : 1'b1; 
	assign rgb1[2] = (counter <= ocr1[23:16] && en == 1 && ocr1[23:16] != 0 ) ? 1'b0 : 1'b1;   
	
	assign rgb2[0] = (counter <= ocr2[7:0] && en == 1 && ocr2[7:0] != 0 ) ? 1'b0 : 1'b1; 
	assign rgb2[1] = (counter <= ocr2[15:8] && en == 1 && ocr2[15:8] != 0 ) ? 1'b0 : 1'b1;   
	assign rgb2[2] = (counter <= ocr2[23:16] && en == 1 && ocr2[23:16] != 0 ) ? 1'b0 : 1'b1; 
	
	assign rgb3[0] = (counter <= ocr3[7:0] && en == 1 && ocr3[7:0] != 0 ) ? 1'b0 : 1'b1;   
	assign rgb3[1] = (counter <= ocr3[15:8] && en == 1 && ocr3[15:8] != 0 ) ? 1'b0 : 1'b1;    
	assign rgb3[2] = (counter <= ocr3[23:16] && en == 1 && ocr3[23:16] != 0 ) ? 1'b0 : 1'b1; 
	
	assign rgb4[0] = (counter <= ocr4[7:0] && en == 1 && ocr4[7:0] != 0 ) ? 1'b0 : 1'b1;  
	assign rgb4[1] = (counter <= ocr4[15:8] && en == 1 && ocr4[15:8] != 0 ) ?1'b0 : 1'b1;   
	assign rgb4[2] = (counter <= ocr4[23:16] && en == 1 && ocr4[23:16] != 0 ) ?1'b0 : 1'b1;  
	
	assign rgb5[0] = (counter <= ocr5[7:0] && en == 1 && ocr5[7:0] != 0 ) ? 1'b0 : 1'b1;   
	assign rgb5[1] = (counter <= ocr5[15:8] && en == 1 && ocr5[15:8] != 0 ) ? 1'b0 : 1'b1;  
	assign rgb5[2] = (counter <= ocr5[23:16] && en == 1 && ocr5[23:16] != 0 ) ? 1'b0 : 1'b1; 
	
	assign rgb6[0] = (counter <= ocr6[7:0] && en == 1 && ocr6[7:0] != 0 ) ? 1'b0 : 1'b1;  
	assign rgb6[1] = (counter <= ocr6[15:8] && en == 1 && ocr6[15:8] != 0 )? 1'b0 : 1'b1;    
	assign rgb6[2] = (counter <= ocr6[23:16] && en == 1 && ocr6[23:16] != 0 ) ? 1'b0 : 1'b1;  
	
	assign rgb7[0] = (counter <= ocr7[7:0] && en == 1 && ocr7[7:0] != 0 ) ? 1'b0 : 1'b1;  
	assign rgb7[1] = (counter <= ocr7[15:8] && en == 1 && ocr7[15:8] != 0 ) ? 1'b0 : 1'b1;  
	assign rgb7[2] = (counter <= ocr7[23:16] && en == 1 && ocr7[23:16] != 0 ) ? 1'b0 : 1'b1;   
	
	assign rgb8[0] = (counter <= ocr8[7:0] && en == 1 && ocr8[7:0] != 0 ) ? 1'b0 : 1'b1;  
	assign rgb8[1] = (counter <= ocr8[15:8] && en == 1 && ocr8[15:8] != 0 )  ? 1'b0 : 1'b1;  
	assign rgb8[2] = (counter <= ocr8[23:16] && en == 1 && ocr8[23:16] != 0 ) ? 1'b0 : 1'b1;    
	
	
endmodule
