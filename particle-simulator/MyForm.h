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
	private: System::Windows::Forms::Label^ titleLbl;
	private: System::Windows::Forms::Button^ clearBtn;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
		   Color dvdLogoColor;

	public:
		MyForm(void)
		{
			InitializeComponent();

			// Initialize the graphics object and the cursor pen
			g = canvas->CreateGraphics();
			bitmap = gcnew Bitmap(canvas->Width, canvas->Height);
			cursorPen = gcnew Pen(Color::Black);

			// Initialize the DVD logo and its velocity
			dvdLogo = Rectangle(0, 0, 20, 20);
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

			// Check for collisions with the bitmap
			Color background = Color::FromArgb(0,0,0,0);
			if (dvdLogo.Left >= 0 && dvdLogo.Right < bitmap->Width && dvdLogo.Top >= 0 && dvdLogo.Bottom < bitmap->Height)
			{
				Color topLeft = bitmap->GetPixel(dvdLogo.Left, dvdLogo.Top);
				Color topRight = bitmap->GetPixel(dvdLogo.Right, dvdLogo.Top);
				Color bottomLeft = bitmap->GetPixel(dvdLogo.Left, dvdLogo.Bottom);
				Color bottomRight = bitmap->GetPixel(dvdLogo.Right, dvdLogo.Bottom);				
				if (topLeft != background || topRight != background || bottomLeft != background || bottomRight != background)
				{
					// If the DVD logo hit a drawing, reverse its velocity and change its color
					velocity.X = -velocity.X;
					velocity.Y = -velocity.Y;
					dvdLogoColor = System::Drawing::Color::FromArgb(255, rand() % 256, rand() % 256, rand() % 256);
				}
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
			this->clearBtn = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// canvas
			// 
			this->canvas->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->canvas->Location = System::Drawing::Point(0, 0);
			this->canvas->Name = L"canvas";
			this->canvas->Size = System::Drawing::Size(582, 440);
			this->canvas->TabIndex = 0;
			this->canvas->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::canvas_Paint);
			this->canvas->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::canvas_MouseDown);
			this->canvas->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::canvas_MouseMove);
			this->canvas->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::canvas_MouseUp);
			// 
			// titleLbl
			// 
			this->titleLbl->AutoSize = true;
			this->titleLbl->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->titleLbl->Location = System::Drawing::Point(588, 9);
			this->titleLbl->Name = L"titleLbl";
			this->titleLbl->Size = System::Drawing::Size(397, 65);
			this->titleLbl->TabIndex = 1;
			this->titleLbl->Text = L"Particle Simulator";
			// 
			// clearBtn
			// 
			this->clearBtn->Location = System::Drawing::Point(604, 352);
			this->clearBtn->Name = L"clearBtn";
			this->clearBtn->Size = System::Drawing::Size(254, 62);
			this->clearBtn->TabIndex = 2;
			this->clearBtn->Text = L"Clear drawings";
			this->clearBtn->UseVisualStyleBackColor = true;
			this->clearBtn->Click += gcnew System::EventHandler(this, &MyForm::clearBtn_Click);
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(598, 88);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(388, 148);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Using .NET Framework (WinForms) to simulate physics.";
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(598, 281);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(353, 68);
			this->label2->TabIndex = 4;
			this->label2->Text = L"You can paint on the canvas (blue area) to draw walls";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(144, 144);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size(999, 440);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->clearBtn);
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

				// canvas->Invalidate();
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

private: System::Void clearBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	bitmap = gcnew Bitmap(canvas->Width, canvas->Height);
}
};

}
