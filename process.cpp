#using <System.dll>

using namespace System;
using namespace System::Diagnostics;

#include "process.h"

ScriptProcess::ScriptProcess(void) {
	InitializeComponent();
}

ScriptProcess::~ScriptProcess() {

}

void ScriptProcess::InitializeComponent(void) {
	this->Exited += gcnew System::EventHandler(this, &ScriptProcess::OnExited);
}

void ScriptProcess::OnExited(System::Object^ sender, System::EventArgs^ e)
{
	//TODO
}
