#pragma once

#include "TPoint.h"
#include <fstream>


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


	void saveChartToFile(std::string fileName);

	TPoint * saveChartRec(TRoot * chart, std::ofstream & file);




	void setEnd(TRoot * t)
	{
		end = t;
	}

	TPoint * showChartRec(System::Drawing::Graphics^ gr, TRoot * chart);
	
	void showChartIt(System::Drawing::Graphics^ gr, TRoot * chart, System::Drawing::Color cl);

	void hideChartIt(System::Drawing::Graphics^ gr, TRoot * chart, System::Drawing::Color cl);

	st findNear(int, int, double, TPoint * ch);
	
	st findAnyPoint(int x, int y, double eps, TPoint * curr);
	
	st findNearEdge(int x, int y, double eps);

	void showChartSingle(System::Drawing::Graphics^ gr, TRoot * chart, System::Drawing::Color cl);

};





struct st
{
	TChart * chart;
	TRoot * ps;
	TRoot * pe;

};
