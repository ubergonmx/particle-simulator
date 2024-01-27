#pragma once
#include <cstdlib>

namespace particlesimulator
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
public
	ref class MyForm : public System::Windows::Forms::Form
	{
		Graphics ^ g;
		Bitmap ^ bitmap;
		bool cursorMoving = false;
		Pen ^ cursorPen;
		int cursorX, cursorY = -1;

		Rectangle dvdLogo;
		Point velocity;
		Color dvdLogoColor;

	public:
		MyForm(void)
		{
			InitializeComponent();

			// Initialize the graphics object and the cursor pen
			g = canvas->CreateGraphics();
			bitmap = gcnew Bitmap(canvas->Width, canvas->Height);
			cursorPen = gcnew Pen(Color::Black);

			// Initialize the list of drawings

			// Initialize the DVD logo and its velocity
			dvdLogo = Rectangle(0, 0, 100, 50);
			dvdLogoColor = Color::Red;
			velocity = Point(5, 5);

			// Create and start the timer
			Timer ^ timer = gcnew Timer();
			timer->Interval = 20; // 20 ms = 50 frames per second
			timer->Tick += gcnew System::EventHandler(this, &MyForm::timer_Tick);
			timer->Start();
		}

	private:
		void timer_Tick(System::Object ^ sender, System::EventArgs ^ e)
		{
			// Update the DVD logo's position
			dvdLogo.X += velocity.X;
			dvdLogo.Y += velocity.Y;

			// If the DVD logo hits the edge of the canvas, reverse its velocity
			if (dvdLogo.Left < 0 || dvdLogo.Right > canvas->Width)
			{
				velocity.X = -velocity.X;
				dvdLogoColor = Color::FromArgb(255, rand() % 256, rand() % 256, rand() % 256);
			}
			if (dvdLogo.Top < 0 || dvdLogo.Bottom > canvas->Height)
			{
				velocity.Y = -velocity.Y;
				dvdLogoColor = Color::FromArgb(255, rand() % 256, rand() % 256, rand() % 256);
			}
			// Redraw the canvas
			canvas->Invalidate();
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

	private:
		System::Windows::Forms::Panel ^ canvas;

	private:
		System::Windows::Forms::Label ^ titleLbl;

	protected:
	protected:
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->canvas = (gcnew System::Windows::Forms::Panel());
			this->titleLbl = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			//
			// canvas
			//
			this->canvas->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->canvas->Location = System::Drawing::Point(0, 0);
			this->canvas->Name = L"canvas";
			this->canvas->Size = System::Drawing::Size(800, 640);
			this->canvas->TabIndex = 0;
			this->canvas->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::canvas_Paint);
			this->canvas->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::canvas_MouseDown);
			this->canvas->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::canvas_MouseMove);
			this->canvas->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::canvas_MouseUp);
			//
			// titleLbl
			//
			this->titleLbl->AutoSize = true;
			this->titleLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
																static_cast<System::Byte>(0)));
			this->titleLbl->Location = System::Drawing::Point(815, 9);
			this->titleLbl->Name = L"titleLbl";
			this->titleLbl->Size = System::Drawing::Size(398, 55);
			this->titleLbl->TabIndex = 1;
			this->titleLbl->Text = L"Particle Simulator";
			//
			// MyForm
			//
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size(1258, 644);
			this->Controls->Add(this->titleLbl);
			this->Controls->Add(this->canvas);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
													  static_cast<System::Byte>(0)));
			this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Particle Simulator - Mangoba, Palpallatoc";
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion

	private:
		System::Void canvas_MouseDown(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
		{
			cursorMoving = true;
			cursorX = e->X;
			cursorY = e->Y;
		}

	private:
		System::Void canvas_MouseUp(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
		{
			cursorMoving = false;
			cursorX = -1;
			cursorY = -1;
		}

	private:
		System::Void canvas_MouseMove(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
		{
			if (cursorX != 1 && cursorY != -1 && cursorMoving)
			{
				Graphics ^ g_bitmap = Graphics::FromImage(bitmap);
				g_bitmap->DrawLine(cursorPen, cursorX, cursorY, e->X, e->Y);

				delete g_bitmap;

				cursorX = e->X;
				cursorY = e->Y;

				canvas->Invalidate();
			}
		}

	private:
		System::Void canvas_Paint(System::Object ^ sender, System::Windows::Forms::PaintEventArgs ^ e)
		{
			// Draw the bitmap
			e->Graphics->DrawImage(bitmap, 0, 0);

			// Draw the DVD logo
			g->FillRectangle(gcnew SolidBrush(dvdLogoColor), dvdLogo);
		}
	};

}
