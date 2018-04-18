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
			highlightPoint = new TPoint;

			

			
			
			

			

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

		TPoint *currPoint;
		TChart *currChart;

		TPoint *highlightPoint;

		bool chartSelect;
		bool pointSelect;
		

		

		//TPoint * Curr;

		//TChart * currChart;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	protected:
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton3;

	protected:














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
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->SuspendLayout();
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(12, 12);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(80, 17);
			this->radioButton1->TabIndex = 0;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Draw Mode";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(12, 35);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(126, 17);
			this->radioButton2->TabIndex = 1;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Vertex Seletion Mode";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(12, 58);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(124, 17);
			this->radioButton3->TabIndex = 2;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"Edge selection mode";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->ClientSize = System::Drawing::Size(1051, 553);
			this->Controls->Add(this->radioButton3);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseUp);
			this->ResumeLayout(false);
			this->PerformLayout();

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


	if (radioButton1->Checked)
	{
		if (mouse_flag_down)
		{
			gr->DrawLine(System::Drawing::Pens::White, x1, y1, x2, y2);

			x2 = e->X;
			y2 = e->Y;

			gr->DrawLine(System::Drawing::Pens::Black, x1, y1, x2, y2);
		}

		st highlightPointSt;
		

		if (top != NULL) 
		{
			if (highlightPoint->isVisible())
			highlightPoint->hide(gr, System::Drawing::Color::Blue);

			highlightPointSt = top->findNear(e->X, e->Y, 50, highlightPoint);

			if (highlightPoint->isVisible())
				highlightPoint->show(gr, System::Drawing::Color::Red);
		}

	}


	if (radioButton2->Checked)
	{

		st highlightPointSt;


		if (top != NULL)
		{
			if (highlightPoint->isVisible())
				highlightPoint->hide(gr, System::Drawing::Color::Blue);
		
			highlightPointSt = top->findNear(e->X, e->Y, 50, highlightPoint);
		
			if (highlightPoint->isVisible())
				highlightPoint->show(gr, System::Drawing::Color::Red);
		}

		if (highlightPointSt.chart != NULL)
		{
			if (highlightPointSt.pe != NULL)
			{
				dynamic_cast<TPoint*>(highlightPointSt.pe)->setX(e->X);
				dynamic_cast<TPoint*>(highlightPointSt.pe)->setY(e->Y);
			}
			if (highlightPointSt.ps != NULL)
			{
				dynamic_cast<TPoint*>(highlightPointSt.ps)->setX(e->X);
				dynamic_cast<TPoint*>(highlightPointSt.ps)->setY(e->Y);
			}

		}


	}


	


	



}
private: System::Void MyForm_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

	mouse_flag_down = false;

	
	if (radioButton1->Checked)
	{
		gr->DrawLine(System::Drawing::Pens::White, x1, y1, x2, y2);
		

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
					TPoint * buf = new TPoint;
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
}
};
}
