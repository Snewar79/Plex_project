#pragma once

#include "TRoot.h"

class TPoint : public TRoot
{

protected :
	int x, y;



public:
	void show(System::Drawing::Graphics^ gr, System::Drawing::Color);
	void hide(System::Drawing::Graphics^ gr, System::Drawing::Color);
	void move(System::Drawing::Graphics^ gr, System::Drawing::Color, System::Drawing::Color, int dx, int dy);

	int getX()
	{
		return x;	
	}
	int getY()
	{
		return y;	
	}

	void setX(int _x)
	{
		x = _x;
	}

	void setY(int _y)
	{
		y = _y;
	}

	void setVisible()
	{
		visible = true;
	}

	void setUnVisiuble()
	{
		visible = false;
	}




};