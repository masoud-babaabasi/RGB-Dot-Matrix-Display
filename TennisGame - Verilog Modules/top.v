`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:22:29 12/23/2016 
// Design Name: 
// Module Name:    top 
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
module top(
	input clk_in,
	output [15:0]anode,
	output [23:0]rgb_pwm,
	output wire buz,
	input RX,
	output TX,
	input ps2d,
	input ps2c
   );

	//Instant Clock Generator
	wire clk_24M,clk_100M;
	
	Clock_genarator dcm_block
   (// Clock in ports
	.CLK_IN_24M(clk_in),      // IN
   // Clock out ports
   .CLK_OUT_24M(clk_24M),     // OUT
   .CLK_OUT_100M(clk_100M),     // OUT
   // Status and control signals
   .RESET(1'b0),// IN
	//.RESET(GPO3_reset_RAMwea[1]),// IN
   .LOCKED(LOCKED)// OUT
	);      
	//**********************************************************************************************************************//
	
	//Instant ps2_reciver
	wire keyboard_tick;
	wire [7:0]ps2key_GPI1;	
	
	ps2_receiver ps2_keyboard (
    .clk(clk_100M), 
    .ps2d(ps2d), 
    .ps2c(ps2c), 
    .rx_done_tick(keyboard_tick), 
    .key(ps2key_GPI1)
    );

	//**********************************************************************************************************************//

	//Instant RAM
	wire GPO3_RAMwea;
	wire [6:0] GPO1_RAM_write_addr;	
	wire [23:0] GPO2_RAM_write_din;	
	wire [6:0] RAM_read_addr;	
	wire [23:0] RAM_read_dout;	
	
	memory Data_RAM (
   .clka(clk_100M), // input clka
	.wea(GPO3_RAMwea), // input [0 : 0] wea
   .addra(GPO1_RAM_write_addr), // input [6 : 0] addra
	.dina(GPO2_RAM_write_din), // input [23 : 0] dina
   .clkb(clk_24M), // input clkb
   .addrb(RAM_read_addr), // input [6 : 0] addrb
   .doutb(RAM_read_dout) // output [23 : 0] doutb
	);
	//**********************************************************************************************************************//
	
	//Instant Matrix_Display
	matrix_display display (
    .clk(clk_24M), 
    .memory(RAM_read_dout), 
    .mem_add(RAM_read_addr), 
    .rgb_pwm(rgb_pwm), 
    .anode(anode)
    );
	//**********************************************************************************************************************//
	
	//Instant MicroBlaze Microcontroller
	wire [7:0] GPO4_buzzer;
	
	MicroBlaze microcontroller (
	.Clk(clk_100M), // input Clk
   .Reset(1'b0), // input Reset
   .UART_Rx(RX), // input UART_Rx
   .UART_Tx(TX), // output UART_Tx
   .FIT1_Interrupt(FIT1_Interrupt), // output FIT1_Interrupt
	.FIT1_Toggle(FIT1_Toggle), // output FIT1_Toggle
	.FIT2_Interrupt(FIT2_Interrupt), // output FIT2_Interrupt
	.FIT2_Toggle(FIT2_Toggle), // output FIT2_Toggle
   .GPO1(GPO1_RAM_write_addr), // output [6 : 0] GPO1		//to memory RAM_write_addr
   .GPO2(GPO2_RAM_write_din), // output [23 : 0] GPO2		//to memory RAM_write_din
   .GPO3(GPO3_RAMwea), // output [0 : 0] GPO3		//to memory RAM_wea
   .GPO4(GPO4_buzzer), // output [7 : 0] GPO4					//to buzzer module
   .GPI1(ps2key_GPI1), // input [7 : 0] GPI1					//from ps2_keyboard
   .GPI1_Interrupt(GPI1_Interrupt), // output GPI1_Interrupt
   .INTC_Interrupt(keyboard_tick), // input [0 : 0] INTC_Interrupt	//from ps2_keyboard key Interrupt 
   .INTC_IRQ(INTC_IRQ) // output INTC_IRQ
	);
	//**********************************************************************************************************************//
	
	//Instant Buzzer Module
	buzer buzzer (
	.clk(clk_24M), 
   .en(GPO4_buzzer[7]), 
   .note(GPO4_buzzer[6:0]), 
   .buz(buz)
    );
	//**********************************************************************************************************************//

endmodule
