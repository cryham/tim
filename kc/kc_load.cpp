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

	par.brightness = 60;
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

	int a = EOfs, n;  //uint8_t b;
	//  header
	char h1 = 't', h2 = 'i', ver = 6;
	h1 = Erd(a);  if (h1 != 't') {  err=E_H1;  return;  }
	h2 = Erd(a);  if (h2 != 'i') {  err=E_H2;  return;  }
	ver = Erd(a);  if (ver > 1) {  err=E_ver;  return;  }

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

	int a = EOfs, n;

	//  header
	char h1 = 't', h2 = 'i', ver = 1;
	Ewr(a, h1);  Ewr(a, h2);  Ewr(a, ver);

	//  params  ----
	++par.verCounter;  // inc ver

	n = sizeof(par);
	Ewr(a, n);  // size
	eeprom_write_block((void*)&par, (void*)a, n);  a+=n;
	if (a >= ESize) {  err=E_size;  return;  }

	memSize = a;
}
