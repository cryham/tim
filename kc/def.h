#pragma once
#include <stdint.h>
#include <stdio.h>
// #include "wiring.h"
// #ifndef min
// #define min(a,b) ((a)<(b)?(a):(b))
// #define max(a,b) ((a)>(b)?(a):(b))
// #endif

//----  Setup  ----	  use:  ram B      flash
//  optional features, comment out to disable
#define GRAPHS          //  322 <1%

#define CK6  // 18x8  new CK6/3

//  temperature 'C sensor DS18B20
#define TEMP1  31	//  44   9%  24k
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

enum EMainMenu  //  main menu entries, level0
{
	M_Mapping, M_Sequences,
	M_Testing, M_Setup, M_Info,
	M_Display, M_Clock, M_Help,
	M_All,  M_Next = M_Display  // 2nd column, -1 off
};



//  menus  --
enum ETesting  //  Testing kbd, level1
{
	T_Layout, T_Pressed, T_Matrix, T_All
};

enum ESetup  //  Setup kbd, level1
{
	S_Layer, S_Keyboard, S_Mouse, S_Scan, S_All
};

enum EInfo  //  Info use,ver
{
	I_Use, I_Version, I_All
};

//  pages  --
enum EDisplay
{
	Di_Bright, Di_Key, Di_Stats, Di_Graph, Di_Debug, Di_All
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
	*strMain[M_All], *strTest[T_All], *strSetup[S_All],
	*strInfo[I_All], *strClock[Cl_All];

//  sub page counts, inside each main menu entry
extern const uint8_t YM1[M_All];

//  time intervals  *0.1s
extern const uint16_t gIntervals[];
const static uint8_t gIntvMask = 0x1F;

