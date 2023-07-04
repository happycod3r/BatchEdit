#include <cstdlib>
#using <mscorlib.dll>
#using <System.dll>	 
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Diagnostics;

#include "process_win.h"

ProcessWin::ProcessWin(void) {
	InitializeComponent();
}

ProcessWin::~ProcessWin() {
	if (components) {
		delete components;
	}
}

void ProcessWin::InitializeComponent(void) {
	this->SuspendLayout();

	array<Control^>^ ctrls = (gcnew array<Control^>(1)
	{

	});
	this->ResumeLayout(false);
	this->PerformLayout();
}