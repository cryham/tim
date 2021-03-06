#pragma once
#include <stdint.h>
#include "def.h"


struct Gui
{
	Ada4_ST7735* d=0;

	//  main  ----
	Gui();
	void Init(Ada4_ST7735* tft);
	void Draw(), DrawEnd();
	void KeyPress();


	//  draw menus
	void DrawTesting(), DrawDisplay();  // set params
	void DrawClock(), DrawGraph();
	void DrawHelp();

	//  draw util
	void DrawOperInfo(), Chk_y1();
	void DrawDispCur(int i, int16_t y), DrawClockCur(int i, int16_t y);
	//  util
	void ClrTemp(int temp);
	void PrintInterval(uint32_t t);
	int TempFtoB(float t);  float TempBtoF(uint8_t b);


	//  keys
	void KeysParDisplay(int sp);
	void KeysClock();

	//  start
	void SetScreen(int8_t start);
	const char* StrScreen(int8_t s);


	//  fade color menu  ---
	enum EFadeClr
	{	C_Main=0, C_Demos, C_Test, C_Map, C_Seq,
		C_Setup, C_Disp, C_Clock, C_Setup2,
		C_Game, C_GameOpt, C_Info, C_ALL  };
	const static uint8_t
		Mclr[C_ALL][2][3];

	void FadeClr(EFadeClr ec, const uint8_t minRGB, const uint8_t mul, const uint8_t div);
	void DrawMenu(int cnt, const char** str, EFadeClr ec, uint16_t curClr,
		uint16_t bckClr, int16_t yadd=10, int16_t nextCol=-1, int16_t numGap=-1);


	//  vars  ---
	int8_t mlevel = 0;  // 0 main, 1 level1, 2 level2

	int8_t ym = 0;      // 0 main y cursor
	int8_t ym1[M_All];  // 1 y cursor for all main menu entries
	int8_t yy = 0;      // = ym1[ym]  level1 y cursor

	//  time, key repeat
	uint32_t oldti=0, oldti_kr=0;
	int8_t kr(uint8_t sc, uint16_t dt);

	//  help
	int8_t hpage = 0;
	const static int8_t HAll = 2;


	//  gui keys pressed, some +-1
	int8_t kRight=0, kUp=0,  kEnt=0, kBack=0;
	int8_t kPgUp=0,  kMid=0, kEnd=0, kSave=0;


	//  level 2 y cursors  - - -
	int8_t ym2Disp = 0, pgDisp = 0;  // Display
	int8_t ym2Clock = 0, pgClock = Cl_StatsExt;  // Clock

	const static uint8_t
		DispPages[Di_All];

	inline static uint8_t ClockVars(int pg)
	{	return pg == Cl_Adjust ? 6 : 0;  }

	//  util
	int16_t RangeAdd(int16_t val, int16_t add, int16_t vmin, int16_t vmax, int8_t cycle=0);
	void Save(), Load(int8_t reset);


	int16_t tInfo=0;  int8_t infType=0;  // info text vars


	//  Temp 'C  ---
#ifdef TEMP1
	float fTemp = -90.f;  // cur value
	int8_t temp1 = 1;     // fist, init
	//  last time read'C, add to graph
	uint32_t msTemp = 0, msTempGr = 0;
	void GetTemp();

#ifdef GRAPHS
	uint8_t grTemp[W];    // graph array
	uint8_t grTpos = 0;   // write pos
	// auto range
	uint8_t grTempUpd = 1;  // update
	uint8_t grFmin = 17, grFmax = 35;  // temp 'C
	uint8_t grBmin = 0, grBmax = 255;  // val Byte
#endif
#endif

};

