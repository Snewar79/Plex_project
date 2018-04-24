

#include "TChart.h"
#include <stdlib.h>
#include <stack>



struct chart_str
{
	
	std::string start;
	std::string end;
	std::string visible;
};


struct point_str
{
	std::string visible;
	std::string start;
	std::string end;
};




void TChart::show(System::Drawing::Graphics^ gr, System::Drawing::Color cl)
{

	showChartIt(gr, this, cl);
	//showChartRec(gr, this);
}

void TChart::hide(System::Drawing::Graphics^ gr, System::Drawing::Color)
{

	hideChartIt(gr, this, System::Drawing::Color::White);


}

void TChart::move(System::Drawing::Graphics^ gr, System::Drawing::Color, System::Drawing::Color, int, int)
{

	//showChart(gr, this);


}


st TChart::findNearEdge(int x, int y, double eps)
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

	//curr->setUnVisiuble();


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




			rasst = System::Math::Abs( (ts->getX() - te->getX()) * (y - te->getY()) - (ts->getY() - te->getY()) * (x - te->getX()));	
			
			double a, b, c;
			
			a = (ts->getX() - x) * (ts->getX() - x) + (ts->getY() - y) * (ts->getY() - y);

			b = (te->getX() - x) * (te->getX() - x) + (te->getY() - y) * (te->getY() - y);

			c = (te->getX() - ts->getX()) * (te->getX() - ts->getX()) + (te->getY() - ts->getY()) * (te->getY() - ts->getY());


			bool not_sharply = false;


			if (b + c > a && c + a > b)
				not_sharply = true;



			if ( bank.top().chart->isVisible() && ((out.chart == NULL && rasst < eps || rasst < eps && rasst < last_dist) && not_sharply))
			{
				last_dist = rasst;
				if (out.chart == NULL)
				{
					out.chart = new TChart;
				}
				//out.chart = bank_buf.chart;
				//dynamic_cast<TPoint*>(out.chart)->setVisible();
				//out.pe = NULL;
				//out.ps = ts;
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


void TChart::hideChartIt(System::Drawing::Graphics^ gr, TRoot * chart, System::Drawing::Color cl)
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
			gr->DrawLine(System::Drawing::Pens::White, ts->getX(), ts->getY(), te->getX(), te->getY());
			
			if (ts->isVisible())
			ts->show(gr, System::Drawing::Color::White);


			if (te->isVisible())
			te->show(gr, System::Drawing::Color::White);

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


void TChart::saveChartToFile(std::string fileName)
{
	std::ofstream fout;

	fout.open(fileName);

	



	saveChartRec(this, fout);

	fout.close();

}

TPoint * TChart::saveChartRec(TRoot * chart, std::ofstream & file)
{

	TChart * tmp;
	TPoint * tmp_p;


	tmp = dynamic_cast<TChart*>(chart);

	if (tmp)
	{
		// if it's a chart


		file << "Chart " << tmp->start << " | " << tmp->end;
		if (chart->isVisible())
			file << " vis\n";
		else file << " unVis\n";
				
		TPoint * st = saveChartRec(tmp->start, file);
		TPoint * en = saveChartRec(tmp->end, file);

		


		

		return en;
	}

	else
	{
		tmp_p = dynamic_cast<TPoint*>(chart);
		if (tmp_p)
		{
			file << "Point " << chart << " " << tmp_p->getX() << " " << tmp_p->getY();
			if (chart->isVisible())
				file << " vis\n";
			else file << " unVis\n";



			return tmp_p;
		}


	}




}


TChart * TChart::openFromFile(std::string fileName)
{

	
	
	std::ifstream file;
	file.open(fileName);
	





	file.close();
	
	return 0;
}


void TChart::showChartSingle(System::Drawing::Graphics^ gr, TRoot * chart, System::Drawing::Color cl)
{
	TRoot *tmp;

	tmp = chart;

	TPoint * start, *end;

	start = dynamic_cast<TPoint*>(dynamic_cast<TChart*>(tmp)->start);

	end = dynamic_cast<TPoint*>(dynamic_cast<TChart*>(tmp)->end);


	if (start == NULL)
	{
		tmp = dynamic_cast<TChart*>(tmp)->start;
		while (start == NULL)
		{
			start = dynamic_cast<TPoint*>(dynamic_cast<TChart*>(tmp)->end);
			tmp = dynamic_cast<TChart*>(tmp)->end;
		}
	}

	if (end == NULL)
	{
		tmp = dynamic_cast<TChart*>(chart)->end;
		while (end == NULL)
		{
			end = dynamic_cast<TPoint*>(dynamic_cast<TChart*>(tmp)->end);
			tmp = dynamic_cast<TChart*>(tmp)->end;
		}


	}

	gr->DrawLine(gcnew System::Drawing::Pen(cl), start->getX(), start->getY(), end->getX(), end->getY());





}

void TChart::showChartIt(System::Drawing::Graphics^ gr, TRoot * chart, System::Drawing::Color cl)
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
			gr->DrawLine(gcnew System::Drawing::Pen(cl), ts->getX(), ts->getY(), te->getX(), te->getY());
			else bank.top().chart->setUnVisible();
			
			if (ts->isVisible())
			ts->show(gr, System::Drawing::Color::Blue);
			else bank.top().chart->setUnVisible();


			if (te->isVisible())
			te->show(gr, System::Drawing::Color::Blue);
			else bank.top().chart->setUnVisible();

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