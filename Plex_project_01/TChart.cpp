

#include "TChart.h"
#include <stdlib.h>
#include <stack>





void TChart::show(System::Drawing::Graphics^ gr, System::Drawing::Color)
{

	showChartIt(gr, this);
	
}

void TChart::hide(System::Drawing::Graphics^ gr, System::Drawing::Color)
{

	//showChart(gr, this);


}

void TChart::move(System::Drawing::Graphics^ gr, System::Drawing::Color, System::Drawing::Color, int, int)
{

	//showChart(gr, this);


}




TPoint * TChart::showChartRec(System::Drawing::Graphics^ gr, TRoot * chart)
{

	TChart * tmp;

	tmp = dynamic_cast<TChart*>(chart);
	
	if (tmp)
	{
		TPoint * st = NULL;
		TPoint * en = NULL;

		st = dynamic_cast<TPoint*>(tmp->start);
		en = dynamic_cast<TPoint*>(tmp->end);




		if (st == NULL)
			st = showChartRec(gr, tmp->start);
		if (en == NULL)
			en = showChartRec(gr, tmp->end);

		st->show(gr,System::Drawing::Color::Blue);
		en->show(gr, System::Drawing::Color::Blue);
		gr->DrawLine(System::Drawing::Pens::Black, st->getX(), st->getY(), en->getX(), en->getY());

		return en;
	}
	else
		throw -1;

}


void TChart::showChartIt(System::Drawing::Graphics^ gr, TRoot * chart)
{

	std::stack <st> bank;

	struct st bank_buf;

	bank_buf.chart = this;
	bank_buf.pe = NULL;
	bank_buf.ps = NULL;

	while (!bank.empty()) bank.pop(); //Clear stack

	bank.push(bank_buf);

	while (!bank.empty())
	{
		
		bank_buf = bank.top();

		TPoint* ts;
		TPoint* te;


		if (bank_buf.ps == NULL)
		{
			ts = dynamic_cast<TPoint*>(bank_buf.chart->start);
			if (ts != NULL)
				bank_buf.ps = ts;
		}
		else
		{
			ts = dynamic_cast<TPoint*>(bank_buf.ps);
		}

		if (bank_buf.pe == NULL)
			te = dynamic_cast<TPoint*>(bank_buf.chart->end);
		else
		{
			te = dynamic_cast<TPoint*>(bank_buf.pe);
		}

		if (ts == NULL)
		{
			bank_buf.chart = dynamic_cast<TChart*>(bank_buf.chart->start);
			bank_buf.pe = NULL;
			bank_buf.ps = NULL;
			bank.push(bank_buf);

			continue;
		}

		if (te == NULL)
		{
			bank.pop();
			bank.push(bank_buf);
			bank_buf.chart = dynamic_cast<TChart*>(bank_buf.chart->end);
			bank_buf.pe = NULL;
			bank_buf.ps = NULL;
			bank.push(bank_buf);

			continue;

		}

		if (ts && te)
		{
			TPoint * buffer;
			buffer = te;


			if (ts->isVisible() && te->isVisible() && bank_buf.chart->isVisible())
			gr->DrawLine(System::Drawing::Pens::Black, ts->getX(), ts->getY(), te->getX(), te->getY());
			
			if (ts->isVisible())
			ts->show(gr, System::Drawing::Color::Blue);


			if (te->isVisible())
			te->show(gr, System::Drawing::Color::Blue);

			bank.pop();

			if (bank.empty()) break;

			bank_buf = bank.top();

			if (bank_buf.ps == NULL)
			{
				bank_buf.ps = buffer;
				bank_buf.chart = bank.top().chart;
				bank.pop();
				bank.push(bank_buf);
			}
			else
			{
				bank_buf.pe = buffer;
				bank_buf.chart = bank.top().chart;
				bank.pop();
				bank.push(bank_buf);
			}

			continue;


		}







	}




}





st TChart::findNear(int x, int y, double eps, TPoint * curr)
{
	st out;
	out.chart = NULL;
	out.pe = NULL;
	out.ps = NULL;
	

	std::stack <st> bank;

	struct st bank_buf;

	bank_buf.chart = this;
	bank_buf.pe = NULL;
	bank_buf.ps = NULL;
	
	double last_dist;

	curr->setUnVisiuble();
	

	while (!bank.empty()) bank.pop(); //Clear fucking stack
	// another does not work 0_o

	bank.push(bank_buf);

	while (!bank.empty())
	{

		bank_buf = bank.top();

		TPoint* ts;
		TPoint* te;


		if (bank_buf.ps == NULL)
		{
			ts = dynamic_cast<TPoint*>(bank_buf.chart->start);
			if (ts != NULL)
				bank_buf.ps = ts;
		}
		else
		{
			ts = dynamic_cast<TPoint*>(bank_buf.ps);
		}

		if (bank_buf.pe == NULL)
			te = dynamic_cast<TPoint*>(bank_buf.chart->end);
		else
		{
			te = dynamic_cast<TPoint*>(bank_buf.pe);
		}

		if (ts == NULL)
		{
			bank_buf.chart = dynamic_cast<TChart*>(bank_buf.chart->start);
			bank_buf.pe = NULL;
			bank_buf.ps = NULL;
			bank.push(bank_buf);

			continue;
		}

		if (te == NULL)
		{
			bank.pop();
			bank.push(bank_buf);
			bank_buf.chart = dynamic_cast<TChart*>(bank_buf.chart->end);
			bank_buf.pe = NULL;
			bank_buf.ps = NULL;
			bank.push(bank_buf);

			continue;

		}

		if (ts && te)
		{
			TPoint * buffer;
			buffer = te;

			double rasst;

			

			
			rasst = (ts->getX() - x)*(ts->getX() - x)  +  (ts->getY() - y)*((ts->getY() - y));
			if ( !curr->isVisible() && rasst < eps || rasst < eps && rasst < last_dist )
			{
				last_dist = rasst;
				if (curr == NULL)
				{
					curr = new TPoint;
				}
				*curr = *ts;

				out.pe = NULL;
				out.ps = ts;
				out.chart = bank.top().chart;
			}

			rasst = (te->getX() - x)*(te->getX() - x)  +  (te->getY() - y)*((te->getY() - y));
			if (!curr->isVisible() && rasst < eps || rasst < eps && rasst < last_dist)
			{
				last_dist = rasst;
				if (curr == NULL)
				{
					curr = new TPoint;
				}
				*curr = *te;
				
				out.ps = NULL;
				out.pe = te;
				out.chart = bank.top().chart;


			}





			bank.pop();

			if (bank.empty()) break;

			bank_buf = bank.top();

			if (bank_buf.ps == NULL)
			{
				bank_buf.ps = buffer;
				bank_buf.chart = bank.top().chart;
				bank.pop();
				bank.push(bank_buf);
			}
			else
			{
				bank_buf.pe = buffer;
				bank_buf.chart = bank.top().chart;
				bank.pop();
				bank.push(bank_buf);
			}

			continue;


		}


	}








	return out;
}


st TChart::findAnyPoint(int x, int y, double eps, TPoint * point)
{
	st out;

	TPoint *outPoint;
	outPoint = dynamic_cast<TPoint*>(start);

	if (outPoint != NULL)
	{
		out.chart = this;
		out.ps = outPoint;
	}
	else
	{
		out = dynamic_cast<TChart*>(start)->findAnyPoint(x, y, eps, NULL);
	}


	return out;

}