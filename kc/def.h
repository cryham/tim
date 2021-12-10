#pragma once
#include <stdint.h>
#include <stdio.h>

//----  Setup  ----	  use:  ram B      flash
//  optional features, comment out to disable
#define GRAPHS          //  322 <1%

//  temperature 'C sensor DS18B20
//#define TEMP1  31	 //  44   9%  24k

#define LCD_LED  32  //  PWM LCD brightness
//-----------------


#define W 160  //  display dim
#define H 128

//  R F800  G 07E0  B 001F  R 32 G 64 B 32  565
#define RGB(r,g,b)  ( ((r)<<11)+ ((g)<<6) +(b))   // 31 31 31
#define RGB2(r,g,b) ( ((r)<<11)+ ((g)<<5) +(b))  // 31 63 31

#ifdef __cplusplus
class Ada4_ST7735;
#endif

typedef unsigned int uint;


//  main menu entries, level0
enum EMainMenu
{
	M_Clock, M_Display, M_Testing, M_Help,
	M_All,  M_Next = -1  //M_Display  // 2nd column, -1 off
};

//  pages  --
enum EDisplay
{
	Di_Bright, Di_Config, Di_Key, Di_Graph, Di_Debug, Di_All
};

enum EClock
{
	Cl_Adjust, Cl_Simple,
	Cl_StatsText, Cl_Stats, Cl_StatsExt,
	#ifdef GRAPHS
		Cl_Graphs,
	#endif
	Cl_All
};

//  string names for all above ^
extern const char
	*strMain[M_All], *strClock[Cl_All];

//  sub page counts, inside each main menu entry
extern const uint8_t YM1[M_All];

//  time intervals  *0.1s
extern const uint16_t gIntervals[];
const static uint8_t gIntvMask = 0x1F;
