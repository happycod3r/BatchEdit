
using namespace System::Diagnostics;
using namespace System::Windows::Forms;

#include "script_runner.h"

ScriptRunner::ScriptRunner(System::String^ file_path) {
	this->init(file_path);
}

ScriptRunner::~ScriptRunner() {

}

void ScriptRunner::init(System::String^ file_path) {
	runScript(file_path);
}

int ScriptRunner::runScript(System::String^ path_to_script) {
	if (!System::String::IsNullOrEmpty(path_to_script))
	{
		Process::Start(path_to_script);
		return 0;
	}
	MessageBox::Show("No script to run!");
	return 1;
}