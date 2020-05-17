#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"
#include <string>

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();		

	window* CreateWind(int, int, int , int) const; //creates the application window
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreatePandHToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar
	void DrawResizeBar() const;	//Create Resize Bar
	void DrawZoomBar() const; //create zoom bar
	void DrawZoomToolBar() const; //create special tool bar when zooming
	void DrawRotateBar() const;   //create rotate bar
	void CreateColorPalette() const; //Create color palette
	void CreateBorderWidthBar() const; //create border width bar

	Input* CreateInput() const; //creates a pointer to the Input object	
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	
	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a rectangle
	void DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo, bool selected=false) const;  //Draw a line
	void DrawTri(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo, bool selected=false) const;  //Draw a triangle
	void DrawCirc(Point P1, double R, GfxInfo CircGfxInfo, bool selected=false) const;  //Draw a circle


	///Make similar functions for drawing all other figures.
	
	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	 //get current drawing color
	color getCrntFillColor() const;	 //get current filling color
	color getCrntBgrndColor() const;  
	int getCrntPenWidth() const;    //get current pen width


	void setCrntDrawColor(color, string); //set current drawing color
	bool setCrntFillColor(color, string); //set current filling color
	void setCrntPenWidth(int);    //set current pen width
	  
	string getCrntFillClrString() const; //return the current fill color as a string
	string getCrntBordClrString() const; //return the current border color as a string

	void PrintMessage(string msg,int size) const;
	void Drawint(const int x,const int y,const long lNumber );
	void PrintNumber(int k,int size) const;
	void Drawstring(const int x,const int y,string msg);
	void DeleteRect(Point P1,Point P2, GfxInfo RectGfxInfo) const ;
	void DeleteLine(Point P1,Point P2, GfxInfo LineGfxInfo) const ;
	void DeleteTri(Point P1,Point P2,Point P3, GfxInfo RectGfxInfo) const ;
	void DeleteCirc(Point P1,double R, GfxInfo CircGfxInfo) const ;
	
	~Output();
};

#endif