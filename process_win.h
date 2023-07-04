#pragma once

public ref class ProcessWin : System::Windows::Forms::Form {
public:
	ProcessWin(void);

protected:
	~ProcessWin();

private:
	System::ComponentModel::Container^ components;

	void ProcessWin::InitializeComponent(void);
};