


#include "TPoint.h"



void TPoint::show(System::Drawing::Graphics^ gr, System::Drawing::Color sc)
{
	
	if (visible)
		gr->DrawEllipse(gcnew System::Drawing::Pen(sc), x - 2, y - 2, 4, 4);

}


void TPoint::hide(System::Drawing::Graphics^ gr, System::Drawing::Color hc)
{

	gr->DrawEllipse(gcnew System::Drawing::Pen(hc), x - 2, y - 2, 4, 4);
}


void TPoint::move(System::Drawing::Graphics^ gr, System::Drawing::Color hc, System::Drawing::Color sc, int dx, int dy)
{

	if (visible)
		hide(gr, System::Drawing::Color::White);

	x += dx;
	y += dy;

	if (visible)
		show(gr, System::Drawing::Color::Blue);
}