`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:10:38 12/27/2016 
// Design Name: 
// Module Name:    buzer 
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
module buzer(
input clk,
input en,
input [6:0]note,
output reg buz=0
    );
	reg [18:0]pre_scale;
	reg [18:0]counter=0;
	always @*
	begin
		case(note)
		0: pre_scale = 387096;//31 Hz
		1: pre_scale = 365370;//32 Hz
		2: pre_scale = 344864;//34 Hz
		3: pre_scale = 325508;//36 Hz
		4: pre_scale = 307238;//39 Hz
		5: pre_scale = 289994;//41 Hz
		6: pre_scale = 273718;//43 Hz
		7: pre_scale = 258356;//46 Hz
		8: pre_scale = 243855;//49 Hz
		9: pre_scale = 230169;//52 Hz
		10: pre_scale = 217250;//55 Hz
		11: pre_scale = 205057;//58 Hz
		12: pre_scale = 193548;//62 Hz
		13: pre_scale = 182685;//65 Hz
		14: pre_scale = 172432;//69 Hz
		15: pre_scale = 162754;//73 Hz
		16: pre_scale = 153619;//78 Hz
		17: pre_scale = 144997;//82 Hz
		18: pre_scale = 136859;//87 Hz
		19: pre_scale = 129178;//92 Hz
		20: pre_scale = 121927;//98 Hz
		21: pre_scale = 115084;//104 Hz
		22: pre_scale = 108625;//110 Hz
		23: pre_scale = 102528;//117 Hz
		24: pre_scale = 96774;//124 Hz
		25: pre_scale = 91342;//131 Hz
		26: pre_scale = 86216;//139 Hz
		27: pre_scale = 81377;//147 Hz
		28: pre_scale = 76809;//156 Hz
		29: pre_scale = 72498;//165 Hz
		30: pre_scale = 68429;//175 Hz
		31: pre_scale = 64589;//185 Hz
		32: pre_scale = 60963;//196 Hz
		33: pre_scale = 57542;//208 Hz
		34: pre_scale = 54312;//220 Hz
		35: pre_scale = 51264;//234 Hz
		36: pre_scale = 48387;//248 Hz
		37: pre_scale = 45671;//262 Hz
		38: pre_scale = 43108;//278 Hz
		39: pre_scale = 40688;//294 Hz
		40: pre_scale = 38404;//312 Hz
		41: pre_scale = 36249;//331 Hz
		42: pre_scale = 34214;//350 Hz
		43: pre_scale = 32294;//371 Hz
		44: pre_scale = 30481;//393 Hz
		45: pre_scale = 28771;//417 Hz
		46: pre_scale = 27156;//441 Hz
		47: pre_scale = 25632;//468 Hz
		48: pre_scale = 24193;//496 Hz
		49: pre_scale = 22835;//525 Hz
		50: pre_scale = 21554;//556 Hz
		51: pre_scale = 20344;//589 Hz
		52: pre_scale = 19202;//624 Hz
		53: pre_scale = 18124;//662 Hz
		54: pre_scale = 17107;//701 Hz
		55: pre_scale = 16147;//743 Hz
		56: pre_scale = 15240;//787 Hz
		57: pre_scale = 14385;//834 Hz
		58: pre_scale = 13578;//883 Hz
		59: pre_scale = 12816;//936 Hz
		60: pre_scale = 12096;//992 Hz
		61: pre_scale = 11417;//1050 Hz
		62: pre_scale = 10777;//1113 Hz
		63: pre_scale = 10172;//1179 Hz
		64: pre_scale = 9601;//1249 Hz
		65: pre_scale = 9062;//1324 Hz
		66: pre_scale = 8553;//1402 Hz
		67: pre_scale = 8073;//1486 Hz
		68: pre_scale = 7620;//1574 Hz
		69: pre_scale = 7192;//1668 Hz
		70: pre_scale = 6789;//1767 Hz
		71: pre_scale = 6408;//1872 Hz
		72: pre_scale = 6048;//1984 Hz
		73: pre_scale = 5708;//2101 Hz
		74: pre_scale = 5388;//2226 Hz
		75: pre_scale = 5086;//2359 Hz
		76: pre_scale = 4800;//2499 Hz
		77: pre_scale = 4531;//2648 Hz
		78: pre_scale = 4276;//2805 Hz
		79: pre_scale = 4036;//2972 Hz
		80: pre_scale = 3810;//3149 Hz
		81: pre_scale = 3596;//3336 Hz
		82: pre_scale = 3394;//3535 Hz
		83: pre_scale = 3204;//3745 Hz
		84: pre_scale = 3024;//3968 Hz
		85: pre_scale = 2854;//4203 Hz
		86: pre_scale = 2694;//4453 Hz
		87: pre_scale = 2543;//4718 Hz
		88: pre_scale = 2400;//4999 Hz
		default: pre_scale = 11417;//1050 Hz
		endcase
	end
	
	always @(posedge clk)
	begin 
	if(en)
	begin
	counter <= counter + 1'b1 ;
	if(counter == pre_scale)
		begin
		counter <= 0;
		buz <= ~buz;
		end
	end
	else buz <= 0;
	end

endmodule
