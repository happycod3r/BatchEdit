#pragma once

// The main window is Autobatch's GUI.
public ref class ReferenceWin : System::Windows::Forms::Form
{
public:

	ReferenceWin();

protected:

	~ReferenceWin();

private:
	System::ComponentModel::Component^ components;
	System::Windows::Forms::WebBrowser^ reference_browser;
	void InitializeComponent(void);
	void onReferenceWinLoad(System::Object^ sender, System::EventArgs^ e);
};