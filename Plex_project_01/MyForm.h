#pragma once

#include "TPoint.h"
#include "TChart.h"
#include <stdlib.h>

namespace Plex_project_01 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			gr = CreateGraphics();
			mouse_flag_down = false;
			

			

			Curr = new TPoint();
			Curr->setX(0);
			Curr->setY(0);
			Curr->setUnVisiuble();


		}



	





	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}


		TPoint * p_arr = new TPoint[4];
		System::Drawing::Graphics^ gr;
		TChart * top = NULL;;
		
		int x1, y1;
		int x2, y2;
		
		bool mouse_flag_down;
		TPoint * Curr;

		













	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->ClientSize = System::Drawing::Size(1051, 553);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

//		
	}
private: System::Void MyForm_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

	x1 = e->X;
	y1 = e->Y;
	
	x2 = x1;
	y2 = y1;

	mouse_flag_down = true;



}
private: System::Void MyForm_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {


	if (top != NULL)
	{
		if (Curr->isVisible())
			Curr->hide(gr, System::Drawing::Color::Blue);
	//	top->show(gr, System::Drawing::Color::Black);
		top->findNear(e->X, e->Y, 40, Curr);
		if (Curr->isVisible())
			Curr->show(gr, System::Drawing::Color::Red);


	}
	
	
	






	if (mouse_flag_down)
	{
		gr->DrawLine(System::Drawing::Pens::White, x1, y1, x2, y2);

		x2 = e->X;
		y2 = e->Y;

		gr->DrawLine(System::Drawing::Pens::Black, x1, y1, x2, y2);
	}




	


	



}
private: System::Void MyForm_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

	gr->DrawLine(System::Drawing::Pens::White, x1, y1, x2, y2);
	mouse_flag_down = false;

	if (top == NULL)
	{
		top = new TChart;
		TPoint* tmp;
		tmp = new TPoint;
		tmp->setX(x1);
		tmp->setY(y1);
		tmp->setVisible();
		top->setSatrt(tmp);

		tmp = new TPoint;
		tmp->setX(x2);
		tmp->setY(y2);
		tmp->setVisible();
		top->setEnd(tmp);

		


	}
	else
	{

		TPoint *first = new TPoint();
		TPoint *second = new TPoint();

		first->setUnVisiuble();
		second->setUnVisiuble();

		st first_st;
		st second_st;
	
		first_st = top->findNear(x1, y1, 40, first);
		second_st = top->findNear(x2, y2, 40, second);

		if (first_st.chart == NULL && second_st.chart != NULL)
		{
			TChart *tmp = new TChart;
			if (second_st.pe != NULL)
			{
				tmp->setEnd(second_st.pe);
				TPoint * buf  = new TPoint;
				buf->setX(x1);
				buf->setY(y1);
				buf->setVisible();
				tmp->setSatrt(buf);
			}
			if (second_st.ps != NULL)
			{
				tmp->setEnd(second_st.ps);
				TPoint * buf = new TPoint;
				buf->setX(x1);
				buf->setY(y1);
				buf->setVisible();
				tmp->setSatrt(buf);
			}
			if (second_st.pe != NULL)
			{
				second_st.chart->setEnd(tmp);
			}
			if (second_st.ps != NULL)
			{
				second_st.chart->setSatrt(tmp);
			}


			
		}


		if (first_st.chart != NULL && second_st.chart == NULL)
		{
			TChart *tmp = new TChart;
			if (first_st.pe != NULL)
			{
				tmp->setEnd(first_st.pe);
				TPoint * buf = new TPoint;
				buf->setX(x2);
				buf->setY(y2);
				buf->setVisible();
				tmp->setSatrt(buf);
			}
			if (first_st.ps != NULL)
			{
				tmp->setEnd(first_st.ps);
				TPoint * buf = new TPoint;
				buf->setX(x2);
				buf->setY(y2);
				buf->setVisible();
				tmp->setSatrt(buf);
			}
			if (first_st.pe != NULL)
			{
				first_st.chart->setEnd(tmp);
			}
			if (first_st.ps != NULL)
			{
				first_st.chart->setSatrt(tmp);
			}



		}

		if (first_st.chart != NULL && second_st.chart != NULL)
		{
			TChart *tmp = new TChart;
			
			if (first_st.ps != NULL)
			{
				tmp->setEnd(first_st.ps);
			}
			else
			{
				tmp->setEnd(first_st.pe);
			}

			if (second_st.ps != NULL)
			{
				tmp->setSatrt(second_st.ps);
			}
			else
			{
				tmp->setSatrt(second_st.pe);
			}
			if (first_st.ps != NULL)
			{
				first_st.chart->setSatrt(tmp);
			}
			else
			{
				first_st.chart->setEnd(tmp);
			}

		}

		if (first_st.chart == NULL && second_st.chart == NULL)
		{
			TChart *tmp = new TChart;
			TChart *tmpR = new TChart;

			TPoint *fp = new TPoint;
			TPoint *sp = new TPoint;
			fp->setVisible();
			fp->setVisible();
			fp->setX(x1);
			fp->setY(y1);

			sp->setVisible();
			sp->setVisible();
			sp->setX(x2);
			sp->setY(y2);


			st rope = top->findAnyPoint(0, 0, 0, NULL);

			tmpR->setEnd(rope.ps);
			tmpR->setSatrt(fp);

			rope.chart->setSatrt(tmpR);
			
			tmpR->setUnVisible();

			tmp->setEnd(sp);
			tmp->setSatrt(fp);
			tmpR->setSatrt(tmp);




		}




	}



	top->show(gr, System::Drawing::Color::Black);

}
};
}
