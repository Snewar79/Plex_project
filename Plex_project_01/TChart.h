#pragma once

#include "TPoint.h"



struct st;


class TChart : public TRoot
{
protected :
	TRoot *start;
	TRoot *end;
	
public: 

	void show(System::Drawing::Graphics^ gr, System::Drawing::Color);
	void hide(System::Drawing::Graphics^ gr, System::Drawing::Color);
	void move(System::Drawing::Graphics^ gr, System::Drawing::Color, System::Drawing::Color, int, int);

	void setSatrt(TRoot * t)
	{
		start = t;
	}

	void setEnd(TRoot * t)
	{
		end = t;
	}

	TPoint * showChartRec(System::Drawing::Graphics^ gr, TRoot * chart);
	
	void showChartIt(System::Drawing::Graphics^ gr, TRoot * chart);

	st findNear(int, int, double, TPoint * ch);
	
	st findAnyPoint(int x, int y, double eps, TPoint * curr);
	
};





struct st
{
	TChart * chart;
	TRoot * ps;
	TRoot * pe;

};
