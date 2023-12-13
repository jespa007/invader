/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

#define  T_E	      	Input::getKey(DEF_KEY_E)
#define  T_ESC	      	Input::getKey(DEF_KEY_ESCAPE)
#define  T_F5	      	Input::getKey(DEF_KEY_F5)
#define  T_F9	      	Input::getKey(DEF_KEY_F9)
#define  T_F12	      	Input::getKey(DEF_KEY_F12)
#define  T_F10	      	Input::getKey(DEF_KEY_F10)
#define  T_SPACE      	Input::getKey(DEF_KEY_SPACE)
#define  T_TAB			Input::getKey(DEF_KEY_TAB)
#define  T_UP           Input::getKey(DEF_KEY_UP)
#define  T_LEFT         Input::getKey(DEF_KEY_LEFT)
#define  T_RIGHT        Input::getKey(DEF_KEY_RIGHT)
#define  T_DOWN         Input::getKey(DEF_KEY_DOWN)



#define  TR_UP          Input::getKeyR(DEF_KEY_UP)
#define  TR_LEFT        Input::getKeyR(DEF_KEY_LEFT)
#define  TR_RIGHT       Input::getKeyR(DEF_KEY_RIGHT)
#define  TR_DOWN        Input::getKeyR(DEF_KEY_DOWN)


typedef enum {
	/** @name ASCII mapped keysyms
	 *  The keyboard syms have been cleverly chosen to map to ASCII
	 */
	/*@{*/
	DEF_KEY_UNKNOWN		= 0,
	DEF_KEY_FIRST		= 0,
	DEF_KEY_BACKSPACE	= 8,
	DEF_KEY_TAB			= 9,
	DEF_KEY_CLEAR		= 12,
	DEF_KEY_RETURN		= 13,
	DEF_KEY_PAUSE		= 19,
	DEF_KEY_ESCAPE		= 27,
	DEF_KEY_SPACE		= 32,
	DEF_KEY_EXCLAIM		= 33,
	DEF_KEY_QUOTEDBL	= 34,
	DEF_KEY_HASH		= 35,
	DEF_KEY_DOLLAR		= 36,
	DEF_KEY_AMPERSAND	= 38,
	DEF_KEY_QUOTE		= 39,
	DEF_KEY_LEFTPAREN	= 40,
	DEF_KEY_RIGHTPAREN	= 41,
	DEF_KEY_ASTERISK	= 42,
	DEF_KEY_PLUS		= 43,
	DEF_KEY_COMMA		= 44,
	DEF_KEY_MINUS		= 45,
	DEF_KEY_PERIOD		= 46,
	DEF_KEY_SLASH		= 47,
	DEF_KEY_0			= 48,
	DEF_KEY_1			= 49,
	DEF_KEY_2			= 50,
	DEF_KEY_3			= 51,
	DEF_KEY_4			= 52,
	DEF_KEY_5			= 53,
	DEF_KEY_6			= 54,
	DEF_KEY_7			= 55,
	DEF_KEY_8			= 56,
	DEF_KEY_9			= 57,
	DEF_KEY_COLON		= 58,
	DEF_KEY_SEMICOLON	= 59,
	DEF_KEY_LESS		= 60,
	DEF_KEY_EQUALS		= 61,
	DEF_KEY_GREATER		= 62,
	DEF_KEY_QUESTION	= 63,
	DEF_KEY_AT			= 64,
	/*
	   Skip uppercase letters
	 */
	DEF_KEY_LEFTBRACKET	= 91,
	DEF_KEY_BACKSLASH	= 92,
	DEF_KEY_RIGHTBRACKET= 93,
	DEF_KEY_CARET		= 94,
	DEF_KEY_UNDERSCORE	= 95,
	DEF_KEY_BACKQUOTE	= 96,
	DEF_KEY_A			= 97,
	DEF_KEY_B			= 98,
	DEF_KEY_C			= 99,
	DEF_KEY_D			= 100,
	DEF_KEY_E			= 101,
	DEF_KEY_F			= 102,
	DEF_KEY_G			= 103,
	DEF_KEY_H			= 104,
	DEF_KEY_I			= 105,
	DEF_KEY_J			= 106,
	DEF_KEY_K			= 107,
	DEF_KEY_L			= 108,
	DEF_KEY_M			= 109,
	DEF_KEY_N			= 110,
	DEF_KEY_O			= 111,
	DEF_KEY_P			= 112,
	DEF_KEY_Q			= 113,
	DEF_KEY_R			= 114,
	DEF_KEY_S			= 115,
	DEF_KEY_T			= 116,
	DEF_KEY_U			= 117,
	DEF_KEY_V			= 118,
	DEF_KEY_W			= 119,
	DEF_KEY_X			= 120,
	DEF_KEY_Y			= 121,
	DEF_KEY_Z			= 122,
	DEF_KEY_DELETE		= 127,
	/* End of ASCII mapped keysyms */
	/*@}*/

	/** @name International keyboard syms */
	/*@{*/
	DEF_KEY_WORLD_0		= 160,		/* 0xA0 */
	DEF_KEY_WORLD_1		= 161,
	DEF_KEY_WORLD_2		= 162,
	DEF_KEY_WORLD_3		= 163,
	DEF_KEY_WORLD_4		= 164,
	DEF_KEY_WORLD_5		= 165,
	DEF_KEY_WORLD_6		= 166,
	DEF_KEY_WORLD_7		= 167,
	DEF_KEY_WORLD_8		= 168,
	DEF_KEY_WORLD_9		= 169,
	DEF_KEY_WORLD_10		= 170,
	DEF_KEY_WORLD_11		= 171,
	DEF_KEY_WORLD_12		= 172,
	DEF_KEY_WORLD_13		= 173,
	DEF_KEY_WORLD_14		= 174,
	DEF_KEY_WORLD_15		= 175,
	DEF_KEY_WORLD_16		= 176,
	DEF_KEY_WORLD_17		= 177,
	DEF_KEY_WORLD_18		= 178,
	DEF_KEY_WORLD_19		= 179,
	DEF_KEY_WORLD_20		= 180,
	DEF_KEY_WORLD_21		= 181,
	DEF_KEY_WORLD_22		= 182,
	DEF_KEY_WORLD_23		= 183,
	DEF_KEY_WORLD_24		= 184,
	DEF_KEY_WORLD_25		= 185,
	DEF_KEY_WORLD_26		= 186,
	DEF_KEY_WORLD_27		= 187,
	DEF_KEY_WORLD_28		= 188,
	DEF_KEY_WORLD_29		= 189,
	DEF_KEY_WORLD_30		= 190,
	DEF_KEY_WORLD_31		= 191,
	DEF_KEY_WORLD_32		= 192,
	DEF_KEY_WORLD_33		= 193,
	DEF_KEY_WORLD_34		= 194,
	DEF_KEY_WORLD_35		= 195,
	DEF_KEY_WORLD_36		= 196,
	DEF_KEY_WORLD_37		= 197,
	DEF_KEY_WORLD_38		= 198,
	DEF_KEY_WORLD_39		= 199,
	DEF_KEY_WORLD_40		= 200,
	DEF_KEY_WORLD_41		= 201,
	DEF_KEY_WORLD_42		= 202,
	DEF_KEY_WORLD_43		= 203,
	DEF_KEY_WORLD_44		= 204,
	DEF_KEY_WORLD_45		= 205,
	DEF_KEY_WORLD_46		= 206,
	DEF_KEY_WORLD_47		= 207,
	DEF_KEY_WORLD_48		= 208,
	DEF_KEY_WORLD_49		= 209,
	DEF_KEY_WORLD_50		= 210,
	DEF_KEY_WORLD_51		= 211,
	DEF_KEY_WORLD_52		= 212,
	DEF_KEY_WORLD_53		= 213,
	DEF_KEY_WORLD_54		= 214,
	DEF_KEY_WORLD_55		= 215,
	DEF_KEY_WORLD_56		= 216,
	DEF_KEY_WORLD_57		= 217,
	DEF_KEY_WORLD_58		= 218,
	DEF_KEY_WORLD_59		= 219,
	DEF_KEY_WORLD_60		= 220,
	DEF_KEY_WORLD_61		= 221,
	DEF_KEY_WORLD_62		= 222,
	DEF_KEY_WORLD_63		= 223,
	DEF_KEY_WORLD_64		= 224,
	DEF_KEY_WORLD_65		= 225,
	DEF_KEY_WORLD_66		= 226,
	DEF_KEY_WORLD_67		= 227,
	DEF_KEY_WORLD_68		= 228,
	DEF_KEY_WORLD_69		= 229,
	DEF_KEY_WORLD_70		= 230,
	DEF_KEY_WORLD_71		= 231,
	DEF_KEY_WORLD_72		= 232,
	DEF_KEY_WORLD_73		= 233,
	DEF_KEY_WORLD_74		= 234,
	DEF_KEY_WORLD_75		= 235,
	DEF_KEY_WORLD_76		= 236,
	DEF_KEY_WORLD_77		= 237,
	DEF_KEY_WORLD_78		= 238,
	DEF_KEY_WORLD_79		= 239,
	DEF_KEY_WORLD_80		= 240,
	DEF_KEY_WORLD_81		= 241,
	DEF_KEY_WORLD_82		= 242,
	DEF_KEY_WORLD_83		= 243,
	DEF_KEY_WORLD_84		= 244,
	DEF_KEY_WORLD_85		= 245,
	DEF_KEY_WORLD_86		= 246,
	DEF_KEY_WORLD_87		= 247,
	DEF_KEY_WORLD_88		= 248,
	DEF_KEY_WORLD_89		= 249,
	DEF_KEY_WORLD_90		= 250,
	DEF_KEY_WORLD_91		= 251,
	DEF_KEY_WORLD_92		= 252,
	DEF_KEY_WORLD_93		= 253,
	DEF_KEY_WORLD_94		= 254,
	DEF_KEY_WORLD_95		= 255,		/* 0xFF */
	/*@}*/

	/** @name Numeric keypad */
	/*@{*/
	DEF_KEY_KP0		= 256,
	DEF_KEY_KP1		= 257,
	DEF_KEY_KP2		= 258,
	DEF_KEY_KP3		= 259,
	DEF_KEY_KP4		= 260,
	DEF_KEY_KP5		= 261,
	DEF_KEY_KP6		= 262,
	DEF_KEY_KP7		= 263,
	DEF_KEY_KP8		= 264,
	DEF_KEY_KP9		= 265,
	DEF_KEY_KP_PERIOD		= 266,
	DEF_KEY_KP_DIVIDE		= 267,
	DEF_KEY_KP_MULTIPLY	= 268,
	DEF_KEY_KP_MINUS		= 269,
	DEF_KEY_KP_PLUS		= 270,
	DEF_KEY_KP_ENTER		= 271,
	DEF_KEY_KP_EQUALS		= 272,
	/*@}*/

	/** @name Arrows + Home/End pad */
	/*@{*/
	DEF_KEY_UP			= 273,
	DEF_KEY_DOWN		= 274,
	DEF_KEY_RIGHT		= 275,
	DEF_KEY_LEFT		= 276,
	DEF_KEY_INSERT		= 277,
	DEF_KEY_HOME		= 278,
	DEF_KEY_END		= 279,
	DEF_KEY_PAGEUP		= 280,
	DEF_KEY_PAGEDOWN		= 281,
	/*@}*/

	/** @name Function keys */
	/*@{*/
	DEF_KEY_F1			= 282,
	DEF_KEY_F2			= 283,
	DEF_KEY_F3			= 284,
	DEF_KEY_F4			= 285,
	DEF_KEY_F5			= 286,
	DEF_KEY_F6			= 287,
	DEF_KEY_F7			= 288,
	DEF_KEY_F8			= 289,
	DEF_KEY_F9			= 290,
	DEF_KEY_F10		= 291,
	DEF_KEY_F11		= 292,
	DEF_KEY_F12		= 293,
	DEF_KEY_F13		= 294,
	DEF_KEY_F14		= 295,
	DEF_KEY_F15		= 296,
	/*@}*/

	/** @name Key state modifier keys */
	/*@{*/
	DEF_KEY_NUMLOCK		= 300,
	DEF_KEY_CAPSLOCK		= 301,
	DEF_KEY_SCROLLOCK		= 302,
	DEF_KEY_RSHIFT		= 303,
	DEF_KEY_LSHIFT		= 304,
	DEF_KEY_RCTRL		= 305,
	DEF_KEY_LCTRL		= 306,
	DEF_KEY_RALT		= 307,
	DEF_KEY_LALT		= 308,
	DEF_KEY_RMETA		= 309,
	DEF_KEY_LMETA		= 310,
	DEF_KEY_LSUPER		= 311,		/**< Left "Windows" key */
	DEF_KEY_RSUPER		= 312,		/**< Right "Windows" key */
	DEF_KEY_MODE		= 313,		/**< "Alt Gr" key */
	DEF_KEY_COMPOSE		= 314,		/**< Multi-key compose key */
	/*@}*/

	/** @name Miscellaneous function keys */
	/*@{*/
	DEF_KEY_HELP		= 315,
	DEF_KEY_PRINT		= 316,
	DEF_KEY_SYSREQ		= 317,
	DEF_KEY_BREAK		= 318,
	DEF_KEY_MENU		= 319,
	DEF_KEY_POWER		= 320,		/**< Power Macintosh power key */
	DEF_KEY_EURO		= 321,		/**< Some european keyboards */
	DEF_KEY_UNDO		= 322,		/**< Atari keyboard has Undo */
	/*@}*/

	/* Add any other keys here */

	DEF_KEY_LAST
} DefKey;

typedef struct{
	Uint32 codeKey;
}EventKey,EventRepeatKey;


class Input{
public:

	static void update();
	static bool getKey(DefKey _key_id);
	static bool getKeyR(DefKey _key_id);
	

	

};
