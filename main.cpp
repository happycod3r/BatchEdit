#include "main.h"
#include "main_win.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	MainWin main_win;
	Application::Run(% main_win);
	return 0;
}

