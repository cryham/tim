#include "kbd_layout.h"
#include "def.h"
#include "keys_usb.h"

const uint16_t clrRect[Omax] = {  // _colors for key types_
//  0 letters  1 digits       2 func F1      3 symbols ,.   4 modifiers L  5 modif R
RGB(12,12,12), RGB(13,13,10), RGB( 8,14,19), RGB(21,21,12),	RGB(12,19,19), RGB(12,19,19),
//  6 ent,tab  7 ent R        8 arrows      9 tiny
RGB( 9,21,12), RGB( 9,21,12), RGB(1,20,20), RGB(17,18,18) };

#if defined(CK6)   //  CK6/3  ------------------------------------------------
#define  wf  fW,kF
#define  wh  kW,kH
const char* CKname = "CK6 18x8";  const int16_t XR = 116, XN = 128;  // pos
const int8_t  kW = 8, kH = 9, /* size */ kF = 6, fW = 7, F = -fW, X = -kW;

const DrawKey drawKeys[nDrawKeys] = {  //  Layout draw
{ 0, 9,wf, 'e',6, 15,K_ESC},  //Esc 15x
{-18,0,wf, '1',2,139,K_F1},{F, 0,wf, '2',2,103,K_F2}, {F,0,wf, '3',2, 13,K_F3}, {F,0,wf, '4',2,110,K_F4},
{-15,0,wf, '5',2, 95,K_F5},{F, 0,wf, '6',2,131,K_F6}, {F,0,wf, '7',2,127,K_F7}, {F,0,wf, '8',2,109,K_F8},
{-14,0,wf, '9',2, 19,K_F9},{F, 0,wf, '0',2,111,K_F10},{F,0,wf, '1',2, 75,K_F11},{F,0,wf, '2',2, 74,K_F12},
 {XR+1,0,wf, '.',6, 57,0},  //Displ

{ 0,20, 8,kH, '`',3,141,K_TILDE}, //~
{-8, 0,wh, '1',1,123,K_1},{X, 0,wh, '2',1,122,K_2},{X,0,wh, '3',1,121,K_3},{X,0,wh, '4',1,116,K_4},
{ X, 0,wh, '5',1,134,K_5},{X, 0,wh, '6',1,133,K_6},{X,0,wh, '7',1,115,K_7},{X,0,wh, '8',1,114,K_8},
{ X, 0,wh, '9',1,113,K_9},{X, 0,wh, '0',1,108,K_0},
{ X, 0,wh, '-',3,126,K_MINUS},{X, 0,wh, '=',3,132,K_EQUAL},{X,0,12,kH, '<',7, 91,K_BACK}, //Back 15x
 {XR,0,wh, 'e',6,138,K_ESC},

{ 0,29,12,kH, 29 ,6,105,K_TAB}, //Tab
{-12,0,wh, 'Q',0, 87,K_Q},{X, 0,wh, 'W',0, 86,K_W},{X,0,wh, 'E',0, 85,K_E},{X,0,wh, 'R',0, 80,K_R},
{ X, 0,wh, 'T',0, 98,K_T},{X, 0,wh, 'Y',0, 97,K_Y},{X,0,wh, 'U',0, 79,K_U},{X,0,wh, 'I',0, 78,K_I},
{ X, 0,wh, 'O',0, 77,K_O},{X, 0,wh, 'P',0, 72,K_P},{X,0,wh, '[',3, 90,K_LBRACE},
{ X, 0,wh, ']',3, 96,K_RBRACE},{X,0, 8,kH,'\\',3, 55,K_BSLASH}, // \| 15x
 {XR,0,wh, '<',7,137,K_BACK},

{ 0,38,15,kH,  2 ,6,104,K_CAPS}, //Caps
{-15,0,wh, 'A',0, 69,K_A},{X, 0,wh, 'S',0, 68,K_S},{X,0,wh, 'D',0, 67,K_D},{X,0,wh, 'F',0, 62,K_F},
{ X, 0,wh, 'G',0,  8,K_G},{X, 0,wh, 'H',0,  7,K_H},{X,0,wh, 'J',0, 61,K_J},{X,0,wh, 'K',0, 60,K_K},
{ X, 0,wh, 'L',0, 59,K_L},{X, 0,wh, ';',3, 54,K_SEMIC},
{ X, 0,wh,'\'',3,  0,K_QUOTE},{X, 0,13,kH, 28,7, 37,K_ENT}, //Ent 14x
 {XR,0,wh, 28,7,119,K_ENT},

{ 0,47,18,kH, 's',4, 94,K_LSHIFT}, //L Sh
{-18,0,wh, 'Z',0, 51,K_Z},{X, 0,wh, 'X',0, 50,K_X},{X,0,wh, 'C',0, 49,K_C},{X,0,wh, 'V',0, 44,K_V},
{ X, 0,wh, 'B',0, 26,K_B},{X, 0,wh, 'N',0, 25,K_N},{X,0,wh, 'M',0, 43,K_M},{X,0,wh, ',',3, 42,K_COMMA},
{ X, 0,wh, '.',3, 41,K_PERIOD},{X,0,wh, '/',3, 18,K_SLASH},
{ X, 0,10,kH, 's',5, 58,K_RSHIFT}, {-10,0,8,kH, '^',5, 12,K_F15}, //R Sh 14x
 {XR,0,wh, 's',7,120,K_RSHIFT}, // 12 up  120 end

 //modif:  L Ctrl, L Gui, L Alt, space, R Alt, App,K_Ss, R Gui, R Ctrl
{ 0,56,11,kH, 'c',4,128,K_LCTRL},{-11,0,7,kH,  9 ,4,106,K_LGUI},{-7,0,7,kH,  '\\',4, 14,K_NON_US_NUM},
{-7, 0,11,kH, 'a',4,  3,K_LALT}, {-11,0,34,kH,' ',6,  9,K_SPACE}, //Space
{-34,0, 9,kH, 'a',5, 21,K_RALT}, // 23 menu 136 ins 135 del  30 ri 27 dn  28 le
{-9, 0, 8,kH,  9 ,6, 23,K_RGUI}, {-8,0, 8,kH,254,5,136,K_MENU},{-8, 0,7,kH,'c',5,135,K_RCTRL}, //R Ct 12x
{-7, 0, 7,kH, '>',5, 30,K_F13},  {-7, 0,7,kH,'v',5, 27,K_F14},
 {XR,0,wh,'c',7,28,K_RCTRL},
//numpad: 17x
{XN,20,wh,  3 ,6, 45,K_NUML},{X, 0,wh, '/',3, 46,KP_DIV},{X,0,wh, 'x',3, 47,KP_MUL},{X,0,kW-2,kH,  '-',3, 29,KP_SUB},
{XN,29,wh, '7',8, 81,K_HOME},{X, 0,wh, 24 ,8, 82,K_UP},  {X,0,wh, '9',8, 83,K_PGUP},{X,0,kW-2,kH*2,'+',3, 84,KP_ADD},
{XN,38,wh, 27 ,8, 99,K_LEFT},{X, 0,wh,  7 ,6,100,K_DEL}, {X,0,wh, 26 ,8,101,K_RIGHT},
{XN,47,wh, '1',8, 63,K_END}, {X, 0,wh, 25 ,8, 64,K_DOWN},{X,0,wh, '3',8, 65,K_PGDN},{X,0,kW-2,kH*2, '|',3, 66,KP_ENT},
{XN,56,kW*2,kH,'_',6, 10,K_INS},{-kW*2,0,wh,'.',6, 11,K_DEL}, //Ins Del
};
const uint8_t gGui=57, gMslow=94, gLoad=95,gSave=110,gDiv=46, gEsc=15,gAdd=84,gEnt=66,gEnt2=37,
	gRight=101,gLeft=99,gDown=64,gUp=82, gPgUp=83,gPgDn=65,gEnd=63,gHome=81,
	gCtrl=128,gSh=94,gMul=47,gSub=29, gIns=10,gDel=100, gBckSp=91,gSpc=9, gC=49,gV=44,gX=50,
	gF1=139,gF2=103,gF3=13,gF6=131,gF7=127,gF8=109,gF9=19,gF10=111,gF11=75,gF12=74;

#endif
#undef wf
#undef wh
#undef wm
