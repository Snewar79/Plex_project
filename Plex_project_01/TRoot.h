#pragma once



class TRoot
{

	protected :		
	
		bool visible;


	public:

		virtual void show(System::Drawing::Graphics^ gr, System::Drawing::Color) = 0;
		virtual void hide(System::Drawing::Graphics^ gr, System::Drawing::Color) = 0;
		virtual void move(System::Drawing::Graphics^ gr, System::Drawing::Color, System::Drawing::Color,  int, int) = 0;
		void setVisible()
		{
			visible = true;
		}

		void setUnVisible()
		{
			visible = false;
		}

		bool isVisible()
		{
			return visible;
		}

};