#pragma once

public ref class ScriptProcess : System::Diagnostics::Process {
public:
	ScriptProcess(void);

protected:
	~ScriptProcess();

private:
	void InitializeComponent(void);

	void OnExited(System::Object^ sender, System::EventArgs^ e);
};