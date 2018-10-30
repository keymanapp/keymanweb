/*
  Name:             VKScanCodes
  Copyright:        Copyright (C) SIL International.
  Documentation:    
  Description:      
  Create Date:      11 Dec 2009

  Modified Date:    17 Dec 2013
  Authors:          mcdurdin
  Related Files:    
  Dependencies:     

  Bugs:             
  Todo:             
  Notes:            
  History:          11 Dec 2009 - mcdurdin - I934 - x64 - Initial version
                    17 Dec 2013 - mcdurdin - I4006 - V9.0 - Remove old aiDefault code
*/
#include "pch.h"   // I4006

UINT USVirtualKeyToScanCode[256] = 
{
	0x00, // L"K_?00",				// &H0
	0x00, // L"K_LBUTTON",			// &H1
	0x00, // L"K_RBUTTON",			// &H2
	0x46, // L"K_CANCE0x00, // L",		   	// &H3
	0x00, // L"K_MBUTTON",			// &H4
	0x00, // L"K_?05",				// &H5
	0x00, // L"K_?06",				// &H6
	0x00, // L"K_?07",				// &H7
	0x0E, // L"K_BKSP",	    		// &H8
	0x0F, // L"K_TAB",	    		// &H9
	0x00, // L"K_?0A",				// &HA
	0x00, // L"K_?0B",				// &HB
	0x4C, // L"K_KP5",		    	// &HC
	0x1C, // L"K_ENTER",				// &HD
	0x00, // L"K_?0E",				// &HE
	0x00, // L"K_?0F",				// &HF
	0x2A, // L"K_SHIFT",				// &H10
	0x1D, // L"K_CONTRO0x00, // L",			// &H11
	0x38, // L"K_ALT",				// &H12
	0x00, // L"K_PAUSE",				// &H13
	0x3A, // L"K_CAPS",				// &H14
	0x00, // L"K_KANJI?15",			// &H15
	0x00, // L"K_KANJI?16",			// &H16
	0x00, // L"K_KANJI?17",			// &H17
	0x00, // L"K_KANJI?18",			// &H18
	0x00, // L"K_KANJI?19",			// &H19
	0x00, // L"K_?1A",				// &H1A
	0x01, // L"K_ESC",				// &H1B
	0x00, // L"K_KANJI?1C",			// &H1C
	0x00, // L"K_KANJI?1D",			// &H1D
	0x00, // L"K_KANJI?1E",			// &H1E
	0x00, // L"K_KANJI?1F",			// &H1F
	0x39, // L"K_SPACE",				// &H20
	0x49, // L"K_PGUP",				// &H21
	0x51, // L"K_PGDN",				// &H22
	0x4F, // L"K_END",				// &H23
	0x47, // L"K_HOME",				// &H24
	0x4B, // L"K_LEFT",				// &H25
	0x48, // L"K_UP",				// &H26
	0x4D, // L"K_RIGHT",				// &H27
	0x50, // L"K_DOWN",				// &H28
	0x00, // L"K_SEL",				// &H29
	0x00, // L"K_PRINT",				// &H2A
	0x00, // L"K_EXEC",				// &H2B
	0x54, // L"K_PRTSCN",			// &H2C
	0x52, // L"K_INS",				// &H2D
	0x53, // L"K_DEL",				// &H2E
	0x63, // L"K_HELP",				// &H2F
	0x0B, // L"K_0",					// &H30
	0x02, // L"K_1",					// &H31
	0x03, // L"K_2",					// &H32
	0x04, // L"K_3",					// &H33
	0x05, // L"K_4",					// &H34
	0x06, // L"K_5",					// &H35
	0x07, // L"K_6",					// &H36
	0x08, // L"K_7",					// &H37
	0x09, // L"K_8",					// &H38
	0x0A, // L"K_9",					// &H39
	0x00, // L"K_?3A",				// &H3A
	0x00, // L"K_?3B",				// &H3B
	0x00, // L"K_?3C",				// &H3C
	0x00, // L"K_?3D",				// &H3D
	0x00, // L"K_?3E",				// &H3E
	0x00, // L"K_?3F",				// &H3F
	0x00, // L"K_?40",				// &H40  

	0x1E, // L"K_A",					// &H41
	0x30, // L"K_B",					// &H42
	0x2E, // L"K_C",					// &H43
	0x20, // L"K_D",					// &H44
	0x12, // L"K_E",					// &H45
	0x21, // L"K_F",					// &H46
	0x22, // L"K_G",					// &H47
	0x23, // L"K_H",					// &H48
	0x17, // L"K_I",					// &H49
	0x24, // L"K_J",					// &H4A
	0x25, // L"K_K",					// &H4B
	0x26, // L"K_L",					// &H4C
	0x32, // L"K_M",					// &H4D
	0x31, // L"K_N",					// &H4E
	0x18, // L"K_O",					// &H4F
	0x19, // L"K_P",					// &H50
	0x10, // L"K_Q",					// &H51
	0x13, // L"K_R",					// &H52
	0x1F, // L"K_S",					// &H53
	0x14, // L"K_T",					// &H54
	0x16, // L"K_U",					// &H55
	0x2F, // L"K_V",					// &H56
	0x11, // L"K_W",					// &H57
	0x2D, // L"K_X",					// &H58
	0x15, // L"K_Y",					// &H59
	0x2C, // L"K_Z",					// &H5A
	0x5B, // L"K_?5B",				// &H5B
	0x5C, // L"K_?5C",				// &H5C
	0x5D, // L"K_?5D",				// &H5D
	0x00, // L"K_?5E",				// &H5E
	0x5F, // L"K_?5F",				// &H5F
	0x52, // L"K_NP0",				// &H60
	0x4F, // L"K_NP1",				// &H61
	0x50, // L"K_NP2",				// &H62
	0x51, // L"K_NP3",				// &H63
	0x4B, // L"K_NP4",				// &H64
	0x4C, // L"K_NP5",				// &H65
	0x4D, // L"K_NP6",				// &H66
	0x47, // L"K_NP7",				// &H67
	0x48, // L"K_NP8",				// &H68
	0x49, // L"K_NP9",				// &H69
	0x37, // L"K_NPSTAR",			// &H6A
	0x4E, // L"K_NPPLUS",			// &H6B
	0x7E, // L"K_SEPARATOR",			// &H6C		// MCD 01-11-02: Brazilian Fix, 00 -> 7E
	0x4A, // L"K_NPMINUS",			// &H6D
	0x53, // L"K_NPDOT",				// &H6E
	0x135, // L"K_NPSLASH",			// &H6F
	0x3B, // L"K_F1",				// &H70
	0x3C, // L"K_F2",				// &H71
	0x3D, // L"K_F3",				// &H72
	0x3E, // L"K_F4",				// &H73
	0x3F, // L"K_F5",				// &H74
	0x40, // L"K_F6",				// &H75
	0x41, // L"K_F7",				// &H76
	0x42, // L"K_F8",				// &H77
	0x43, // L"K_F9",				// &H78
	0x44, // L"K_F10",				// &H79
	0x57, // L"K_F11",				// &H7A
	0x58, // L"K_F12",				// &H7B
	0x64, // L"K_F13",				// &H7C
	0x65, // L"K_F14",				// &H7D
	0x66, // L"K_F15",				// &H7E
	0x67, // L"K_F16",				// &H7F
	0x68, // L"K_F17",				// &H80
	0x69, // L"K_F18",				// &H81
	0x6A, // L"K_F19",				// &H82
	0x6B, // L"K_F20",				// &H83
	0x6C, // L"K_F21",				// &H84
	0x6D, // L"K_F22",				// &H85
	0x6E, // L"K_F23",				// &H86
	0x76, // L"K_F24",				// &H87  

	0x00, // L"K_?88",				// &H88
	0x00, // L"K_?89",				// &H89
	0x00, // L"K_?8A",				// &H8A
	0x00, // L"K_?8B",				// &H8B
	0x00, // L"K_?8C",				// &H8C
	0x00, // L"K_?8D",				// &H8D
	0x00, // L"K_?8E",				// &H8E
	0x00, // L"K_?8F",				// &H8F 

	0x45, // L"K_NUMLOCK",			// &H90
	0x46, // L"K_SCROL0x00, // L",			// &H91 

	0x00, // L"K_?92",				// &H92
	0x00, // L"K_?93",				// &H93
	0x00, // L"K_?94",				// &H94
	0x00, // L"K_?95",				// &H95
	0x00, // L"K_?96",				// &H96
	0x00, // L"K_?97",				// &H97
	0x00, // L"K_?98",				// &H98
	0x00, // L"K_?99",				// &H99
	0x00, // L"K_?9A",				// &H9A
	0x00, // L"K_?9B",				// &H9B
	0x00, // L"K_?9C",				// &H9C
	0x00, // L"K_?9D",				// &H9D
	0x00, // L"K_?9E",				// &H9E
	0x00, // L"K_?9F",				// &H9F
	0x2A, // L"K_?A0",				// &HA0
	0x36, // L"K_?A1",				// &HA1
	0x1D, // L"K_?A2",				// &HA2
	0x1D, // L"K_?A3",				// &HA3
	0x38, // L"K_?A4",				// &HA4
	0x38, // L"K_?A5",				// &HA5
	0x6A, // L"K_?A6",				// &HA6
	0x69, // L"K_?A7",				// &HA7
	0x67, // L"K_?A8",				// &HA8
	0x68, // L"K_?A9",				// &HA9
	0x65, // L"K_?AA",				// &HAA
	0x66, // L"K_?AB",				// &HAB
	0x32, // L"K_?AC",				// &HAC
	0x20, // L"K_?AD",				// &HAD
	0x2E, // L"K_?AE",				// &HAE
	0x30, // L"K_?AF",				// &HAF
	0x19, // L"K_?B0",				// &HB0
	0x10, // L"K_?B1",				// &HB1
	0x24, // L"K_?B2",				// &HB2
	0x22, // L"K_?B3",				// &HB3
	0x6C, // L"K_?B4",				// &HB4
	0x6D, // L"K_?B5",				// &HB5
	0x6B, // L"K_?B6",				// &HB6
	0x21, // L"K_?B7",				// &HB7
	0x00, // L"K_?B8",				// &HB8
	0x00, // L"K_?B9",				// &HB9 

	0x27, // L"K_COLON",				// &HBA
	0x0D, // L"K_EQUA0x00, // L",				// &HBB
	0x33, // L"K_COMMA",				// &HBC
	0x0C, // L"K_HYPHEN",			// &HBD
	0x34, // L"K_PERIOD",			// &HBE
	0x35, // L"K_SLASH",				// &HBF
	0x29, // L"K_BKQUOTE",			// &HC0 

	0x73, // L"K_?C1",				// &HC1
	0x7E, // L"K_?C2",				// &HC2
	0x00, // L"K_?C3",				// &HC3
	0x00, // L"K_?C4",				// &HC4
	0x00, // L"K_?C5",				// &HC5
	0x00, // L"K_?C6",				// &HC6
	0x00, // L"K_?C7",				// &HC7
	0x00, // L"K_?C8",				// &HC8
	0x00, // L"K_?C9",				// &HC9
	0x00, // L"K_?CA",				// &HCA
	0x00, // L"K_?CB",				// &HCB
	0x00, // L"K_?CC",				// &HCC
	0x00, // L"K_?CD",				// &HCD
	0x00, // L"K_?CE",				// &HCE
	0x00, // L"K_?CF",				// &HCF
	0x00, // L"K_?D0",				// &HD0
	0x00, // L"K_?D1",				// &HD1
	0x00, // L"K_?D2",				// &HD2
	0x00, // L"K_?D3",				// &HD3
	0x00, // L"K_?D4",				// &HD4
	0x00, // L"K_?D5",				// &HD5
	0x00, // L"K_?D6",				// &HD6
	0x00, // L"K_?D7",				// &HD7
	0x00, // L"K_?D8",				// &HD8
	0x00, // L"K_?D9",				// &HD9
	0x00, // L"K_?DA",				// &HDA 

	0x1A, // L"K_LBRKT",				// &HDB
	0x2B, // L"K_BKSLASH",			// &HDC
	0x1B, // L"K_RBRKT",				// &HDD
	0x28, // L"K_QUOTE",				// &HDE
	0x73, // L"K_oDF",				// &HDF			// MCD 01-11-02: Brazilian fix: 00 -> 73
	0x00, // L"K_oE0",				// &HE0
	0x00, // L"K_oE1",				// &HE1
	0x56, // L"K_oE2",				// &HE2
	0x00, // L"K_oE3",				// &HE3
	0x00, // L"K_oE4",				// &HE4 

	0x00, // L"K_?E5",				// &HE5 

	0x00, // L"K_oE6",				// &HE6 

	0x00, // L"K_?E7",				// &HE7
	0x00, // L"K_?E8",				// &HE8 

	0x71, // L"K_oE9",				// &HE9
	0x5C, // L"K_oEA",				// &HEA
	0x7B, // L"K_oEB",				// &HEB
	0x00, // L"K_oEC",				// &HEC
	0x6F, // L"K_oED",				// &HED
	0x5A, // L"K_oEE",				// &HEE
	0x00, // L"K_oEF",				// &HEF
	0x00, // L"K_oF0",				// &HF0
	0x5B, // L"K_oF1",				// &HF1
	0x00, // L"K_oF2",				// &HF2
	0x5F, // L"K_oF3",				// &HF3
	0x00, // L"K_oF4",				// &HF4
	0x5E, // L"K_oF5",				// &HF5 

	0x00, // L"K_?F6",				// &HF6
	0x00, // L"K_?F7",				// &HF7
	0x00, // L"K_?F8",				// &HF8
	0x5D, // L"K_?F9",				// &HF9
	0x00, // L"K_?FA",				// &HFA
	0x62, // L"K_?FB",				// &HFB
	0x00, // L"K_?FC",				// &HFC
	0x00, // L"K_?FD",				// &HFD
	0x00, // L"K_?FE",				// &HFE
	0x00  // L"K_?FF"				// &HFF
};


/* Queue and sending functions */
extern const int VKContextReset[256];

const int VKContextReset[256] = {
	1,   //L"K_?00",				// &H0
	1,   //L"K_LBUTTON",			// &H1
	1,   //L"K_RBUTTON",			// &H2
	1,   //L"K_CANCEL",		   	// &H3
	1,   //L"K_MBUTTON",			// &H4
	1,   //L"K_?05",				// &H5
	1,   //L"K_?06",				// &H6
	1,   //L"K_?07",				// &H7
	1,   //L"K_BKSP",	    		// &H8
	1,   //L"K_TAB",	    		// &H9
	1,   //L"K_?0A",				// &HA
	1,   //L"K_?0B",				// &HB
	1,   //L"K_KP5",		    	// &HC
	1,   //L"K_ENTER",				// &HD
	1,   //L"K_?0E",				// &HE
	1,   //L"K_?0F",				// &HF
	0,   //L"K_SHIFT",				// &H10
	0,   //L"K_CONTROL",			// &H11
	0,   //L"K_ALT",				// &H12
	1,   //L"K_PAUSE",				// &H13
	0,   //L"K_CAPS",				// &H14
	1,   //L"K_KANJI?15",			// &H15
	1,   //L"K_KANJI?16",			// &H16
	1,   //L"K_KANJI?17",			// &H17
	1,   //L"K_KANJI?18",			// &H18
	1,   //L"K_KANJI?19",			// &H19
	1,   //L"K_?1A",				// &H1A
	1,   //L"K_ESC",				// &H1B
	1,   //L"K_KANJI?1C",			// &H1C
	1,   //L"K_KANJI?1D",			// &H1D
	1,   //L"K_KANJI?1E",			// &H1E
	1,   //L"K_KANJI?1F",			// &H1F
	0,   //L"K_SPACE",				// &H20
	1,   //L"K_PGUP",				// &H21
	1,   //L"K_PGDN",				// &H22
	1,   //L"K_END",				// &H23
	1,   //L"K_HOME",				// &H24
	1,   //L"K_LEFT",				// &H25
	1,   //L"K_UP",				// &H26
	1,   //L"K_RIGHT",				// &H27
	1,   //L"K_DOWN",				// &H28
	1,   //L"K_SEL",				// &H29
	1,   //L"K_PRINT",				// &H2A
	1,   //L"K_EXEC",				// &H2B
	1,   //L"K_PRTSCN",			// &H2C
	0,   //L"K_INS",				// &H2D
	1,   //L"K_DEL",				// &H2E
	1,   //L"K_HELP",				// &H2F
	0,   //L"K_0",					// &H30
	0,   //L"K_1",					// &H31
	0,   //L"K_2",					// &H32
	0,   //L"K_3",					// &H33
	0,   //L"K_4",					// &H34
	0,   //L"K_5",					// &H35
	0,   //L"K_6",					// &H36
	0,   //L"K_7",					// &H37
	0,   //L"K_8",					// &H38
	0,   //L"K_9",					// &H39
	0,   //L"K_?3A",				// &H3A
	0,   //L"K_?3B",				// &H3B
	0,   //L"K_?3C",				// &H3C
	0,   //L"K_?3D",				// &H3D
	0,   //L"K_?3E",				// &H3E
	0,   //L"K_?3F",				// &H3F
	0,   //L"K_?40",				// &H40

	0,   //L"K_A",					// &H41
	0,   //L"K_B",					// &H42
	0,   //L"K_C",					// &H43
	0,   //L"K_D",					// &H44
	0,   //L"K_E",					// &H45
	0,   //L"K_F",					// &H46
	0,   //L"K_G",					// &H47
	0,   //L"K_H",					// &H48
	0,   //L"K_I",					// &H49
	0,   //L"K_J",					// &H4A
	0,   //L"K_K",					// &H4B
	0,   //L"K_L",					// &H4C
	0,   //L"K_M",					// &H4D
	0,   //L"K_N",					// &H4E
	0,   //L"K_O",					// &H4F
	0,   //L"K_P",					// &H50
	0,   //L"K_Q",					// &H51
	0,   //L"K_R",					// &H52
	0,   //L"K_S",					// &H53
	0,   //L"K_T",					// &H54
	0,   //L"K_U",					// &H55
	0,   //L"K_V",					// &H56
	0,   //L"K_W",					// &H57
	0,   //L"K_X",					// &H58
	0,   //L"K_Y",					// &H59
	0,   //L"K_Z",					// &H5A
	0,   //L"K_?5B",				// &H5B
	0,   //L"K_?5C",				// &H5C
	0,   //L"K_?5D",				// &H5D
	0,   //L"K_?5E",				// &H5E
	0,   //L"K_?5F",				// &H5F
	0,   //L"K_NP0",				// &H60
	0,   //L"K_NP1",				// &H61
	0,   //L"K_NP2",				// &H62
	0,   //L"K_NP3",				// &H63
	0,   //L"K_NP4",				// &H64
	0,   //L"K_NP5",				// &H65
	0,   //L"K_NP6",				// &H66
	0,   //L"K_NP7",				// &H67
	0,   //L"K_NP8",				// &H68
	0,   //L"K_NP9",				// &H69
	0,   //L"K_NPSTAR",			// &H6A
	0,   //L"K_NPPLUS",			// &H6B
	0,   //L"K_SEPARATOR",			// &H6C
	0,   //L"K_NPMINUS",			// &H6D
	0,   //L"K_NPDOT",				// &H6E
	0,   //L"K_NPSLASH",			// &H6F
	1,   //L"K_F1",				// &H70
	1,   //L"K_F2",				// &H71
	1,   //L"K_F3",				// &H72
	1,   //L"K_F4",				// &H73
	1,   //L"K_F5",				// &H74
	1,   //L"K_F6",				// &H75
	1,   //L"K_F7",				// &H76
	1,   //L"K_F8",				// &H77
	1,   //L"K_F9",				// &H78
	1,   //L"K_F10",				// &H79
	1,   //L"K_F11",				// &H7A
	1,   //L"K_F12",				// &H7B
	1,   //L"K_F13",				// &H7C
	1,   //L"K_F14",				// &H7D
	1,   //L"K_F15",				// &H7E
	1,   //L"K_F16",				// &H7F
	1,   //L"K_F17",				// &H80
	1,   //L"K_F18",				// &H81
	1,   //L"K_F19",				// &H82
	1,   //L"K_F20",				// &H83
	1,   //L"K_F21",				// &H84
	1,   //L"K_F22",				// &H85
	1,   //L"K_F23",				// &H86
	1,   //L"K_F24",				// &H87

	0,   //L"K_?88",				// &H88
	0,   //L"K_?89",				// &H89
	0,   //L"K_?8A",				// &H8A
	0,   //L"K_?8B",				// &H8B
	0,   //L"K_?8C",				// &H8C
	0,   //L"K_?8D",				// &H8D
	0,   //L"K_?8E",				// &H8E
	0,   //L"K_?8F",				// &H8F

	0,   //L"K_NUMLOCK",			// &H90
	0,   //L"K_SCROLL",			// &H91

	0,   //L"K_?92",				// &H92
	0,   //L"K_?93",				// &H93
	0,   //L"K_?94",				// &H94
	0,   //L"K_?95",				// &H95
	0,   //L"K_?96",				// &H96
	0,   //L"K_?97",				// &H97
	0,   //L"K_?98",				// &H98
	0,   //L"K_?99",				// &H99
	0,   //L"K_?9A",				// &H9A
	0,   //L"K_?9B",				// &H9B
	0,   //L"K_?9C",				// &H9C
	0,   //L"K_?9D",				// &H9D
	0,   //L"K_?9E",				// &H9E
	0,   //L"K_?9F",				// &H9F
	0,   //L"K_?A0",				// &HA0
	0,   //L"K_?A1",				// &HA1
	0,   //L"K_?A2",				// &HA2
	0,   //L"K_?A3",				// &HA3
	0,   //L"K_?A4",				// &HA4
	0,   //L"K_?A5",				// &HA5
	0,   //L"K_?A6",				// &HA6
	0,   //L"K_?A7",				// &HA7
	0,   //L"K_?A8",				// &HA8
	0,   //L"K_?A9",				// &HA9
	0,   //L"K_?AA",				// &HAA
	0,   //L"K_?AB",				// &HAB
	0,   //L"K_?AC",				// &HAC
	0,   //L"K_?AD",				// &HAD
	0,   //L"K_?AE",				// &HAE
	0,   //L"K_?AF",				// &HAF
	0,   //L"K_?B0",				// &HB0
	0,   //L"K_?B1",				// &HB1
	0,   //L"K_?B2",				// &HB2
	0,   //L"K_?B3",				// &HB3
	0,   //L"K_?B4",				// &HB4
	0,   //L"K_?B5",				// &HB5
	0,   //L"K_?B6",				// &HB6
	0,   //L"K_?B7",				// &HB7
	0,   //L"K_?B8",				// &HB8
	0,   //L"K_?B9",				// &HB9

	0,   //L"K_COLON",				// &HBA
	0,   //L"K_EQUAL",				// &HBB
	0,   //L"K_COMMA",				// &HBC
	0,   //L"K_HYPHEN",			// &HBD
	0,   //L"K_PERIOD",			// &HBE
	0,   //L"K_SLASH",				// &HBF
	0,   //L"K_BKQUOTE",			// &HC0

	0,   //L"K_?C1",				// &HC1
	0,   //L"K_?C2",				// &HC2
	0,   //L"K_?C3",				// &HC3
	0,   //L"K_?C4",				// &HC4
	0,   //L"K_?C5",				// &HC5
	0,   //L"K_?C6",				// &HC6
	0,   //L"K_?C7",				// &HC7
	0,   //L"K_?C8",				// &HC8
	0,   //L"K_?C9",				// &HC9
	0,   //L"K_?CA",				// &HCA
	0,   //L"K_?CB",				// &HCB
	0,   //L"K_?CC",				// &HCC
	0,   //L"K_?CD",				// &HCD
	0,   //L"K_?CE",				// &HCE
	0,   //L"K_?CF",				// &HCF
	0,   //L"K_?D0",				// &HD0
	0,   //L"K_?D1",				// &HD1
	0,   //L"K_?D2",				// &HD2
	0,   //L"K_?D3",				// &HD3
	0,   //L"K_?D4",				// &HD4
	0,   //L"K_?D5",				// &HD5
	0,   //L"K_?D6",				// &HD6
	0,   //L"K_?D7",				// &HD7
	0,   //L"K_?D8",				// &HD8
	0,   //L"K_?D9",				// &HD9
	0,   //L"K_?DA",				// &HDA

	0,   //L"K_LBRKT",				// &HDB
	0,   //L"K_BKSLASH",			// &HDC
	0,   //L"K_RBRKT",				// &HDD
	0,   //L"K_QUOTE",				// &HDE
	0,   //L"K_oDF",				// &HDF
	0,   //L"K_oE0",				// &HE0
	0,   //L"K_oE1",				// &HE1
	0,   //L"K_oE2",				// &HE2
	0,   //L"K_oE3",				// &HE3
	0,   //L"K_oE4",				// &HE4

	0,   //L"K_?E5",				// &HE5

	0,   //L"K_oE6",				// &HE6

	0,   //L"K_?E7",				// &HE7
	0,   //L"K_?E8",				// &HE8

	0,   //L"K_oE9",				// &HE9
	0,   //L"K_oEA",				// &HEA
	0,   //L"K_oEB",				// &HEB
	0,   //L"K_oEC",				// &HEC
	0,   //L"K_oED",				// &HED
	0,   //L"K_oEE",				// &HEE
	0,   //L"K_oEF",				// &HEF
	0,   //L"K_oF0",				// &HF0
	0,   //L"K_oF1",				// &HF1
	0,   //L"K_oF2",				// &HF2
	0,   //L"K_oF3",				// &HF3
	0,   //L"K_oF4",				// &HF4
	0,   //L"K_oF5",				// &HF5

	0,   //L"K_?F6",				// &HF6
	0,   //L"K_?F7",				// &HF7
	0,   //L"K_?F8",				// &HF8
	0,   //L"K_?F9",				// &HF9
	0,   //L"K_?FA",				// &HFA
	0,   //L"K_?FB",				// &HFB
	0,   //L"K_?FC",				// &HFC
	0,   //L"K_?FD",				// &HFD
	0,   //L"K_?FE",				// &HFE
	0,   //L"K_?FF"				// &HFF
};
