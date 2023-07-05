#include "reference_win.h"

#include <fstream>
#include <sstream>

#using <System.dll>	 
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Drawing;

ReferenceWin::ReferenceWin(void) {
	InitializeComponent();
}

ReferenceWin::~ReferenceWin() {
	if (components) {
		delete components;
	}
}

void  ReferenceWin::InitializeComponent(void) {
	this->SuspendLayout();

	Size = ::Size(600, 700);
	Text = "BatchEdit v1.0.0 Reference";
	this->Load += gcnew System::EventHandler(this, &ReferenceWin::onReferenceWinLoad);

	array<Control^>^ ctrls = (gcnew array<Control^>(1) {

	});

	Controls->AddRange(ctrls);

	this->ResumeLayout(false);
	this->PerformLayout();
}

void ReferenceWin::onReferenceWinLoad(System::Object^ sender, System::EventArgs^ e)
{
	// Load the Markdown file
	std::ifstream file("docs/batch_cmd_ref.md");
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string markdownContent = buffer.str();

	// Convert the Markdown to HTML
	// You'll need a Markdown-to-HTML library for this step,
	// such as markdown-it or marked. Make sure to include
	// the necessary headers and link against the library.

	// Assuming you have converted the Markdown to HTML
	// and stored it in the 'htmlContent' variable.

	reference_browser = gcnew System::Windows::Forms::WebBrowser();
	// Display the HTML content in the WebBrowser control
	//reference_browser->DocumentText = gcnew System::String(htmlContent.c_str());
}
