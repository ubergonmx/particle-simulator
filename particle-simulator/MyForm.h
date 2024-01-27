#pragma once

namespace particlesimulator {

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
		Graphics^ g;
		bool cursorMoving = false;
		Pen^ cursorPen;
		int cursorX, cursorY = -1;


	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			g = canvas->CreateGraphics();
			cursorPen = gcnew Pen(Color::Black);
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
	private: System::Windows::Forms::Panel^ canvas;
	private: System::Windows::Forms::Label^ titleLbl;
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
			this->canvas = (gcnew System::Windows::Forms::Panel());
			this->titleLbl = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// canvas
			// 
			this->canvas->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->canvas->Location = System::Drawing::Point(0, 0);
			this->canvas->Name = L"canvas";
			this->canvas->Size = System::Drawing::Size(1280, 760);
			this->canvas->TabIndex = 0;
			this->canvas->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::canvas_MouseDown);
			this->canvas->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::canvas_MouseMove);
			this->canvas->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::canvas_MouseUp);
			// 
			// titleLbl
			// 
			this->titleLbl->AutoSize = true;
			this->titleLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->titleLbl->Location = System::Drawing::Point(1305, 9);
			this->titleLbl->Name = L"titleLbl";
			this->titleLbl->Size = System::Drawing::Size(398, 55);
			this->titleLbl->TabIndex = 1;
			this->titleLbl->Text = L"Particle Simulator";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1728, 760);
			this->Controls->Add(this->titleLbl);
			this->Controls->Add(this->canvas);
			this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->Name = L"MyForm";
			this->Text = L"Particle Simulator - Mangoba, Palpallatoc";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void canvas_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		cursorMoving = true;
		cursorX = e->X;
		cursorY = e->Y;
	}
	private: System::Void canvas_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		cursorMoving = false;
		cursorX = -1;
		cursorY = -1;
	}
	private: System::Void canvas_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (cursorX != 1 && cursorY != -1 && cursorMoving) {
			g->DrawLine(cursorPen, cursorX, cursorY, e->X, e->Y);
			cursorX = e->X;
			cursorY = e->Y;
		}
	}
	};
}
