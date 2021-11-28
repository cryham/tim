#include "WProgram.h"
#include "kc_data.h"

//  load, save in eeprom
//.............................................
#define EOfs 0      //  offset and
#define ESize 2048  //  max size to use

#define Erd(a)    eeprom_read_byte((uint8_t*)a);      ++a;  memSize = a;  if (a >= ESize) {  err=E_size;  return;  }
#define Ewr(a,b)  eeprom_write_byte((uint8_t*)a, b);  ++a;  memSize = a;  if (a >= ESize) {  err=E_size;  return;  }


//  default params  ----
void ParInit()
{
	par.debounce = 4;  // ms?
	par.strobe_delay = 4;
	par.scanFreq = 50;  // 1 kHz

	par.brightness = 80;
	par.startScreen = 0;

	par.verCounter = 0;
	par.krDelay = 250/5;  par.krRepeat = 80/5;  // ms

	par.rtcCompensate = 0;
	par.tempOfs = int8_t(-0.6/*'C*/ / 0.03);  //-20

	par.timeTemp = 10;   // 8s
	par.timeTgraph = 15; // 1m  gIntervals
	par.minTemp = 17;  par.maxTemp = 35;
	par.xCur = W-1;
}

//  errors
const char* KCerrStr[E_max] = {
	"ok", "> Max size",  "Hdr1 !k", "Hdr2 !c", "Hdr3 ver <",
};

//  get ram allocated
uint16_t KC_Main::GetSize()
{
	uint16_t s=0;
	s += sizeof(KC_Main);
	return s;
}


//  Load
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
void KC_Main::Load()
{
	err = E_ok;
	//set.Clear();

	int a = EOfs, i, n;  uint8_t b;
	//  header
	set.h1 = Erd(a);  if (set.h1 != 'k') {  err=E_H1;  return;  }
	set.h2 = Erd(a);  if (set.h2 != 'c') {  err=E_H2;  return;  }
	set.ver = Erd(a);  if (set.ver > 9) {  err=E_ver;  return;  }

	//  matrix
	set.rows = Erd(a);  if (set.rows > KC_MaxRows) {  err=E_rows;  return;  }
	set.cols = Erd(a);  if (set.cols > KC_MaxCols) {  err=E_cols;  return;  }
	set.scanKeys = set.rows * set.cols;
	set.seqSlots = Erd(a);  // now less than in ee
	if (set.seqSlots > KC_MaxSeqs) {  err=E_slots;  set.seqSlots = KC_MaxSeqs;  }


	//  params  ----
	ParInit();  // defaults

	n = Erd(a);  // size
	eeprom_read_block((void*)&par, (void*)a, n);  a+=n;
	if (a >= ESize) {  err=E_size;  return;  }

	if (par.startScreen >= ST_ALL)
		par.startScreen = ST_ALL-1;
	setDac = 1;  // upd
	
	memSize = a;
}

//  Save
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
void KC_Main::Save()
{
	err = E_ok;
	//  sth very wrong
	if (set.rows * set.cols != set.scanKeys)
	{	err=E_rcEq;  return;  }

	#ifndef CK1
	if (set.nkeys() != int(set.scanKeys))
	{	err=E_nkeys;  return;  }
	#endif

	int a = EOfs, i, n;

	//  header
	set.h1 = 'k';  set.h2 = 'c';  set.ver = 3;  // cur
	Ewr(a, set.h1);  Ewr(a, set.h2);  Ewr(a, set.ver);

	//  matrix
	Ewr(a, set.rows);  Ewr(a, set.cols);  Ewr(a, set.seqSlots);


	//  params  ----
	++par.verCounter;  // inc ver

	n = sizeof(par);
	Ewr(a, n);  // size
	eeprom_write_block((void*)&par, (void*)a, n);  a+=n;
	if (a >= ESize) {  err=E_size;  return;  }

	memSize = a;
}
