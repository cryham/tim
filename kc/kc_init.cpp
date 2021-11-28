#include "kc_data.h"
#include "kbd_layout.h"
#include "usb_keyboard.h"
#include "matrix.h"
#include "keys_usb.h"
#include "kc_params.h"
#include "WProgram.h"  // rtc, Mouse


//------------------------------------------------
void KC_Main::SeqModClear()
{
	//  clear modif
	for (int i=0; i <= K_ModLast; ++i)
		seqMod[i] = 0;
}

//  ctor  Main
//------------------------------------------------
KC_Main::KC_Main()
{
	err = E_ok;  memSize = 0;
	setDac = 1;
	SeqModClear();

	Mouse.screenSize(1920,1200);  //?

	//  rtc set
	unsigned long t = rtc_get();

	int yr = t/3600/24/365;
	if (yr == 0)  // set date if none
	{
		//  whatever in 2018, 614736000
		t = 18 * 365 + 8 * 30;  t *= 24 * 3600;
		t += 16 * 3600;
		rtc_set(t);
	}
	ResetStats(true);

#ifdef GRAPHS
	memset(grPMin, 0, sizeof(grPMin));
#endif
}

//  Reset stats, rtc, times
//------------------------------------------------
void KC_Main::ResetStats(bool rtc)
{
	// rtc
	unsigned long t = rtc_get();
	if (rtc)
		tm_on = t;

	tm_key = tm_keyOld = tm_keyAct = t;
	//  ms
	uint32_t ms = millis();
	msMin1 = msKeyLay = ms;

	//  cnt
	tInactSum = tInact1 = tInact2 = 0;
	min1_Keys = 0;

	cnt_press = 0;  // matrix.h
	cnt_press1min = 0;
}


//  clear evth
//------------------------------------------------
void KC_Setup::Clear()
{
	//  header  ver
	h1 ='k';  h2 = 'c';  ver = 3;  //+ up on changes

	//  default  matrix
	rows = 8;  cols = 18;  scanKeys = rows * cols;
	seqSlots = KC_MaxSeqs;

	int i,l;
	for (l=0; l < KC_MaxLayers; ++l)
	for (i=0; i < KC_MaxRows * KC_MaxCols; ++i)
		key[l][i] = KEY_NONE;

	//  const size
	for (i=0; i < KC_MaxSeqs; ++i)
	{	seqs[i].data.clear();
		seqs[i].data.shrink_to_fit();  // free ram
	}
}

//  ctor  Setup
//------------------------------------------------
KC_Setup::KC_Setup()
{
	//Clear();
	InitCK();
}

//  Init
//------------------------------------------------
void KC_Setup::InitCK()
{
	Clear();
#if defined(CK8)
	rows = 8;  cols = 20;
#elif defined(CK1)
	rows = 6;  cols = 8;
#elif defined(CK3)
	rows = 8;  cols = 18;
#endif
	scanKeys = rows * cols;
	seqSlots = KC_MaxSeqs;

	int i;
	//  from draw layout
	for (i=0; i < nDrawKeys; ++i)
	{
		const DrawKey& dk = drawKeys[i];
		if (dk.sc != NO)
		{
			#define add(code, lay)  key[lay][dk.sc] = code
			add(dk.code, 0);

			#undef add
	}	}

}
