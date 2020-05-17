#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\Output.h"
#include <string>
#include <vector>

//Base class for all figures
class CFigure
{
protected:
	static int ID_C; //virtual ID shared between all figures
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	bool choosen;   //used in pick and hide mode

	
	/// Add more parameters if needed.

public:
	CFigure(GfxInfo FigureGfxInfo);
	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected

	virtual void Draw(Output* pOut) const  = 0 ;		//Draw the figure
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	void ChngBrdWdth(int width);    //changes the figure's boder width

	bool CheckForBound(Point p1,Point p2,Point p3);
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	

	virtual Point GetCenter()=0;
	virtual void Rotate(int degrees) = 0;	//Rotate the figure
	Point rotatebypoint(Point rotatedpoint, Point Center, int);
	virtual void Resize(float,float) = 0;	//Resize the figure
	virtual bool Move(int x,int y) = 0;		//Move the figure (return type is bool because it's needed in paste)
	virtual CFigure* Copy() = 0;  //make a copy from the selected item to copy 
	virtual CFigure*Paste() = 0;  //make a new object similar to the one in the clipboard
	virtual bool CheckCoordinates(int x, int y) = 0; //Check x,y in Figure
	virtual void Save(string filename) = 0; //save figure info
	virtual void Zoom()=0;

	int getID();
	void setID(int); //function used to re-set ID during loading
	static void setID_C(int ); //set total figure count to virtual ID
	static void decID_C(); //function to discrement the ID
	void setFillClr(string fillC);
	void setBorderClr(string BordC);
	string getFillClr();
	string getBorderClr();
	virtual bool CheckLine()=0; //returns true if fig type is line, used in change fill color to solve the problem of line dissappearing

	virtual void DeleteFig(Output *pOut) const=0;  //functions used in pick and hide mode
	virtual int getarea()=0;
	virtual string returntype()const =0;
    void setchoosen(bool B);
	bool ischoosen();
	bool CompareFilled(CFigure*Pointed) const;
	virtual void Shift(float)=0;
	virtual bool ChangePlace(int X,int Y)=0;
	virtual void DrawSF(Output* pOut) const  = 0 ;		//Draw figure in scramble and find mode (added because of zooming factor)
	virtual bool CheckCoordinates_SF(int x, int y) = 0; //Check co-ordinates for scramble and find (to avoid clashing with zoom)


	
	//virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file

	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
};

#endif