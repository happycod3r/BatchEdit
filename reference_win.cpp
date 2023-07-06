
#using <System.dll>	 
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

#include "resource.h"
#include "reference_win.h"


using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Drawing;

ReferenceWin::ReferenceWin() {
	InitializeComponent();
}

ReferenceWin::~ReferenceWin() {
	if (components) {
		delete components;
	}
}

void ReferenceWin::InitializeComponent() {
	this->SuspendLayout();

	Size = ::Size(600, 700);
	Text = "BatchEdit v1.0.0 Reference";
	this->Load += gcnew System::EventHandler(this, &ReferenceWin::onReferenceWinLoad);

	reference_browser = gcnew WebBrowser();
	reference_browser->Size = ::Size(600, 630);
	reference_browser->Location = ::Point(0, 0);
	reference_browser->BackColor = SystemColors::ControlDark;

	forward = gcnew Button();
	forward->Size = ::Size(60, 50);
	forward->Location = ::Point(520, 620);
	forward->BackColor = ::Color::Red;
	forward->Text = "-->";
	forward->Click += gcnew System::EventHandler(this, &ReferenceWin::onForwardBtnClick);

	back = gcnew Button();
	back->Size = ::Size(60, 50);
	back->Location = ::Point(0, 620);
	back->BackColor = ::Color::Red;
	back->Text = "<--";
	back->Click += gcnew System::EventHandler(this, &ReferenceWin::onBackBtnClick);

	array<Control^>^ ctrls = (gcnew array<Control^>(3) {
		reference_browser,
			forward,
			back
	});

	Controls->AddRange(ctrls);

	this->ResumeLayout(false);
	this->PerformLayout();
}

void ReferenceWin::onReferenceWinLoad(System::Object^ sender, System::EventArgs^ e)
{
	reference_browser->Navigate("https://learn.microsoft.com/en-us/windows-server/administration/windows-commands/windows-commands");
	reference_browser->Show();
}

void ReferenceWin::onForwardBtnClick(System::Object^ sender, System::EventArgs^ e)
{
	if (!reference_browser->GoForward()) {
		// do something ...
	}
}

void ReferenceWin::onBackBtnClick(System::Object^ sender, System::EventArgs^ e)
{
	if (!reference_browser->GoBack()) {
		// do something ... 
	}
}

