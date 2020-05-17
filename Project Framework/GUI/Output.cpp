#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1350;
	UI.height = 600;
	UI.wx = 5;
	UI.wy =5;


	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 70;
	UI.MenuItemWidth = 60;
	
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.ToolBarColor = WHITE;
	UI.PenWidth = 3;	//width of the figures frames
	UI.ZoomFactor = 1;
	
	UI.BkGrndClr = "LIGHTGOLDENRODYELLOW";
	UI.drawClr = "BLUE";
	UI.fillClr = "GREEN";

	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\Menu_Rect.jpg";
	MenuItemImages[ITM_CIRC] = "images\\MenuItems\\Menu_Circ.jpg";
	MenuItemImages[ITM_LINE] = "images\\MenuItems\\Menu_Line.jpg";
	MenuItemImages[ITM_TRIANGLE] = "images\\MenuItems\\Menu_Tri.jpg";
	MenuItemImages[ITM_CHNGBK_CLR] = "images\\MenuItems\\CHNGBK_CLR.jpg";
	MenuItemImages[ITM_CHNGDRW_CLR] = "images\\MenuItems\\CHNGDRW_CLR.jpg";
	MenuItemImages[ITM_CHNGFILL_CLR] = "images\\MenuItems\\CHNGFILL_CLR.jpg";
	MenuItemImages[ITM_CHNGBORDERWDTH] = "images\\MenuItems\\borderWidth.jpg";
	MenuItemImages[ITM_SELECT] = "images\\MenuItems\\Menu_Select.jpg";
    MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\resize.jpg";

	MenuItemImages[ITM_ZOOM] = "images\\MenuItems\\zoom.jpg";
	MenuItemImages[ITM_ROTATE] = "images\\MenuItems\\rotate.jpg";
	MenuItemImages[ITM_BACK_FRONT_SWAP] = "images\\MenuItems\\backfront.jpg";

	MenuItemImages[ITM_DELETE] = "images\\MenuItems\\delete.jpg";
	MenuItemImages[ITM_MOVE] = "images\\MenuItems\\move.jpg";
	MenuItemImages[ITM_CPY] = "images\\MenuItems\\copy.jpg";
	MenuItemImages[ITM_CUT] = "images\\MenuItems\\cut.jpg";
	MenuItemImages[ITM_PASTE] = "images\\MenuItems\\paste.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\load.jpg";
	MenuItemImages[ITM_SWITCH_TO_PLAY] = "images\\MenuItems\\playmode.jpg";

	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	//Clear Tool bar by drawing a filled white rectangle
	pWind->SetPen(UI.ToolBarColor, 1);
	pWind->SetBrush(UI.ToolBarColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

	UI.InterfaceMode = MODE_PLAY;

	string MenuItemImages[PLAY_ITM_COUNT];

	///TODO: write code to create Play mode menu

	MenuItemImages[ITM_PICK_HIDE] = "images\\MenuItems\\pick_hide.jpg";
	MenuItemImages[ITM_SCRAMBLE_FIND] = "images\\MenuItems\\scramble.jpg";
	MenuItemImages[ITM_SWITCH_TO_DRAW] = "images\\MenuItems\\back.jpg";

	//Draw menu item one image at a time
	for(int i=0; i<PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePandHToolBar() const
{
	//Clear Tool bar by drawing a filled white rectangle
	pWind->SetPen(UI.ToolBarColor, 1);
	pWind->SetBrush(UI.ToolBarColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

	UI.InterfaceMode = MODE_PANDH;

	string MenuItemImages[5];

	///TODO: write code to create Play mode menu

	MenuItemImages[ITM_BYTYPE] = "images\\MenuItems\\by_type.jpg";
	MenuItemImages[ITM_BYCOLOR] = "images\\MenuItems\\by_colour.jpg";
	MenuItemImages[ITM_BYTYPECOLOR] = "images\\MenuItems\\bycolourandtype.jpg";
	MenuItemImages[ITM_BYAREA] = "images\\MenuItems\\by_area.jpg";
	MenuItemImages[ITM_BACK] = "images\\MenuItems\\back.jpg";

	//Draw menu item one image at a time
	for(int i=0; i<5; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drwawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int Output::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

string Output::getCrntFillClrString() const
{
	return UI.fillClr;
}

string Output::getCrntBordClrString() const
{
	return UI.drawClr;
}

color Output::getCrntBgrndColor() const
{ return UI.BkGrndColor;}


//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
	
}


void Output::DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = LineGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, LineGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (LineGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(LineGfxInfo.FillClr);
	}
	else	
		style = FRAME;
	
	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, style);
	
}

void Output::DrawTri(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = TriGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, TriGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (TriGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(TriGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
	
}


void Output::DrawCirc(Point P1, double R, GfxInfo CircGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = CircGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, CircGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (CircGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(CircGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawCircle(P1.x, P1.y,R, style);
	
}

void Output::DrawResizeBar() const
{
	pWind->DrawImage("images\\MenuItems\\ResizeBar\\quarter.jpg", ITM_RESIZE*UI.MenuItemWidth, UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\ResizeBar\\half.jpg", ITM_RESIZE*UI.MenuItemWidth, 2 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\ResizeBar\\two.jpg", ITM_RESIZE*UI.MenuItemWidth, 3 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\ResizeBar\\four.jpg", ITM_RESIZE*UI.MenuItemWidth, 4 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
}
void Output::DrawZoomBar()const
{
	pWind->DrawImage("images\\MenuItems\\ZoomBar\\zoomin.jpg", ITM_ZOOM*UI.MenuItemWidth, UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\ZoomBar\\zoomout.jpg", ITM_ZOOM*UI.MenuItemWidth, 2 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
}

void Output::DrawZoomToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\Menu_Rect.jpg";
	MenuItemImages[ITM_CIRC] = "images\\MenuItems\\Menu_Circ.jpg";
	MenuItemImages[ITM_LINE] = "images\\MenuItems\\Menu_Line.jpg";
	MenuItemImages[ITM_TRIANGLE] = "images\\MenuItems\\Menu_Tri.jpg";
	MenuItemImages[ITM_CHNGBK_CLR] = "images\\MenuItems\\CHNGBK_CLR.jpg";
	MenuItemImages[ITM_CHNGDRW_CLR] = "images\\MenuItems\\CHNGDRW_CLR.jpg";
	MenuItemImages[ITM_CHNGFILL_CLR] = "images\\MenuItems\\CHNGFILL_CLR.jpg";
	MenuItemImages[ITM_CHNGBORDERWDTH] = "images\\MenuItems\\borderWidth.jpg";
	MenuItemImages[ITM_SELECT] = "images\\MenuItems\\Menu_Select.jpg";
    MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\resize.jpg";

	MenuItemImages[ITM_ZOOM] = "images\\MenuItems\\zoom.jpg";
	MenuItemImages[ITM_ROTATE] = "images\\MenuItems\\rotate.jpg";
	MenuItemImages[ITM_BACK_FRONT_SWAP] = "images\\MenuItems\\backfront.jpg";

	MenuItemImages[ITM_DELETE] = "images\\MenuItems\\delete.jpg";
	MenuItemImages[ITM_MOVE] = "images\\MenuItems\\move.jpg";
	MenuItemImages[ITM_CPY] = "images\\MenuItems\\ZoomBar\\copyZ.jpg";
	MenuItemImages[ITM_CUT] = "images\\MenuItems\\ZoomBar\\cutZ.jpg";
	MenuItemImages[ITM_PASTE] = "images\\MenuItems\\ZoomBar\\pasteZ.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\load.jpg";
	MenuItemImages[ITM_SWITCH_TO_PLAY] = "images\\MenuItems\\ZoomBar\\playmodeZ.jpg";

	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";


	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}

void Output::DrawRotateBar() const
{
	pWind->DrawImage("images\\MenuItems\\RotateBar\\rotate90.jpg", ITM_ROTATE*UI.MenuItemWidth, UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\RotateBar\\rotate180.jpg", ITM_ROTATE*UI.MenuItemWidth, 2 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\RotateBar\\rotate270.jpg", ITM_ROTATE*UI.MenuItemWidth, 3 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);

}

void Output::CreateColorPalette() const
{
	pWind->DrawImage("images\\MenuItems\\Colors\\white.jpg", ITM_CHNGBK_CLR*UI.MenuItemWidth, UI.ToolBarHeight + 2, 0.5* UI.MenuItemWidth, 0.5*UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\Colors\\gray.jpg", ITM_CHNGBK_CLR*UI.MenuItemWidth *1.127,  UI.ToolBarHeight + 2, 0.5*UI.MenuItemWidth, 0.5*UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\Colors\\Black.jpg", ITM_CHNGBK_CLR*UI.MenuItemWidth *1.252, UI.ToolBarHeight + 2, 0.5*UI.MenuItemWidth, 0.5*UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\Colors\\brown.jpg", ITM_CHNGBK_CLR*UI.MenuItemWidth *1.376, UI.ToolBarHeight + 2, 0.5*UI.MenuItemWidth, 0.5*UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\Colors\\red.jpg", ITM_CHNGBK_CLR*UI.MenuItemWidth   *1.498, UI.ToolBarHeight + 2, 0.5* UI.MenuItemWidth, 0.5*UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\Colors\\orange.jpg", ITM_CHNGBK_CLR*UI.MenuItemWidth *1.622,  UI.ToolBarHeight + 2, 0.5*UI.MenuItemWidth, 0.5*UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\Colors\\yellow.jpg", ITM_CHNGBK_CLR*UI.MenuItemWidth, UI.ToolBarHeight + 37, 0.5*UI.MenuItemWidth, 0.5*UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\Colors\\pale yellow.jpg", ITM_CHNGBK_CLR*UI.MenuItemWidth *1.127, UI.ToolBarHeight + 37, 0.5*UI.MenuItemWidth, 0.5*UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\Colors\\green.jpg", ITM_CHNGBK_CLR*UI.MenuItemWidth *1.252, UI.ToolBarHeight + 37, 0.5* UI.MenuItemWidth, 0.5*UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\Colors\\Turquoise.jpg", ITM_CHNGBK_CLR*UI.MenuItemWidth *1.376,  UI.ToolBarHeight + 37, 0.5*UI.MenuItemWidth, 0.5*UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\Colors\\skyblue.jpg", ITM_CHNGBK_CLR*UI.MenuItemWidth *1.498, UI.ToolBarHeight + 37, 0.5*UI.MenuItemWidth, 0.5*UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\Colors\\blue.jpg", ITM_CHNGBK_CLR*UI.MenuItemWidth *1.622, UI.ToolBarHeight + 37, 0.5*UI.MenuItemWidth, 0.5*UI.ToolBarHeight);

}

void Output::CreateBorderWidthBar() const
{
	pWind->DrawImage("images\\MenuItems\\penWidth\\3.jpg", ITM_CHNGBORDERWDTH*UI.MenuItemWidth, UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\penWidth\\5.jpg", ITM_CHNGBORDERWDTH*UI.MenuItemWidth, 2 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\penWidth\\7.jpg", ITM_CHNGBORDERWDTH*UI.MenuItemWidth, 3 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\penWidth\\9.jpg", ITM_CHNGBORDERWDTH*UI.MenuItemWidth, 4 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\penWidth\\11.jpg", ITM_CHNGBORDERWDTH*UI.MenuItemWidth, 5 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
}

void Output::setCrntDrawColor(color C, string Clr)
{
	UI.DrawColor = C;
	UI.drawClr = Clr;
}

bool Output::setCrntFillColor(color C, string Clr)
{
	UI.FillColor = C;
	UI.fillClr = Clr;
	return true;
}

void Output::setCrntPenWidth(int width)
{
	UI.PenWidth = width;
}

//functions for pick and hide
void Output::PrintMessage(string msg,int size) const	//Prints a message on status bar
{
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(size, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}

void Output::Drawint(const int x,const int y,const long lNumber )
{
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(30, BOLD , BY_NAME, "Arial");   
	pWind->DrawInteger(x,y,lNumber);
}
void Output ::PrintNumber(int k,int size) const
{
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawInteger(size, UI.height - (int)(UI.StatusBarHeight/1.5), k);

}
void Output::Drawstring(const int x,const int y,string msg)
{
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(30, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(x,y,msg);
}

void Output:: DeleteRect(Point P1,Point P2, GfxInfo RectGfxInfo) const
{	
	color DrawingClr;
	RectGfxInfo.DrawClr = getCrntBgrndColor();
	DrawingClr=getCrntBgrndColor();
	
	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(getCrntBgrndColor());
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

  }

void Output:: DeleteLine(Point P1,Point P2, GfxInfo LineGfxInfo) const 
{
	color DrawingClr;
	
	LineGfxInfo.DrawClr = getCrntBgrndColor();
	DrawingClr=getCrntBgrndColor();
	
	pWind->SetPen(DrawingClr, LineGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (LineGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(getCrntBgrndColor());
	}
	else	
		style = FRAME;

	
	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, style);
}

void Output:: DeleteTri(Point P1,Point P2,Point P3, GfxInfo TriGfxInfo) const 
{
	color DrawingClr;
	
	TriGfxInfo.DrawClr = getCrntBgrndColor();
	DrawingClr=getCrntBgrndColor();
	
	pWind->SetPen(DrawingClr, TriGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (TriGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(getCrntBgrndColor());
	}
	else	
		style = FRAME;

	
	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y,P3.x,P3.y, style);
}


void Output:: DeleteCirc(Point P1,double R, GfxInfo CircGfxInfo) const 
{
	color DrawingClr;
	
	CircGfxInfo.DrawClr = getCrntBgrndColor();
	DrawingClr=getCrntBgrndColor();
	
	pWind->SetPen(DrawingClr, CircGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (CircGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(getCrntBgrndColor());
	}
	else	
		style = FRAME;

	
	pWind->DrawCircle(P1.x, P1.y, R, style);
}



//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

