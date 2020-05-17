#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY,	//Playing mode
	MODE_PANDH, //Pick and hide mode
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_RECT,		//Recangle item in menu
	ITM_CIRC,		//Circle item in menu
	ITM_LINE,
	ITM_TRIANGLE,
	ITM_CHNGBK_CLR,
	ITM_CHNGDRW_CLR,
	ITM_CHNGFILL_CLR,
	ITM_CHNGBORDERWDTH,
	ITM_SELECT,
	ITM_RESIZE,
	ITM_ZOOM,
	ITM_ROTATE,
	ITM_BACK_FRONT_SWAP,
	ITM_DELETE,
	ITM_MOVE,
	ITM_CPY,
	ITM_CUT,
	ITM_PASTE,
	ITM_SAVE,
	ITM_LOAD,
	ITM_SWITCH_TO_PLAY,

	//TODO: Add more items names here

	ITM_EXIT,		//Exit item
	
	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	
	//TODO: Add more items names here

	ITM_PICK_HIDE,
	ITM_SCRAMBLE_FIND,
	ITM_SWITCH_TO_DRAW,
	

	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};

enum   PandH   //items of pick and hide 
{
	ITM_BYTYPE,
	ITM_BYCOLOR,
	ITM_BYTYPECOLOR,
	ITM_BYAREA,
	ITM_BACK,
};


__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	
	int	width, height,	//Window width and height
		wx , wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;		//Width of each item in toolbar menu
	

	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	string fillClr;
	string drawClr;
	string BkGrndClr;
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	color ToolBarColor;
	int PenWidth;			//width of the pen that draws shapes
	int ZoomFactor;

	/// Add more members if needed
	
}UI;	//create a global object UI

#endif