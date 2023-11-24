// Engineer: Milad Katiraie
// Group:Masoud Babaabasi		Ahmad Hamzeei		Milad Katiraie
// Create Date:    12/23/2016
// Project Name:	Tennis Game
// Description: This Project is write for FPGA Lesson for show RGB Module Ability
//

//main include
#include <stdio.h>
#include "platform.h"
//Timer control
#include "xparameters.h" // add
#include "xiomodule.h" // add
//User include
#include "tennisgame.h"
#include "stdlib.h"

//****************************************************************************************************************//

//Defines
//Keyboard key
#define rocket1_up 		0x1D	//W
#define rocket1_down 	0x1B	//S
#define rocket1_left 	0x1C	//A
#define rocket1_right 	0x23	//D
#define rocket1_hiden 	0x15	//Q
#define rocket1_magic 	0x24	//E
//
#define rocket2_up 		0x75	//Arrow Up
#define rocket2_down 	0x72	//Arrow Down
#define rocket2_left 	0x6B	//Arrow  Left
#define rocket2_right 	0x74	//Arrow Right
#define rocket2_hiden 	0x70	//KP 0
#define rocket2_magic 	0x69	//Kp 1
//Ball Direction
#define down_left		0x00
#define down_right		0x01
#define up_left			0x02
#define up_right		0x03
//Ball Color
#define ball_color_default 0xffa500		//orange

//****************************************************************************************************************//

//****************************************************************************************************************//

//Global variables
XIOModule io;
//Color
volatile unsigned int background_color = 0x13e962;		//green:00a000
volatile unsigned int rocket1_color = 0x0000ff;		//blue
volatile unsigned int rocket2_color = 0xff0000;		//red
volatile unsigned int ball_color = ball_color_default;		//orange
//Rockets Position
volatile u8 rocket1_x = 1;		//x on lowest pixel
volatile u8 rocket1_y = 3;		//y on lowest pixel
volatile u8 rocket2_x = 14;		//x on lowest pixel
volatile u8 rocket2_y = 3;		//y on lowest pixel
//Ball Position
volatile u8 ball_x = 8;			//default state
volatile u8 ball_y = 3;			//default state
volatile u8 ball_direction = up_left;		//Ball direction state
//player magic
volatile u8 rocket1_specialpoint = 0;
volatile u8 rocket2_specialpoint = 0;
//Ball speed
volatile u8 ballmotion_start_flag = 0;	//0:disable		1:enable
volatile u8 ball_speed = 20;			//max speed_counter set speed
volatile u8 ball_speed_counter = 0;
//hint variable for change rocket color
volatile u8 hint_count = 0;
//player points
volatile u8 player1_point = 0;
volatile u8 player2_point = 0;
//finish game flag
volatile u8 finish_flag = 0;
//game start delay flag
volatile u8 gamestart_flag = 0;
//delay variable
volatile unsigned int delay_count = 0;
volatile u8 delay_flag = 0;
//hiden ball special move variable
volatile u8 hiden_ball_flag = 0;
volatile u8 hiden_ball_time = 0;
//ball sound flag
volatile u8 ball_tick_flag = 0;
//Page Flash flag
volatile u8 page_flash_flag = 0;

//****************************************************************************************************************//

//functions

void setpoint(u8 x , u8 y , unsigned int color){
	//function for set color to point
	//color R G B
	u8 addr = (x*8) + y;
	XIOModule_DiscreteWrite(&io, 1, addr);		//set addr
	XIOModule_DiscreteWrite(&io, 3, 1);			//write enable
	XIOModule_DiscreteWrite(&io, 2, color);		//set Data
	XIOModule_DiscreteWrite(&io, 3, 0);			//write disable
}

void delay(unsigned int delay){
	//set delay with 1msecond accuracy
	delay_flag = 1;		//initial state
	delay_count = 0;	//initial state
	while(delay_count<delay);
	delay_flag = 0;
}

int random_num(){
	int num = rand()%4;
	return num;
}
//*****************************************************************************//
//Page Layout function
void game_start_page(){
	//start game page
	u8 x = 0;
	u8 y = 0;
	for(x = 1; x < 15 ; x++){
		for(y = 0; y < 8 ; y++){
			if(x == rocket1_x && (y == rocket1_y || y == (rocket1_y + 1))){
				setpoint(x , y , rocket1_color);		//position rocket1
			}
			else if(x == rocket2_x && (y == rocket2_y || y == (rocket2_y + 1))){
				setpoint(x , y , rocket2_color);		//position rocket2
			}
			else if(x == ball_x && y == ball_y ){
				setpoint(x , y , ball_color);		//position ball
			}
			else{
				setpoint(x , y , background_color);		//Background
			}
		}
	}
}

void start_game(){
	//start gmae shows
	u8 x , y , k;
	unsigned int addr;
	//delay for show coe
	delay(3000);	//delay for 3seconds
	//clear page
	for(x = 0 ; x < 16 ; x++){
		for(y = 0 ; y<8 ; y++){
			setpoint(x , y , 0);		//clear
		}
	}
	//show name with music
	//Show Masoud Babaabasi name
	for(k = 0 ; k < 67 ; k++){
		//play music
		if(k < 67){
		    XIOModule_DiscreteWrite(&io, 4, (0x80|underworld_melody[k]));		//play music
		}
		//show window
		for(x = 0 ; x < 16 ; x++){
			for(y = 0 ; y<8 ; y++){
				addr = (k*8)+(x*8)+y;
				setpoint(x , y , masoud_name[addr]);		///show Masoud Babaabasi
			}
		}
		delay(74);	//delay for 0.074seconds
		//not play note
		if(k < 57){
			XIOModule_DiscreteWrite(&io, 4, 0);		//dont play music
		}
		delay(75);	//delay for 0.075seconds
	}
	delay(250);	//delay for 0.25seconds
	for(x = 0 ; x < 16 ; x++){
		for(y = 0 ; y<8 ; y++){
			addr = (k*8)+(x*8)+y;
			setpoint(x , y , 0);		//clear
		}
	}
	XIOModule_DiscreteWrite(&io, 4, 0);		//dont play music
	delay(250);	//delay for 0.25seconds
	//Show Ahmad Hamzeei name
	for(k = 0 ; k < 67 ; k++){
		//play music
		if(k < 57){
		    XIOModule_DiscreteWrite(&io, 4, (0x80|underworld_melody[k]));		//play music
		}
		//show window
		for(x = 0 ; x < 16 ; x++){
			for(y = 0 ; y<8 ; y++){
				addr = (k*8)+(x*8)+y;
				setpoint(x , y , ahmad_name[addr]);		///show Ahmad Hamzeei
			}
		}
		delay(74);	//delay for 0.074seconds
		//not play note
		if(k < 57){
			XIOModule_DiscreteWrite(&io, 4, 0);		//dont play music
		}
		delay(75);	//delay for 0.075seconds
	}
	delay(250);	//delay for 0.25seconds
	for(x = 0 ; x < 16 ; x++){
		for(y = 0 ; y<8 ; y++){
			addr = (k*8)+(x*8)+y;
			setpoint(x , y , 0);		//clear
		}
	}
	XIOModule_DiscreteWrite(&io, 4, 0);		//dont play music
	delay(250);	//delay for 0.25seconds
	//Show Milad Katiraie name
	for(k = 0 ; k < 67 ; k++){
		//play music
		if(k < 57){
		    XIOModule_DiscreteWrite(&io, 4, (0x80|underworld_melody[k]));		//play music
		}
		//show window
		for(x = 0 ; x < 16 ; x++){
			for(y = 0 ; y<8 ; y++){
				addr = (k*8)+(x*8)+y;
				setpoint(x , y , milad_name[addr]);		///show Milad Katiraie
			}
		}
		delay(74);	//delay for 0.074seconds
		//not play note
		if(k < 57){
			XIOModule_DiscreteWrite(&io, 4, 0);		//dont play music
		}
		delay(75);	//delay for 0.075seconds
	}
	delay(250);	//delay for 0.25seconds
	for(x = 0 ; x < 16 ; x++){
		for(y = 0 ; y<8 ; y++){
			addr = (k*8)+(x*8)+y;
			setpoint(x , y , 0);		//clear
		}
	}
	XIOModule_DiscreteWrite(&io, 4, 0);		//dont play music
	delay(250);	//delay for 0.25seconds
	//*********************************************************//
	game_start_page();
    delay(5000);	//delay for 5seconds
    ballmotion_start_flag = 1;		//start ball_motion
}

void refresh_Column_Point(){
	//refresh Column Point after restart
	//clean Column Points
	u8 i = 0;
	u8 specialpoint_show ;
	for(i = 0 ; i < 8 ; i++){
		setpoint(0 , i , 0x000000);
		setpoint(15 , i , 0x000000);
	}
	//set Player points
	for(i = 0 ; i < player1_point ; i++){
		setpoint(0 , i , 0x0000ff);
	}
	for(i = 0 ; i < player2_point ; i++){
		setpoint(15 , i , 0xff0000);
	}
	//set player special move point for player vriable valid amount
	for(i = 0 ; i < rocket1_specialpoint ; i++){
		specialpoint_show = 7 - i;			//7 = 8-1
		if(specialpoint_show > (player1_point - 1)){
			setpoint(0 , specialpoint_show , 0x00ff00);		//show special point:color green
		}
		else{
			setpoint(0 , specialpoint_show , 0x00ffff);		//show special point:color blue and green
		}
	}
	for(i = 0 ; i < rocket2_specialpoint ; i++){
		specialpoint_show = 7 - i;			//7 = 8-1
		if(specialpoint_show > (player2_point - 1)){
			setpoint(15 , specialpoint_show , 0x00ff00);	//show special point:color green
		}
		else{
			setpoint(15 , specialpoint_show , 0xffff00);	//show special point:color red and green
		}
	}
}

void page_flash(){
	//Flash Dot Matrix
	u8 x;
	u8 y;
	//Clear
	for(x = 0; x < 16 ; x++){
		for(y = 0; y < 8 ; y++){
			setpoint(x , y , 0x000000);
		}
	}
	delay(250);		//delay for 0.25 second
	//flash
	for(x = 0; x < 16 ; x++){
		for(y = 0; y < 8 ; y++){
			setpoint(x , y , 0xffffff);
		}
	}
	delay(250);		//delay for 0.25 second
	//Clear
	for(x = 0; x < 16 ; x++){
		for(y = 0; y < 8 ; y++){
			setpoint(x , y , 0x000000);
		}
	}
	delay(250);		//delay for 0.25 second

	//refresh page
	game_start_page();

	//refresh Column Point	for other player show
	refresh_Column_Point();
}

void restart_game(){
	//restart game after one player get 1 point
	//set game default values
	rocket1_color = 0x0000ff;
	rocket2_color = 0xff0000;
	ball_color = ball_color_default;	//orange
	//Rockets Position
	rocket1_x = 1;		//x on lowest pixel
	rocket1_y = 3;		//y on lowest pixel
	rocket2_x = 14;		//x on lowest pixel
	rocket2_y = 3;		//y on lowest pixel
	//Ball Position
	ball_x = 6 + random_num();			//random position
	ball_y = 2 + random_num() ;			//random position
	//B all Direction
	ball_direction = random_num();		//Ball direction random
	//player magic
	rocket1_specialpoint = 0;
	rocket2_specialpoint = 0;
	//Ball speed
	ball_speed = 20;			//max speed_counter set speed
	ball_speed_counter = 0;
	//hint variable for change rocket color
	hint_count = 0;
	//****************************************************************//
	//restart game
	ballmotion_start_flag = 0;		//stop ball motion
	game_start_page();
	refresh_Column_Point();
	//set flag for delay 4 second
	gamestart_flag = 1;
}

void win_player(unsigned char player){
	//finished game
	u8 x = 0;
	u8 y = 0;
	u8 addr = 0;
	//
	ballmotion_start_flag = 0;		//stop ball motion
	//
	for(x = 0; x < 16 ; x++){
		for(y = 0; y < 8 ; y++){
			addr = x*8 + y;
			if(player == 1){
				setpoint(x , y , player1_win[addr]);
			}
			else if(player == 2){
				setpoint(x , y , player2_win[addr]);
			}
		}
	}
	finish_flag = 1;		//finish game
}

void finish_game(){
	u8 x;
	u8 y;
	unsigned int i = 0;
	//finish game
	for(i = 0 ; i<79 ; i++){
		XIOModule_DiscreteWrite(&io, 4, (0x80|underworld_melody[i]));		//play music
		delay(60);
		XIOModule_DiscreteWrite(&io, 4, 0);		//play music
		delay(90);
	}
	//empty RAM
	for(x = 0; x < 16 ; x++){
		for(y = 0; y < 8 ; y++){
			setpoint(x , y , 0x000000);
		}
	}
	delay(5000);	//delay for 5seconds
	//set player point 0 for start
	player1_point = 0;
	player2_point = 0;
	//restart game
	restart_game();
	//set flag 0 for next time
	finish_flag = 0;
}
//*****************************************************************************//
//function for Rockets motion
void  rocket1_motion(unsigned char satate){
	//function for rocket1 motion
	if(satate == 'l'){
		//set background color to last rocket1 position
		setpoint(rocket1_x , rocket1_y , background_color);
		setpoint(rocket1_x , (rocket1_y + 1) , background_color);
	}
	if(satate == 'n'){
		//set color to new rocket1 position
		setpoint(rocket1_x , rocket1_y , rocket1_color);
		setpoint(rocket1_x , (rocket1_y + 1) , rocket1_color);
	}
}

void  rocket2_motion(unsigned char satate){
	//function for rocket2 motion
	if(satate == 'l'){
		//set background color to last rocket1 position
		setpoint(rocket2_x , rocket2_y , background_color);
		setpoint(rocket2_x , (rocket2_y + 1) , background_color);
	}
	if(satate == 'n'){
		//set color to new rocket1 position
		setpoint(rocket2_x , rocket2_y , rocket2_color);
		setpoint(rocket2_x , (rocket2_y + 1) , rocket2_color);
	}
}
//*****************************************************************************//
//set point and set special move point for player
void player_point(unsigned char player){
	//set point for player
	if(player == 1){
		//set 1 point for player1
		if(player1_point<8){
			player1_point = player1_point + 1;		//set point
			setpoint(0 , (player1_point - 1) , 0x0000ff);		//show point:color blue
			restart_game();		//restart game for resume game
		}
		else{
			//finish game
			win_player(1);
		}
	}
	else if(player == 2){
		//set 1 point for player2
		if(player2_point<8){
			player2_point = player2_point + 1;		//set point
			setpoint(15 , (player2_point - 1) , 0xff0000);		//show point:color red
			restart_game();		//restart game for resume game
		}
		else{
			//finish game
			win_player(2);
		}
	}
}

void rocket_special_point(unsigned char player){
	//rockets special points
	if(player == 1){
		if(rocket1_specialpoint < 8){
			u8 point_show = 0;
			//
			rocket1_specialpoint = rocket1_specialpoint +1;		//increase special point
			//set special point on Column Points from up
			point_show = 8 - rocket1_specialpoint;
			if(point_show > (player1_point - 1) ){
				setpoint(0 , point_show , 0x00ff00);		//show special point:color green
			}
			else{
				setpoint(0 , point_show , 0x00ffff);		//show special point:color blue and green
			}

		}
	}
	//
	if(player == 2){
		if(rocket2_specialpoint < 8){
			u8 point_show = 0;
			//
			rocket2_specialpoint = rocket2_specialpoint +1;		//increase special point
			//set special point on Column Points from up
			point_show = 8 - rocket2_specialpoint;
			if(point_show > (player2_point - 1) ){
				setpoint(15 , point_show , 0x00ff00);		//show special point:color green
			}
			else{
				setpoint(15 , point_show , 0xffff00);		//show special point:color red and green
			}
		}
	}
}

//*****************************************************************************//
//function for special move
void  hidenball(unsigned char player){
	//HidenBall for few pixel
	if(hiden_ball_flag == 0){		//if ball is hiden can hide again
		if(player == 1 && rocket1_specialpoint > 0){
			//set hiden_ball_time
			if((ball_x + rocket1_specialpoint) < 13){
				hiden_ball_time = rocket1_specialpoint;
			}
			else{
				hiden_ball_time = 13 - ball_x;
			}
			//hiden ball
			ball_color = background_color + (background_color & 0x1f1f1f);
			hiden_ball_flag = 1;
			//refresh page
			game_start_page();
			//set special move point to 0
			rocket1_specialpoint = 0;
			//refresh Column Point	for other player show
			refresh_Column_Point();
		}
		//*******************************************************************//
		if(player == 2 && rocket2_specialpoint > 0){
			//set hiden_ball_time
			if(2<(ball_x - rocket2_specialpoint)){
				hiden_ball_time = rocket2_specialpoint;
			}
			else{
				hiden_ball_time = ball_x - 2;
			}

			//hiden ball
			ball_color = background_color + (background_color & 0x1f1f1f);
			hiden_ball_flag = 1;
			//refresh page
			game_start_page();
			//set special move point to 0
			rocket2_specialpoint = 0;
			//refresh Column Point	for other player show
			refresh_Column_Point();
		}
	}
}

void  magic_motion(unsigned char player){
	//Keep away ball for few pixel
	//Magic motion move variable
	u8 magic_ball_movement;

	if(player == 1){
		//set magic_ball_movement
		if((ball_x + rocket1_specialpoint) < 12){
			magic_ball_movement = rocket1_specialpoint;
		}
		else{
			magic_ball_movement = 12 - ball_x;
		}
		//}
		//ball movement
		ball_x = ball_x + magic_ball_movement;

		//flash page if Special Point is 7 or 8
		if(rocket1_specialpoint == 7 || rocket1_specialpoint == 8){
			//set special move point to 0
			rocket1_specialpoint = 0;
			page_flash_flag = 1;
		}
		else{
			//set special move point to 0
			rocket1_specialpoint = 0;
			//refresh page
			game_start_page();
			//refresh Column Point	for other player show
			refresh_Column_Point();
		}

	}
	//*****************************************************************//
	if(player == 2){
		//set magic_ball_movement
		if(3<(ball_x - rocket2_specialpoint)){
			magic_ball_movement = rocket2_specialpoint;
		}
		else{
			magic_ball_movement = ball_x - 3;
		}

		//ball movement
		ball_x = ball_x - magic_ball_movement;

		//flash page if Special Point is 7 or 8
		if(rocket2_specialpoint == 7 || rocket2_specialpoint == 8){
			//set special move point to 0
			rocket2_specialpoint = 0;
			page_flash_flag = 1;
		}
		else{
			//set special move point to 0
			rocket2_specialpoint = 0;
			//refresh page
			game_start_page();
			//refresh Column Point	for other player show
			refresh_Column_Point();
		}
		//set special move point to 0
		rocket2_specialpoint = 0;
	}
}
//*****************************************************************************//
//function to change rocket color and ball speed
void increase_ball_speed(){
	//increase ball speed
	//interval is 0.05 second
	if(ball_speed > 1){
		ball_speed = ball_speed - 1;
	}
	else{
		ball_speed = 1;		//minimum speed:0.1 second
	}
}

void hint(unsigned char player){
	//change rocket color and play sound
	if(ball_tick_flag == 0){
		XIOModule_DiscreteWrite(&io, 4, (0x80 | 0x26));		//tick
		ball_tick_flag = 2;
	}
	//
	hint_count = hint_count + 1;
	if(hint_count < 20){
		if(player == 1){
			//player1 color default is blue
			rocket1_color = rocket1_color + 0x191400 - 0x000019;	//R+25	G+20	B-25
		}
		if(player == 2){
			//player1 color default is blue
			rocket2_color = rocket2_color + 0x001402;	//R		G+20	B+2
		}
	}
	else{
		//No red no blue only Luteous
		rocket1_color = 0xffd700;	//Gold
		rocket2_color = 0xffd700;	//Gold
		//ball color change
		ball_color = 0xf4a460;	//Sandy Brown
	}
}
//*****************************************************************************//
//function for ball direction and ball motion
void ball_motion(){
	//set ball position
	setpoint(ball_x , ball_y , background_color);		//set background color to last position
	//set new position
	switch (ball_direction){
		case(down_left):{
			ball_y = ball_y - 1;
			ball_x = ball_x - 1;
			break;
		}
		case(down_right):{
			ball_y = ball_y - 1;
			ball_x = ball_x + 1;
			break;
		}
		case(up_left):{
			ball_y = ball_y + 1;
			ball_x = ball_x - 1;
			break;
		}
		case(up_right):{
			ball_y = ball_y + 1;
			ball_x = ball_x + 1;
			break;
		}
		default:{
			ball_y = ball_y ;
			ball_x = ball_x ;
			break;
		}
	}
	//set ball to new position
	setpoint(ball_x , ball_y , ball_color);		//set ball to new position
}

void ball_status(){
	//set ball status(Direction) then call ball_motion
	//if ball on up or down row
	if(ball_y == 0){
		ball_direction = ball_direction + 2;		//equal change direction
	}
	if(ball_y == 7){
		ball_direction = ball_direction - 2;		//equal change direction
	}
	//***********************************************************************//
	//Rocket1 Hit
	if(ball_x == (rocket1_x + 1) && (ball_y == rocket1_y || ball_y == (rocket1_y + 1))){
		if(ball_direction == up_left){
			ball_direction = up_right;
		}
		if(ball_direction == down_left){
			ball_direction = down_right;
		}
		increase_ball_speed();		//increase ball speed
		hint(1);		//call hint function for change rocket1 color
		rocket_special_point(1);		//call special point function for increase player special move point
	}
	//Dealing with rocket edge
	else if(ball_x == (rocket1_x + 1) && ball_y == (rocket1_y - 1) && ball_direction == up_left){
		ball_direction = down_right;
		hint(1);		//call hint function for change rocket1 color
	}
	else if(ball_x == (rocket1_x + 1) && ball_y == (rocket1_y + 1 + 1) && ball_direction == down_left){
		ball_direction = up_right;
		hint(1);		//call hint function for change rocket1 color
	}
	//***********************************************************************//
	//Rocket2 Hit
	if(ball_x == (rocket2_x - 1) && (ball_y == rocket2_y || ball_y == (rocket2_y + 1))){
		if(ball_direction == up_right){
			ball_direction = up_left;
		}
		if(ball_direction == down_right){
			ball_direction = down_left;
		}
		increase_ball_speed();		//increase ball speed
		hint(2);		//call hint function for change rocket2 color
		rocket_special_point(2);		//call special point function for increase player special move point
	}
	else if(ball_x == (rocket2_x - 1) && ball_y == (rocket2_y - 1) && ball_direction == up_right){
		ball_direction = down_left;
		hint(2);		//call hint function for change rocket2 color
	}
	else if(ball_x == (rocket2_x - 1) && ball_y == (rocket2_y + 1 + 1) && ball_direction == down_right){
		ball_direction = up_left;
		hint(2);		//call hint function for change rocket2 color
	}
	//***********************************************************************//
	//Special Position
	if(ball_x == (rocket1_x + 1) && ball_y == (rocket1_y - 1) && ball_y == 0 && ball_direction == down_right){
		ball_direction = up_right;
		hint(1);		//call hint function for change rocket2 color
	}
	if(ball_x == (rocket1_x + 1) && ball_y == (rocket1_y + 1 + 1) && ball_y == 7 && ball_direction == up_right){
		ball_direction = down_right;
		hint(1);		//call hint function for change rocket1 color
	}
	if(ball_x == (rocket2_x - 1) && ball_y == (rocket2_y - 1) && ball_y == 0 && ball_direction == down_left){
		ball_direction = up_left;
		hint(2);		//call hint function for change rocket2 color
	}
	if(ball_x == (rocket2_x - 1) && ball_y == (rocket2_y + 1 + 1) && ball_y == 7 && ball_direction == up_left){
		ball_direction = down_left;
		hint(2);		//call hint function for change rocket2 color
	}
	//***********************************************************************//
	//refresh ball color after hide ball
	if(hiden_ball_flag == 1){
		if(hiden_ball_time > 0){
			hiden_ball_time = hiden_ball_time -1;
		}
		else{
			//finish hide ball time
			ball_color = ball_color_default;
			hiden_ball_flag = 0;		//enable hiden for next time
		}
	}
	//***********************************************************************//
	//Hitting the edges of the forbidden
	if(ball_x == 1){
		//player2 win 1 point
		player_point(2);
	}
	if(ball_x == 14){
		//player1 win 1 point
		player_point(1);
	}
	//call ball_motion for set changes
	if(ballmotion_start_flag == 1){
		ball_motion();
	}
}

//****************************************************************************************************************//

//timer1 handler
void timerTick1(void* ref) {
	//Timer Tick
	if(ballmotion_start_flag == 1){
		if(ball_speed_counter < ball_speed){
			ball_speed_counter++;
		}
		else{
			ball_speed_counter = 0;
			ball_status();
		}
	}

	//ball tick flag
	if(ball_tick_flag > 1){
		ball_tick_flag = ball_tick_flag -1;
	}
	else{
		XIOModule_DiscreteWrite(&io, 4, 0);		//tick
		ball_tick_flag = 0;			//for next hint
	}
}
//timer2 handler
void timerTick2(void* ref) {
	//Timer Tick
	//delay counter
	if(delay_flag == 1){
		delay_count ++ ;
	}
}
//External Interrupt
void IntHandler(void *ref) {
	//Handelling interrupt for Keyboard Key
	u8 keyboard_key = XIOModule_DiscreteRead(&io, 1);
	switch (keyboard_key){
		//Rocket1
		case rocket1_up:{
			if(rocket1_y < 6){
				//7-1 = 6
				rocket1_motion('l');	//change background color
				rocket1_y = rocket1_y + 1;
				rocket1_motion('n');	//set new rockect point
			}
			else
				rocket1_y = rocket1_y;
			break;

		}
		case rocket1_down:{
			if(rocket1_y > 0){
				rocket1_motion('l');	//change background color
				rocket1_y = rocket1_y - 1;
				rocket1_motion('n');	//set new rockect point
			}
			else
				rocket1_y = rocket1_y;
			break;

		}
		case rocket1_left:{
			if(rocket1_x > 1){
				rocket1_motion('l');	//change background color
				rocket1_x = rocket1_x - 1;
				rocket1_motion('n');	//set new rockect point
				}
			else
				rocket1_x = rocket1_x;
			break;
		}
		case rocket1_right:{
			if(rocket1_x < 4){
				rocket1_motion('l');	//change background color
				rocket1_x = rocket1_x + 1;
				rocket1_motion('n');	//set new rockect point
				}
			else
				rocket1_x = rocket1_x;
			break;
		}
		case rocket1_hiden:	hidenball(1);	//1 for player1
							break;
		case rocket1_magic:	magic_motion(1);	//1 for player1
							break;
		//******************************************************************//
		case rocket2_up:{
			if(rocket2_y < 6){
				//7-1 = 6
				rocket2_motion('l');	//change background color
				rocket2_y = rocket2_y + 1;
				rocket2_motion('n');	//set new rockect point
			}
			else
				rocket2_y = rocket2_y;
			break;

		}
		case rocket2_down:{
			if(rocket2_y > 0){
				rocket2_motion('l');	//change background color
				rocket2_y = rocket2_y - 1;
				rocket2_motion('n');	//set new rockect point
			}
			else
				rocket2_y = rocket2_y;
			break;

		}
		case rocket2_left:{
			if(rocket2_x > 11){
				rocket2_motion('l');	//change background color
				rocket2_x = rocket2_x - 1;
				rocket2_motion('n');	//set new rockect point
				}
			else
				rocket2_x = rocket2_x;
			break;
		}
		case rocket2_right:{
			if(rocket2_x < 14){
				rocket2_motion('l');	//change background color
				rocket2_x = rocket2_x + 1;
				rocket2_motion('n');	//set new rockect point
				}
			else
				rocket2_x = rocket2_x;
			break;
		}
		case rocket2_hiden:	hidenball(2);	//2 for player2
							break;
		case rocket2_magic:	magic_motion(2);	//2 for player2
							break;
		default:
							break;
	}
}

//****************************************************************************************************************//

int main()
{
	//
    init_platform();
    //initial settings
    XIOModule_Initialize(&io, XPAR_IOMODULE_0_DEVICE_ID);
    //
    XIOModule_Start(&io);
    //timer2 start for set delay
    microblaze_register_handler(XIOModule_DeviceInterruptHandler,XPAR_IOMODULE_0_DEVICE_ID);
    XIOModule_Connect(&io, XIN_IOMODULE_FIT_2_INTERRUPT_INTR, timerTick2, NULL); // register timerTick() as our interrupt handler
    XIOModule_Enable(&io, XIN_IOMODULE_FIT_2_INTERRUPT_INTR); // enable the interrupt
    microblaze_enable_interrupts(); // enable global interrupts
    //********************************//
    //start game
    start_game();
    //********************************//
    //timer1 start
    microblaze_register_handler(XIOModule_DeviceInterruptHandler,XPAR_IOMODULE_0_DEVICE_ID);
    XIOModule_Connect(&io, XIN_IOMODULE_FIT_1_INTERRUPT_INTR, timerTick1, NULL); // register timerTick() as our interrupt handler
    XIOModule_Enable(&io, XIN_IOMODULE_FIT_1_INTERRUPT_INTR); // enable the interrupt
    //External Interrupt start
    XIOModule_Connect(&io, XIN_IOMODULE_EXTERNAL_INTERRUPT_INTR, IntHandler, NULL);
    XIOModule_Enable(&io, XIN_IOMODULE_EXTERNAL_INTERRUPT_INTR);
    //
    microblaze_enable_interrupts(); // enable global interrupts
    //************************************************************************************************************//

    while(1){
    	//delay before restart game after player get 1 point
    	if(gamestart_flag == 1){
    		//delay for 4 second for show winner
    		delay(4000);	//delay for 4seconds
    		ballmotion_start_flag = 1;		//start ball motion
    		gamestart_flag = 0;
    	}

    	//flash Dot Matrix
    	if(page_flash_flag == 1){
    		page_flash();
    		page_flash_flag = 0;
    	}

    	//finish game
    	if(finish_flag == 1){
    		finish_game();
    	}

    }
    return 0;
}
